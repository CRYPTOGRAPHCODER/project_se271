#include "game.h"
#include "functions.h"

std::string gameManager::life_dec(int basic, double rnd_min, double rnd_max){
    double dm = basic*rnd_r(rnd_min, rnd_max)*gv.level;
    int d1;
    if(pl.item_check(13)){
        d1 = (int)(dm*0.7);
    }else{
        d1 = (int)dm;}
    pl.add_life(-d1);
    return "\n" + d.msg_life + std::to_string(d1) + d.msg_sub;
}
std::string gameManager::life_inc(int basic, double rnd_min, double rnd_max){
    double dm = basic*rnd_r(rnd_min, rnd_max);
    int d1;
    if(pl.item_check(16)){
        d1 = (int)(dm*1.3);
    }else{
        d1 = (int)dm;}
    pl.add_life(d1);
    return "\n" + d.msg_life + std::to_string(d1) + d.msg_add;
}
std::string gameManager::life_set(int value){
    int d1 = pl.get_life()-1;
    pl.set_life(value);
    return "\n" + d.msg_life + std::to_string(d1) + d.msg_sub;
}
std::string gameManager::money_dec(int basic, double rnd_min, double rnd_max){
    double dm = basic*rnd_r(rnd_min, rnd_max);
    int d1;
    if(pl.item_check(14)){
        d1 = (int)(dm*0.7/100)*100;
    }else{
        d1 = (int)(dm/100)*100;}

    pl.add_money(-d1);
    return "\n" + d.msg_money + std::to_string(d1) + d.msg_sub;
}
std::string gameManager::money_inc(int basic, double rnd_min, double rnd_max){
    double dm = basic*rnd_r(rnd_min, rnd_max);
    int d1;
    if(pl.item_check(17)){
        d1 = (int)(dm*1.3/100)*100;
    }else{
        d1 = (int)(dm/100)*100;}
    pl.add_money(d1);
    return "\n" + d.msg_money + std::to_string(d1) + d.msg_add;
}
std::string gameManager::stats_dec(int basic, double rnd_min, double rnd_max, int index){
    double dm = basic*rnd_r(rnd_min, rnd_max);
    int d1;
    if(pl.item_check(11)){
        d1 = (int)(dm*0.7);
    }else{
        d1 = (int)dm;}
    pl.add_stats(-d1,index);
    return "\n" + d.msg_stats[index] + std::to_string(d1) + d.msg_sub;
}
std::string gameManager::stats_inc(int basic, double rnd_min, double rnd_max, int index){
    double dm = basic*rnd_r(rnd_min, rnd_max);
    int d1;
    if(pl.item_check(14)){
        d1 = (int)(dm*1.3);
    }else{
        d1 = (int)dm;}
    pl.add_stats(d1,index);
    return "\n" + d.msg_stats[index] + std::to_string(d1) + d.msg_add;
}
std::string gameManager::random_info(double rnd_min, double rnd_max){
    int d2 = (int)(rnd_r(0,gv.subject_num));
    std::string co="";
    co += "\n" + d.subjects[s[d2].title] + d.msg_subject[0];
    co += std::to_string((int)(s[d2].workload[0]*rnd_r(rnd_min,rnd_max)))+",";
    co += std::to_string((int)(s[d2].workload[1]*rnd_r(rnd_min,rnd_max)))+",";
    co += std::to_string((int)(s[d2].workload[2]*rnd_r(rnd_min,rnd_max)))+",";
    co += std::to_string((int)(s[d2].workload[3]*rnd_r(rnd_min,rnd_max)));
    co +=d.msg_subject[1];
    return co;
}
std::string gameManager::workload_var(double rnd_min, double rnd_max,int index){
    //if index = 0 -> every workload
    int d2 = (int)(rnd_r(0,gv.subject_num));
    std::string co="";
    double d1 = rnd_r(rnd_min,rnd_max);
    if(index == 0){
        s[d2].workload[0]*=d1;s[d2].workload[1]*=d1;
        s[d2].workload[2]*=d1;s[d2].workload[3]*=d1;
        co += "\n" + d.subjects[s[d2].title] + d.msg_workload[0];
    }else{
        s[d2].workload[(int)rnd_r(0,4)]*=d1;
        co += "\n" + d.subjects[s[d2].title] + d.msg_workload[1];
    }
    if(d1<1){
        co += std::to_string(d1)+d.msg_workload_dec;
    }else{
        co += std::to_string(d1)+d.msg_workload_inc;
    }
    return co;
}
std::string gameManager::item_get_random(int min, int max){
    int item = 0;
    item = rnd_r(min,max);
    pl.item_add(item);
    return d.msg_item + d.items[item] + d.msg_gain;
}
std::string gameManager::item_loss(){
    int num = 0;
    for(int i=0;i<ITEMS_MAX;i++){
        if(pl.get_items()[i]!=0){
            num = pl.get_items()[i];
            pl.item_delete(i);
            break;
        }
    }
    return d.msg_item + d.items[num] + d.msg_loss;
}

/// Actions
/* Meet Friends
 * 70% get subject information
 * 30% Random
*/
void gameManager::meet_friend(){
    int act = (int)(rnd_r(0, 100));
    //Basic string
    std::string co ="";
    if(act < 30) {              //랜덤 과목 load 안내
        co += d.co_meet_friend[0];
        co += money_dec(20000,0.9,1.1);
        co += random_info(1,1);
    }else if(act < 50) {        //랜덤 과목 load 안내
        co += d.co_meet_friend[1];
        co += life_dec(100,0.8,1.2);
        co += random_info(0.9,1.1);
        co += random_info(0.9,1.1);
    }else if(act < 70) {        //랜덤 과목의 load에 *0.8 혹은 *1.2만큼 곱한 값을 알려준다.
        co += d.co_meet_friend[1];
        co += money_dec(15000,0.9,1.1);
        co += life_dec(70,0.8,1.2);
        co += random_info(0.8,1.2);
        co += random_info(0.8,1.2);
        co += random_info(0.8,1.2);
    }else if(act < 72) {        // 친구 고민상담 / Money ----
        co += d.co_meet_friend[2];
        co += money_dec(50000,0.9,1.2);
    }else if(act < 74) {        // 친구 고민상담 / Money --
        co += d.co_meet_friend[3];
        co += money_dec(16000,0.8,1.4);
    }else if(act < 75){         // 친구 고민상담 / Money ---
        co += d.co_meet_friend[4];
        co += money_dec(32000,0.7,1.6);
    }else if(act < 76){         //친구 고민상담 / Money -
        co += d.co_meet_friend[5];
        co += money_dec(8000,0.5,2.0);
    }else if(act < 79){         //피시방에서 적당히 놀다가 온 경우/ life ++ money -
        co += d.co_meet_friend[6];
        co += money_dec(8000,1.0,1.5);
        co += life_inc(50,0.9,1.1);
    }else if(act < 81) {        //피시방에서 밤늦게 온 경우 / life - money --
        co += d.co_meet_friend[7];
        co += money_dec(16000,1.0,1.5);
        co += life_dec(50,0.9,1.1);
    }else if(act < 82) {        //피시방에서 밤을 샌 경우 / life -- money ---
        co += d.co_meet_friend[8];
        co += money_dec(32000,1.0,1.5);
        co += life_dec(200,0.9,1.1);
    }else if(act < 86) {        //친구와 운동 / life - stats life ++ stats rec ++
        co += d.co_meet_friend[9];
        co += life_dec(100,1,2);
        co += stats_inc(1,1,3,0);
        co += stats_inc(1,1,3,1);
    }else if(act < 88) {        //친구가 교수님을 뵙고 옴, 랜덤 과목 난이도 증가
        co += d.co_meet_friend[10];
        co += workload_var(1.5,1.9,0);
    }else if(act < 90) {        //위와 동일하나 난이도가 감소 하는 이벤트
        co += d.co_meet_friend[11];
        co += workload_var(0.5,0.7,0);
    }else if(act < 95) {        //친구를 만나고 노래방에 간 경우 / money --, life +
        co += d.co_meet_friend[12];
        co += money_dec(4000,1,3);
        co += life_inc(50,0.9,1.1);
    }else if(act < 99) {        //친구를 만나려 했으나 모두 일정이 있어서 아무도 만나지 못함
        co += d.co_meet_friend[13];
    }else {                     //친구들이 모두 일정이 있음 -> 나는 친구들이 모두 일정이 있는 경우가 나올 정도로 친구가 적은 놈임 -> 감정이 블루해짐 / stats life -
        co += stats_dec(1,0.5,2,0);
    }
    // Update Console and Button
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

/* Visit Professor
 * 20% Empty
 * 60% Workload differ
 * 20% Random
*/
void gameManager::visit_professor(){
    int act = (int)(rnd_r(0,100));
    std::string co ="";
    if(act < 20) {              //교수님을 뵈러 갔으나 교수님이 안 계신다. / life ---
        co += d.co_visit_professor[0];
        co += life_dec(50,0.9,1.1);
    }else if(act < 40) {        //Random 과목의 load를 안내
        co += d.co_visit_professor[1];
        co += random_info(1,1);
        co += random_info(1,1);
        co += random_info(1,1);
    }else if(act < 60) {        //Random 과목의 load를 증가
        co += d.co_visit_professor[2];
        co += workload_var(1.7,2.0,0);
        co += workload_var(1.7,2.0,0);
    }else if(act < 80) {        //Random 과목의 load를 감소
        co += d.co_visit_professor[3];
        co += workload_var(0.4,0.6,0);
        co += workload_var(0.4,0.6,0);
    }else if(act < 82) {        //어떻게 공부를 해야하는지 힌트를 얻음 / Random 과목의 stats +++
        co += d.co_visit_professor[4];
        co += stats_inc(1,1,3,2);
        co += stats_inc(1,1,3,3);
        co += stats_inc(1,1,3,4);
        co += stats_inc(1,1,3,5);
    }else if(act < 85) {        //아무일도 일어나지 않는다.
        co += d.co_visit_professor[5];
    }else if(act < 87) {        //진로상담을 받음 / life +++ stats life +++
        co += d.co_visit_professor[6];
        co += stats_inc(1,1,3,0);
        co += stats_inc(1,1,3,1);
        co += life_inc(40,0.9,1.1);
    }else if(act < 89) {        //회식, 행복 / life ++++
        co += d.co_visit_professor[7];
        co += life_inc(100,0.9,1.1);
    }else if(act < 91) {        //서적을 받음 / randome 과목의 stats ++
        co += d.co_visit_professor[8];
        co += stats_inc(1,1,3,rnd_r(2,6));
    }else if(act < 93) {        //격려받음 스텟상승 / randome 과목의 stats ++
        co += d.co_visit_professor[9];
        co += stats_inc(1,1,3,rnd_r(2,6));
    }else if(act < 95) {        //불안해짐 자신감감소 / random 과목의 stats --
        co += d.co_visit_professor[10];
        co += stats_dec(1,1,3,rnd_r(2,6));
    }else {                     //교수님 뵌 줄 알았는데, 꿈이었던거임 엌ㅋ 너무나 귀찮아진것 / life ++, stats life --
        co += d.co_visit_professor[11];
        co += life_inc(50,0.9,1.1);
        co += stats_dec(1,1,3,0);
    }
    // Update Console and Button
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

/* Club Room
 * 30% Item
 * 30% Info
 * 40% Random
*/
void gameManager::club_room(){
    int act = (int)(rnd_r(0,100));
    std::string co ="";
    if(act < 3) {              // Mahjong
        co += d.co_club_room[0];
        co += "\n"+d.co_club_room[1];
        co += life_dec(190,0.9,1.1);
    }else if(act < 6) {        // Mahjong
        co += d.co_club_room[0];
        co += "\n"+d.co_club_room[2];
        co += money_dec(12000,0.9,1.1);
        co += life_inc(60,0.9,1.1);
    }else if(act < 14) {        // Mahjong - Common item
        co += d.co_club_room[0];
        co += "\n"+d.co_club_room[3];
        co += life_dec(90,0.9,1.1);
        co += item_get_random(6,12);
    }else if(act < 22) {        // Mahjong - info
        co += d.co_club_room[0];
        co += "\n"+d.co_club_room[4];
        co += life_dec(80,0.9,1.1);
        co += random_info(0.9,1.1);
        co += random_info(0.9,1.1);
    }else if(act < 24) {        // Mahjong
        co += d.co_club_room[0];
        co += "\n"+d.co_club_room[5];
        co += life_inc(50,0.9,1.1);
    }else if(act < 25) {        // Mahjong
        co += d.co_club_room[0];
        co += "\n"+d.co_club_room[6];
        co += life_inc(80,0.9,1.1);
        co += money_dec(20000,0.9,1.1);
    }

    else if(act < 35) {        // 3D Printer - item
        co += d.co_club_room[10];
        co += "\n"+d.co_club_room[11];
        co += life_dec(60,0.9,1.1);
        co += item_get_random(1,3);
    }else if(act < 36) {        // 3D Printer - computer
        co += d.co_club_room[10];
        co += "\n"+d.co_club_room[12];
        co += life_dec(110,0.9,1.1);
        co += item_get_random(17,17);
    }else if(act < 44) {        // 3D Printer - info
        co += d.co_club_room[10];
        co += "\n"+d.co_club_room[13];
        co += life_dec(90,0.9,1.1);
        co += random_info(0.9,1.1);
        co += random_info(0.9,1.1);
    }else if(act < 47) {        // 3D Printer
        co += d.co_club_room[10];
        co += "\n"+d.co_club_room[14];
        co += life_dec(50,0.9,1.1);
        co += stats_inc(1,1,2.5,3);
    }else if(act < 49) {        // 3D Printer
        co += d.co_club_room[10];
        co += "\n"+d.co_club_room[15];
        co += life_dec(100,0.9,1.1);
        co += stats_inc(1,2.5,4,3);
    }else if(act < 50) {        // 3D Printer
        co += d.co_club_room[10];
        co += "\n"+d.co_club_room[16];
        co += life_dec(150,0.9,1.1);
        co += stats_inc(1,4,6,3);
    }

    else if(act < 58) {         // book - common item
        co += d.co_club_room[20];
        co += "\n"+d.co_club_room[21];
        co += life_dec(60,0.9,1.1);
        co += item_get_random(1,3);
    }else if(act < 59) {        // book - necronomicon
        co += d.co_club_room[20];
        co += "\n"+d.co_club_room[22];
        co += life_dec(50,0.9,1.1);
        co += item_get_random(34,34);
    }else if(act < 60) {        // book - info
        co += d.co_club_room[20];
        co += "\n"+d.co_club_room[23];
        co += life_dec(50,0.9,1.1);
        co += random_info(0.9,1.1);
        co += random_info(0.9,1.1);
    }else if(act < 67) {        // book
        co += d.co_club_room[20];
        co += "\n"+d.co_club_room[24];
        co += life_dec(50,0.9,1.1);
        co += stats_inc(1,2,4,4);
    }else if(act < 69) {        // book
        co += d.co_club_room[20];
        co += "\n"+d.co_club_room[25];
        co += life_dec(100,0.9,1.1);
        co += stats_inc(1,3,6,4);
    }else if(act < 71) {        // book
        co += d.co_club_room[20];
        co += "\n"+d.co_club_room[26];
        co += life_dec(50,0.9,1.1);
        co += stats_dec(1,1,2.5,2);
        co += stats_dec(1,1,2.5,3);
        co += stats_dec(1,1,2.5,4);
        co += stats_dec(1,1,2.5,5);
    }else if(act < 73) {        // book
        co += d.co_club_room[20];
        co += "\n"+d.co_club_room[27];
        co += life_dec(50,0.9,1.1);
        co += stats_inc(1,2,4,5);
    }else if(act < 75) {        // book
        co += d.co_club_room[20];
        co += "\n"+d.co_club_room[28];
        co += life_dec(90,0.9,1.1);
        co += stats_inc(1,3,6,5);
    }

    else if(act < 85) {         // math hw - items
        co += d.co_club_room[30];
        co += "\n"+d.co_club_room[31];
        co += life_dec(60,0.9,1.1);
        co += item_get_random(6,12);
    }else if(act < 86) {        // math hw - rare items
        co += d.co_club_room[30];
        co += "\n"+d.co_club_room[32];
        co += life_dec(50,0.9,1.1);
        co += item_get_random(33,33);
    }else if(act < 91) {        // math hw - info
        co += d.co_club_room[30];
        co += "\n"+d.co_club_room[33];
        co += life_dec(50,0.9,1.1);
        co += random_info(0.9,1.1);
        co += random_info(0.9,1.1);
    }else if(act < 94) {        // math hw
        co += d.co_club_room[30];
        co += "\n"+d.co_club_room[34];
        co += life_dec(50,0.9,1.1);
        co += stats_inc(1,1,3,2);
    }else if(act < 97) {        // math hw
        co += d.co_club_room[30];
        co += "\n"+d.co_club_room[35];
        co += life_dec(100,0.9,1.1);
        co += stats_inc(1,2,4,2);
    }else {        // math hw
        co += d.co_club_room[30];
        co += "\n"+d.co_club_room[36];
        co += life_dec(170,0.9,1.1);
        co += stats_inc(1,3,6,2);
    }
    // Update Console and Button
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

/* main - work
 * 60% Normal Work
*/
void gameManager::work(){
    int act = (int)(rnd_r(0, 100));
    //Basic string
    std::string co ="";
    if(act < 60) {              // 노동의 기쁨 life- money++
        co += d.co_work[0];
        co += money_inc(40000,0.8,1.2);
        co += life_dec(100,0.9,1.1);
    }else if(act < 63) {        // 헛수고 life-
        co += d.co_work[1];
        co += life_dec(80,0.9,1.1);
    }else if(act < 66) {        // 악덕사장 life--
        co += d.co_work[2];
        co += life_dec(160,0.9,1.1);
    }else if(act < 67) {        // 돈갖고 튀어라 life- money++++
        co += d.co_work[3];
        co += money_inc(200000,0.8,1.2);
        co += life_dec(100,0.9,1.1);
    }else if(act < 73) {        // 재능 기부 life- stat+
        co += d.co_work[4];
        co += life_dec(90,0.9,1.1);
        co += stats_inc(1,1,3,2);
        co += stats_inc(1,1,3,3);
        co += stats_inc(1,1,3,4);
        co += stats_inc(1,1,3,5);
    }else if(act < 78) {        // 공짜 돈 money+
        co += d.co_work[5];
        co += money_inc(20000,0.8,1.2);
    }else if(act < 85) {        // 내 시급 어디? life-- lifestat+
        co += d.co_work[6];
        co += life_dec(120,0.9,1.1);
        co += stats_inc(1,1,3,0);
        co += stats_inc(1,1,3,1);
    }else if(act < 88) {        // 구직난 -
        co += d.co_work[7];
    }else if(act < 91) {        // 너무 많은 일자리
        co += d.co_work[8];
    }else if(act < 95) {        // 일들의 연속 life-- lifestat- money+++
        co += d.co_work[9];
        co += money_inc(80000,0.8,1.2);
        co += life_dec(120,0.9,1.1);
        co += stats_dec(1,1,3,0);
        co += stats_dec(1,1,3,1);
    }else {                     // 이것도 일 life+ lifestat+
        co += d.co_work[10];
        co += life_inc(40,0.9,1.1);
        co += stats_inc(1,1,3,0);
    }
    // Update Console and Buttons
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

/* main - rest
 * 70% increase health
*/
void gameManager::rest(){
    int act = (int)(rnd_r(0, 100));
    //Basic string
    std::string co ="";
    if(act < 70) {              // 휴식 life +++
        co += d.co_rest[0];
        if(pl.item_check(19)){
            co += life_inc(260,0.9,1.1);
        }else{
            co += life_inc(200,0.9,1.1);}
    }else if(act < 73){         // 내 사전에 휴식은 없다 life-- stat++
        co += d.co_rest[1];
        co += life_dec(80,0.9,1.1);
        co += stats_inc(1,3,5,rnd_r(2,6));
    }else if(act < 76){         // 비디오 게임 life+ stat-
        co += d.co_rest[2];
        co += life_inc(80,0.9,1.1);
        co += stats_dec(1,0,2,rnd_r(2,6));
    }else if(act < 78){         // 비디오 게임 life+ stat+
        co += d.co_rest[3];
        co += life_inc(80,0.9,1.1);
        co += stats_inc(1,0,2,rnd_r(2,6));
    }else if(act < 80){         // 뒤죽박죽 stat random, life+++ hpstat+
        co += d.co_rest[4];
        co += life_inc(200,0.9,1.1);
        co += stats_inc(1,3,3,0);
        co += stats_inc(1,3,3,1);
        co += stats_inc(1,0,3,2);
        co += stats_inc(1,0,3,3);
        co += stats_inc(1,0,3,4);
        co += stats_inc(1,0,3,5);
    }else if(act < 85){         // 소란 -
        co += d.co_rest[5];
    }else if(act < 86){         // 1석2조 - hp+++ stat++
        co += d.co_rest[6];
        co += life_inc(170,0.9,1.1);
        co += stats_inc(1,1,3,0);
    }else if(act < 88){         // TV - hp+ soci+
        co += d.co_rest[7];
        co += life_inc(50,0.9,1.1);
        co += stats_inc(1,1,3,0);
    }else if(act < 90){         // TV - hp+ stat+
        co += d.co_rest[8];
        co += life_inc(60,0.9,1.1);
        co += stats_inc(1,1,3,0);
    }else if(act < 92){         // Friends - hp + money-
        co += d.co_rest[9];
        co += life_inc(70,0.9,1.1);
        co += money_dec(6000,0.9,1.1);
    }else if(act < 95){         // Friends HP++ INFO
        co += d.co_rest[9];
        co += life_inc(120,0.9,1.1);
        co += random_info(1,1);
    }else if(act < 97){         // Empty - HP++
        co += d.co_rest[9];
        co += life_inc(180,0.9,1.1);
    }else{                      // Empty - HP-
        co += d.co_rest[10];
        co += life_dec(30,0.9,1.1);
    }
    // Update console and Buttons
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

/* main - study
 * increase random study stat
 * lose helath
*/
void gameManager::study(){
    int act = (int)(rnd_r(0, 100));
    //Basic string
    std::string co ="";
    if(act < 70) {              // Study stat++ hp--
        co += d.co_study[(int)(rnd_r(0,3))];
        double min = 1;
        double max = 2.5;
        if(pl.item_check(20)){
            min*=1.3; max*=1.3;
        }
        co += stats_inc(1,min,max,2);
        co += stats_inc(1,min,max,3);
        co += stats_inc(1,min,max,4);
        co += stats_inc(1,min,max,5);
        co += life_dec(190,0.9,1.1);
    }else if(act < 75) {        // Study?
        co += d.co_study[3];
    }else if(act < 78) {        // GakSung stat +++ life--
        co += d.co_study[4];
        co += stats_inc(1,2,4.5,2);
        co += stats_inc(1,2,4.5,3);
        co += stats_inc(1,2,4.5,4);
        co += stats_inc(1,2,4.5,5);
        co += life_dec(210,0.9,1.1);
    }else if(act < 83) {        // Rest - hp+ stat+
        co += d.co_study[5];
        co += stats_inc(1,1,3,0);
        co += stats_inc(1,0,2,1);
        co += life_inc(40,0.9,1.1);
    }else if(act < 88) {        // Tutoring stat+ hp-
        co += d.co_study[6];
        co += stats_inc(1,2,4.5,rnd_r(2,6));
        co += stats_inc(1,2,4.5,rnd_r(2,6));
        co += life_dec(90,0.9,1.1);
    }else if(act < 92) {        // Exhaust stat+++ stat- hp----
        co += d.co_study[7];
        co += stats_dec(1,3,5,2);
        co += stats_dec(1,1,3,3);
        co += stats_inc(1,4,6,2);
        co += stats_inc(1,4,6,3);
        co += stats_inc(1,4,6,4);
        co += stats_inc(1,4,6,5);
        co += life_dec(300,0.9,1.1);
    }else if(act < 95) {        // NT
        co += d.co_study[8];
    }else if(act < 98) {        // NT
        co += d.co_study[9];
    }else {                     // Treasure
        co += d.co_study[10];
        co += money_inc(9000,0.9,1.1);
    }
    // Update console and buttons
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

/* main - exercise
 * 60% Excercise
*/
void gameManager::exercise(){
    int act = (int)(rnd_r(0, 100));
    //Basic string
    std::string co ="";
    if(act < 63) {              // Exercise hp-- stat+
        co += d.co_exercise[(int)(rnd_r(0,2))];
        double min = 2;
        double max = 4.5;
        if(pl.item_check(21)){
            min*=1.3; max*=1.3;
        }
        co += stats_inc(1,min,max,0);
        co += stats_inc(1,min/2,max/2,1);
        co += life_dec(160,0.9,1.1);
    }else if(act < 70) {        // Overwork hp-- stat-
        co += d.co_exercise[2];
        co += stats_dec(1,1,2.5,0);
        co += stats_dec(1,1,2.5,1);
        co += life_dec(250,0.9,1.1);
    }else if(act < 73) {        // Dream shift hp- stat+ stat-
        co += d.co_exercise[3];
        co += stats_inc(1,1.5,4.5,0);
        co += stats_inc(1,1,2.5,1);
        co += stats_dec(1,0.5,2,2);
        co += stats_dec(1,0.5,2,3);
        co += stats_dec(1,0.5,2,4);
        co += stats_dec(1,0.5,2,5);
        co += life_dec(150,0.9,1.1);
    }else if(act < 76) {        // Vending Machine Money++ hp--
        co += d.co_exercise[4];
        co += money_inc(3000,0.9,1.1);
        co += life_dec(30,0.9,1.1);
    }else if(act < 84) {        // Nothing
        co += d.co_exercise[5];
    }else if(act < 89) {        // Special Training hp-
        co += d.co_exercise[6];
        co += stats_inc(1,4,8,0);
        co += stats_inc(1,3,5,1);
        co += life_dec(250,0.9,1.1);
    }else if(act < 93) {        // Spent
        co += d.co_exercise[7];
        co += stats_inc(1,2.5,5,0);
        co += stats_inc(1,1.5,3,1);
        co += life_dec(170,0.9,1.1);
    }else if(act < 94) {        // Critical hp---- stat-;
        co += d.co_exercise[8];
        co += stats_dec(1,4,6,0);
        co += stats_dec(1,2,5,1);
        co += life_set(1);
    }else if(act < 97) {        // Bowling - Win
        co += d.co_exercise[9];
        co += stats_inc(1,2,4,0);
        co += stats_inc(1,1,2.2,1);
        co += life_dec(130,0.9,1.1);
    }else {                     // Bowling - Lose
        co += d.co_exercise[10];
        co += stats_inc(1,2,4,0);
        co += stats_inc(1,1,2.2,1);
        co += life_dec(130,0.9,1.1);
        co += money_dec(3000,0.9,1.1);
    }
    // Update Console and Buttons
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}


/* Wander Around
 * 100% Random
*/
void gameManager::wander_around(){
    int act = rnd_r(0,58);
    //Console string initialize
    std::string co ="";

    if(act<5){          // 멍 때리기 - STAT--
        co += d.co_wander_around[0];
        co += stats_dec(1,1.5,3,2);
        co += stats_dec(1,1.5,3,3);
        co += stats_dec(1,1.5,3,4);
        co += stats_dec(1,1.5,3,5);
    }else if(act<9){    // 달리기 선수 - HPST++ HP--;
        co +=d.co_wander_around[1];
        co += stats_inc(1,3,6,0);
        co += life_dec(100,0.9,1.2);
    }else if(act<13){   // 전력 질주 - HP--
        co += d.co_wander_around[2];
        co += life_dec(100,0.9,1.2);
        co += item_get_random(6,12);
    }else if(act<17){   // 사소한 충돌 - No change
        co += d.co_wander_around[3];
    }else if(act<21){   // 사소한 충돌 - $+
        co += d.co_wander_around[4];
        co += money_inc(10000,0.9,1.1);
    }else if(act<25){   // 사소한 충돌 - HP---, RECO-
        co += d.co_wander_around[5];
        co += stats_dec(1,2,4,0);
        co += life_dec(150,0.9,1.2);
    }else if(act<30){   // 책의 힘 - LITE++
        co += d.co_wander_around[6];
        co += stats_inc(1,3,6,4);
    }else if(act<35){   // 책의 힘 - SCIN+ CODE+
        co+=d.co_wander_around[7];
        co += stats_inc(1,2.5,5,2);
        co += stats_inc(1,2.5,5,3);
    }else if(act<40){   // 책의 힘 - No change
        co += d.co_wander_around[8];
    }else if(act<43){   // 친구의 선물 - Add Item
        co += d.co_wander_around[9];
        co += item_get_random(11,17);
    }else if(act<46){   // 친구의 선물 - No change
        co += d.co_wander_around[10];
    }else if(act<48){   // 도플갱어 - Soul of GDS
        co += d.co_wander_around[11];
        co += item_get_random(30,30);
    }else if(act<50){   // 도플갱어 all stat**
        co += d.co_wander_around[12];
        co += stats_inc(pl.get_stats()[0],1.3,1.6,0);
        co += stats_inc(pl.get_stats()[1],1.3,1.6,1);
        co += stats_inc(pl.get_stats()[2],1.3,1.6,2);
        co += stats_inc(pl.get_stats()[3],1.3,1.6,3);
        co += stats_inc(pl.get_stats()[4],1.3,1.6,4);
        co += stats_inc(pl.get_stats()[5],1.3,1.6,5);
    }else if(act<55){   // 소매치기 money---
        co += d.co_wander_around[13];
        co += money_dec(pl.get_money(),0.5,0.9);
    }else if(act<58){   // 강도 item -
        co += d.co_wander_around[14];
        co += item_loss();
    }else if(act<63){   // 오늘은 내가 요리사 HPST+ RECO+ HP+
        co += d.co_wander_around[15];
        co += stats_inc(1,2,5,0);
        co += stats_inc(1,2,3,1);
        co += life_inc(100,0.9,1.1);
    }else if(act<68){   // 오늘은 내가 요리사 HPST- RECO- HP-
        co += d.co_wander_around[16];
        co += stats_dec(1,2,5,0);
        co += stats_dec(1,2,3,1);
        co += life_dec(100,0.9,1.1);
    }else if(act<73){   // 친구의 질문   SCIE+ CODE+
        co += d.co_wander_around[17];
        co += stats_inc(1,2,4,2);
        co += stats_inc(1,2,4,3);
    }else if(act<78){   // 친구의 질문 Nothing
        co += d.co_wander_around[18];
    }else if(act<82){   // 실험 조언 SCIE- CODE-
        co += d.co_wander_around[19];
        co += stats_dec(1,1,3,2);
        co += stats_dec(1,1,3,3);
    }else if(act<87){   // 목적 없는 사람 Nothing
        co += d.co_wander_around[20];
    }else if(act<90){   // 특강 ITEM+
        co += d.co_wander_around[21];
        co += item_get_random(29,29);
    }else if(act<95){   // 특강 HP+
        co += d.co_wander_around[22];
        co += life_inc(60,0.9,1.1);
    }else{              // 의미 없는 토론
        co += d.co_wander_around[23];
        co += stats_dec(1,1,3,4);
        co += stats_dec(1,1,3,5);
    }
    print_update(co,d.bt_wander_around);
    // End turn
    game_turn_pass();
}

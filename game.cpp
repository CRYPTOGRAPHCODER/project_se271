#include "game.h"
#include "functions.h"
#include "player.h"

gameManager::gameManager(){
    gv.turn = 0;
    gv.level = 1;
    gv.subject_num = 35;
    generate_subjects();
    for(int i=0;i<BUTTON_LENGTH;i++){
        this->button[i]="";
    }
    item_value_update();
    print_update(d.co_intro01,d.bt_basic);
}

gameManager::~gameManager(){
    //delete[] s;
}

// gamestate
// 0~19 : intro
// 20 : Main Turn 21 : Go outside 22 : Connect Internet
// 23 : Store 24 : Rest at home 25 : Study
// 26 : Exercise 44 : game over 100~ : sugang

/// Proceed

void gameManager::proceed(int input){
    switch(gv.gamestate){
    case 0:
        gv.gamestate ++;        // To Intro 2
        print_update(d.co_intro02,d.bt_basic);
        break;
    case 1:
        gv.gamestate ++;        // To Intro 3
        print_update(d.co_intro03,d.bt_basic);
        break;
    case 2:
        gv.gamestate ++;        // To Intro 4
        print_update(d.co_intro04,d.bt_basic);
        break;
    case 3:
        gv.gamestate ++;        // To Intro 4
        print_update(d.co_intro05,d.bt_basic);
        break;
    case 4:
        gv.gamestate ++;        // To Intro 4
        print_update(d.co_intro06,d.bt_basic);
        break;
    case 5:
        gv.gamestate = 20;      // To Main
        print_update(d.co_main,d.bt_main);
        break;
    case 20:                                            // Main
        gv.gamestate += input;
        switch(input){
        case 1:
            print_update(d.co_outside,d.bt_outside);break;   // To Outside
        case 2:
            print_update(d.co_sugang,d.bt_sugang);break;     // To Sugang
        case 3:
            print_update(d.co_store,d.bt_store);break;       // To Store
        case 4:
            rest();break;                                    // To Rest
        case 5:
            study();break;                                   // To Study
        case 6:
            exercise();break;                                // To Exercise
        default:
            break;
        }
        break;
    case 21:                                            // Outside
        switch(input){
        case 1:
            meet_friend();gv.gamestate = 31;break;       // To Meet Friend
        case 2:
            club_room();gv.gamestate = 31;break;         // To Club Room
        case 3:
            visit_professor();gv.gamestate = 31;break;   // To Visit Professor
        case 4:
            wander_around();gv.gamestate = 31;break;     // To Wander around
        case 5:
            work();gv.gamestate = 31;break;              // To Work
        case 9:
            gv.gamestate = 20;print_update(d.co_main,d.bt_main);break; // Back to Main
        default: break;
        }
        break;
    case 22:                                            // Sugang
        switch(input){
        case 1:                                             // To Login
            if(gv.turn%40<28){                       // Back to Main if Day<8
                gv.gamestate = 20;
                print_update(d.co_main, d.bt_main);
            }
            else{                                           // Login Successful
                gv.gamestate = 101;
                print_sugang_apply(gv.gamestate - 100,'n');
            }
            break;
        case 2:                                             // View Sugang Data
            gv.gamestate = 100;
            print_sugang_data();
            break;
        case 3:
            gv.gamestate = 98;
            print_sugang_my_data();
            break;
        case 9:                                             // Back To Main
            gv.gamestate = 20;
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 23:                                                // Store (Not Available)
        switch(input){
        case 1:                                                 // Buy
            gv.gamestate = 81;
            print_store_buy(1);
            break;
        case 2:                                                 // Sell
            gv.gamestate = 80;
            print_store_sell();
            break;
        default:
            gv.gamestate = 20;
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 81: case 82: case 83: case 84: case 85: case 86:
        switch(input){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            buy_item((gv.gamestate-81)*7+input);
            print_store_buy(gv.gamestate - 80);
            break;
        case 8:                                             // View Next Items
            if(gv.gamestate >= (80 + d.item_number/7 + 1)){
                gv.gamestate = 80;
            }
            gv.gamestate += 1;
            print_store_buy(gv.gamestate-80);
            break;
        case 9:
            gv.gamestate = 20;                           // To Main Menu
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 80:
        switch(input){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
            item_sell(input-1);
            print_store_sell();
            break;
        case 9:
            gv.gamestate = 20;                           // To Main Menu
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 99:                                            // Sugang logout
        gv.gamestate = 20;
        print_update(d.co_main,d.bt_main);
        game_turn_pass();
        break;
                                                        // Sugang Login
    case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115:
        switch(input){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            gv.s_time -= (int)(rnd_r(10.0,13.0));   // Decrease Time
            sugang_time_decrease(10.0,13.0);
            sugang_apply((gv.gamestate-101)*7+input-1);  // Apply to subject
            if(gv.s_time <= 0){
                gv.gamestate = 99;
                sugang_time_pass(1000);
                print_update(d.co_logout,d.bt_logout);
            }
            break;
        case 8:                                             // View Next Subject
            if(gv.gamestate >= (100 + gv.subject_num/7 + 1)){
                gv.gamestate = 100;
            }
            gv.gamestate += 1;
            print_sugang_apply(gv.gamestate - 100,'n');
            sugang_time_decrease(1.0,3.0);
            if(gv.s_time <= 0){
                gv.gamestate = 99;
                sugang_time_pass(1000);
                print_update(d.co_logout,d.bt_logout);
            }
            break;
        case 9:
            gv.gamestate = 20;                           // To Main Menu, spend turn
            print_update(d.co_main,d.bt_main);
            game_turn_pass();
            break;
        }
        break;
    case 40:                                                // Semester reset
        gv.gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    case 44:                                                // Game over
        break;
    case 77:                                                // Game Clear
        break;
    case 24: case 25: case 26: case 27:case 31: case 98: case 100:   // Default Cases
    default:
        gv.gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    }
}

/* turn pass event for almost every action
*/
void gameManager::game_turn_pass(){
    // Gradually increase level
    gv.level *= 1.01;
    // Reset sugang time
    gv.s_time = gv.s_time_full;

    // player data update
    pl.stat_update();

    // Sugang time pass
    if(gv.turn%40>=28){
        sugang_time_pass(300);
    }

    /// Item effects
    // Item 1
    if(pl.item_check(18)){
        gv.s_time = gv.s_time*1.5;}
    // Item 2
    if(pl.item_check(34)){
        pl.add_life(60);}
    // Item 5
    if(pl.item_check(35)){
        pl.add_life(30);}
    // Item 30
    if(pl.get_life()<=0 && pl.item_check(30)==true){
        pl.set_life(pl.get_life_f()*0.3);
        pl.item_delete_find(30);
    }
    /// Item Values
    item_value_update();
    /// Bytecoin
    d.item_value[29]=(int)(d.item_value[29]*rnd_r(0.8,1.2));
    if(d.item_value[29]>10000000){
        d.item_value[29] = 10000000;
    }
    if(d.item_value[29]<10000){
        d.item_value[29] = 10000;
    }
    // Calculate semester
    if(gv.turn%40==39){
        calculate_semester();
    }
    /// Add Score
    pl.add_score_turn(gv.turn,gv.level);
    // Game Clear Check
    if(pl.get_life()>0 && pl.get_credit_acquired_chs()>=pl.get_credit_required_chs()&&pl.get_credit_acquired_ess()>=pl.get_credit_required_ess()){
        gv.gamestate = 77;
        std::string c="";
        for(int i=0;i<6;i++){
            c+=d.co_gameclear[i];}
        print_update(c,d.bt_gameclear);
    }
    // Game Over Check - Should be last step
    if(pl.get_life()<=0){
        pl.set_life(0);
        gv.gamestate = 44;
        std::string c="";
        for(int i=0;i<6;i++){
            c+=d.co_gameover[i];}
        print_update(c,d.bt_gameover);
    }
    gv.turn ++;
}

std::string print_blank(int data,int tab){
    std::string o = std::to_string(data);
    for(int i=std::to_string(data).length();i<tab;i++){
        o+=" ";
    }
    return o;
}

/* calculating semester
 * only function that can handle gamestate except proceed
*/
void gameManager::calculate_semester(){
    gv.gamestate = 40;
    std::string c = d.co_semester[0];
    c+= "";
    c+= "\n   |     과목의 어려운 정도    |";
    c+= "\n학점| 이학 | 공학 | 문학 | 사회 |체력소모|학점|과목명";
    int drain_total = 0;
    int credit_total = 0;
    for(int i = 0; i<SUBJECTS_MAX;i++){
        if(pl.get_subjects()[i]==-1){
            continue;
        }
        c+= "\n";
        int l = pl.get_subjects()[i];
        c+= " "+ std::to_string(s[l].credit)+" |";
        c+= print_blank(s[l].workload[0],6)+"|";
        c+= print_blank(s[l].workload[1],6)+"|";
        c+= print_blank(s[l].workload[2],6)+"|";
        c+= print_blank(s[l].workload[3],6)+"|";
        if(pl.item_check(22)){
            s[l].workload[0]*=0.9;s[l].workload[1]*=0.9;
            s[l].workload[2]*=0.9;s[l].workload[3]*=0.9;
        }
        if(pl.item_check(23)){
            s[l].workload[0]*=0.9;
        }
        if(pl.item_check(24)){
            s[l].workload[1]*=0.9;
        }
        if(pl.item_check(25)){
            s[l].workload[2]*=0.9;
        }
        if(pl.item_check(26)){
            s[l].workload[3]*=0.9;
        }
        int drain = s[l].workload[0]/pl.get_stats()[2]+s[l].workload[1]/pl.get_stats()[3]+s[l].workload[2]/pl.get_stats()[4]+s[l].workload[3]/pl.get_stats()[5];
        c+= print_blank(drain,7)+"|";
        drain_total += drain;
        if(drain<pl.get_life_f()/30){
            c+=" A |";
        }else if(drain<pl.get_life_f()/25*s[l].credit){
            c+=" B |";
        }else if(drain<pl.get_life_f()/18*s[l].credit){
            c+=" C |";
        }else if(drain<pl.get_life_f()/12*s[l].credit){
            c+=" D |";
        }else{
            c+=" F |";
        }
        std::string m = d.subjects[s[l].title];
        if(s[i].level == 2){
            m+=" II";
        }else if(s[i].level == 3){
            m+=" III";
        }else if(s[i].level == 4){
            m+=" IV";
        }
        c+=m;




        // Effect to player
        pl.add_life(-drain);
        if(drain<pl.get_life_f()/12*s[l].credit){
            if(s[i].category==0){
                pl.add_credit_acquired_ess(s[l].credit);
            }else{
                pl.add_credit_acquired_chs(s[l].credit);
            }
            pl.add_score(drain);
        }
        if(drain>pl.get_life_f()/12*s[l].credit){
            if(pl.item_check(27)){
                if(s[i].category==0){
                    pl.add_credit_acquired_ess(s[l].credit);
                }else{
                    pl.add_credit_acquired_chs(s[l].credit);
                }
                pl.item_delete_find(27);
            }
            pl.add_score(drain/5);
        }
        credit_total += s[l].credit;
        // bonus stat for subjects
        pl.add_stats(s[l].credit*s[l].workload[s[l].area-2]/500,s[l].area-2);
    }
    pl.add_stats((int)(credit_total-10)/2,0);
    pl.add_stats((int)(credit_total-10)/4,1);
    pl.add_stats((int)(credit_total-10)/4,2);
    pl.add_stats((int)(credit_total-10)/4,3);
    pl.add_stats((int)(credit_total-10)/4,4);
    pl.add_stats((int)(credit_total-10)/4,5);

    c += "\n\n"+d.co_semester[1];
    gv.subject_num += (int)(rnd_r(5,8));
    if(gv.subject_num>=100){
        gv.subject_num = 100;
    }
    for(int j=0;j<SUBJECTS_MAX;j++){
        pl.set_subjects(-1,j);
    }

    generate_subjects();
    print_update(c,d.bt_semester);
}



void gameManager::print_update(std::string co, std::string* bt){
    this->console = co;
    for(int i=0;i<BUTTON_LENGTH;i++){this->button[i]=bt[i];}
    if(co==""){
        this->console = "ERROR";
        for(int i=0;i<9;i++){this->button[i]="";}
    }
    // For Debug
    // this->console += "\n\n"+std::to_string(gamestate);
}



void gameManager::buy_item(int index){
    if(pl.get_money()>=(int)(d.item_value[index])){
        pl.add_money(-(int)(d.item_value[index]));
        pl.item_add(index);
    }
    item_value_update();
}
void gameManager::print_store_buy(int index){
    std::string c = d.co_store_buy;
    std::string k[9] = d.bt_store_buy;
    for (int i=0;i<7;i++){
        int p = (index-1)*7+i+1;
        // Disable button if there are no subject data
        if(p>=d.item_shop){
            k[i] = "";
            continue;
        }
        std::string b = "\"";
        b+= d.items[p]+"\" 효과:";
        b+= d.items_ex[p];
        b+= " 가격:"+std::to_string((int)(d.item_value[p]));
        k[i] = b;
    }
    print_update(c,k);
}
void gameManager::print_store_sell(){
    std::string c = d.co_store_sell;
    std::string k[9] = d.bt_store_sell;
    for (int i=0;i<8;i++){
        if(pl.get_items()[i]<=0){
            k[i] = "";
            continue;
        }
        std::string b = "";
        b+= d.items[pl.get_items()[i]];
        if(pl.get_items()[i]==29 || pl.get_items()[i]==31){
            b+= " 가격: "+std::to_string((int)(d.item_value[pl.get_items()[i]]*0.9));
        }else{
            b+= " 가격: "+std::to_string((int)(d.item_value[pl.get_items()[i]]*0.2));
        }
        k[i] = b;
    }
    print_update(c,k);
}
void gameManager::item_sell(int index){
    switch(pl.get_items()[index]){
    case 29: case 31:
        pl.add_money((int)(d.item_value[pl.get_items()[index]]*0.9));
        break;
    default:
        pl.add_money((int)(d.item_value[pl.get_items()[index]]*0.2));
        break;
    }
    pl.item_delete(index);
}

void gameManager::item_value_update(){

    d.item_value[3] = pl.get_life_f()*38;
    if(d.item_value[3]<300000){
        d.item_value[3]=300000;
    }
    d.item_value[4] = pl.get_life_f()*70;
    if(d.item_value[4]<600000){
        d.item_value[4]=600000;
    }
    d.item_value[5] = 5000;
    for(int i=0;i<pl.get_stats()[0];i++){
        d.item_value[5]*=1.07;
    }
    d.item_value[6] = 7000;
    for(int i=0;i<pl.get_stats()[1];i++){
        d.item_value[6]*=1.07;
    }
    d.item_value[7] = 3000;
    for(int i=0;i<pl.get_stats()[2];i++){
        d.item_value[7]*=1.07;
    }
    d.item_value[8] = 3000;
    for(int i=0;i<pl.get_stats()[3];i++){
        d.item_value[8]*=1.07;
    }
    d.item_value[9] = 3000;
    for(int i=0;i<pl.get_stats()[4];i++){
        d.item_value[9]*=1.07;
    }
    d.item_value[10] = 3000;
    for(int i=0;i<pl.get_stats()[5];i++){
        d.item_value[10]*=1.07;
    }
}

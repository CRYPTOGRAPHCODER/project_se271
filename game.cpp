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
    print_update(d.co_intro01,d.bt_intro);
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
        print_update(d.co_intro02,d.bt_intro);
        break;
    case 1:
        gv.gamestate ++;        // To Intro 3
        print_update(d.co_intro03,d.bt_intro);
        break;
    case 2:
        gv.gamestate ++;        // To Intro 4
        print_update(d.co_intro04,d.bt_intro);
        break;
    case 3:
        gv.gamestate ++;        // To Intro 4
        print_update(d.co_intro05,d.bt_intro);
        break;
    case 4:
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
                print_sugang_apply(gv.gamestate - 100);
            }
            break;
        case 2:                                             // View Sugang Data
            gv.gamestate = 100;
            print_sugang_data();
            break;
        case 9:                                             // Back To Main
            gv.gamestate = 20;
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 23:                                                // Store (Not Available)
        //print_update(d.co_store,d.bt_store);
        gv.gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
                                                        // Sugang Login
    case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115:
        switch(input){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            sugang_apply((gv.gamestate-101)*7+input-1);  // Apply to subject
            gv.s_time -= (int)(rnd_r(10.0,13.0));   // Decrease Time
            sugang_time_decrease(10.0,13.0);
            print_sugang_apply(gv.gamestate-100);
            if(gv.s_time <= 0){
                gv.s_time = gv.s_time_full;
                gv.gamestate = 20;
                print_update(d.co_main,d.bt_main);
                sugang_time_pass(1000);
                game_turn_pass();
            }
            break;
        case 8:                                             // View Next Subject
            if(gv.gamestate >= (100 + gv.subject_num/7 + 1)){
                gv.gamestate = 100;
            }
            gv.gamestate += 1;
            sugang_time_decrease(1.0,3.0);
            if(gv.s_time <= 0){
                gv.s_time = gv.s_time_full;
                gv.gamestate = 20;
                print_update(d.co_main,d.bt_main);
                sugang_time_pass(1000);
                game_turn_pass();
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
    case 44:
        break;
    case 24: case 25: case 26: case 27:case 31: case 100:   // Default Cases
    default:
        gv.gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    }
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
    for(int i = 0; i<SUBJECTS_MAX;i++){
        if(pl.get_subjects()[i]==-1){
            continue;
        }
        c+= "\n";
        int l = pl.get_subjects()[i];
        c+= " "+ std::to_string(s[l].credit)+" |";
        c+= std::to_string(s[l].workload[0]);
        if(s[l].workload[0]<1000){
            c+= "  |";
        }else if(s[l].workload[0]<10000){
            c+= " |";
        }else{
            c+= "|";
        }
        c+= std::to_string(s[l].workload[1]);
        if(s[l].workload[1]<1000){
            c+= "  |";
        }else if(s[l].workload[1]<10000){
            c+= " |";
        }else{
            c+= "|";
        }
        c+= std::to_string(s[l].workload[2]);
        if(s[l].workload[2]<1000){
            c+= "  |";
        }else if(s[l].workload[2]<10000){
            c+= " |";
        }else{
            c+= "|";
        }
        c+= std::to_string(s[l].workload[3]);
        if(s[l].workload[3]<1000){
            c+= "  |";
        }else if(s[l].workload[3]<10000){
            c+= " |";
        }else{
            c+= "|";
        }
        int drain = s[i].workload[0]/pl.get_stats()[2]+s[i].workload[1]/pl.get_stats()[3]+s[i].workload[2]/pl.get_stats()[4]+s[i].workload[3]/pl.get_stats()[5];
        c+= std::to_string(drain);
        if(drain<100){
            c+= "     |";
        }else if(drain<1000){
            c+= "    |";
        }else{
            c+= "   |";
        }
        pl.add_life(-drain);
        drain_total += drain;
        if(drain<pl.get_life_f()/30){
            c+=" A |";
        }else if(drain<pl.get_life_f()/25*s[i].credit){
            c+=" B |";
        }else if(drain<pl.get_life_f()/20*s[i].credit){
            c+=" C |";
        }else if(drain<pl.get_life_f()/15*s[i].credit){
            c+=" D |";
        }else{
            c+=" F |";
        }

        std::string m = d.subjects[s[i].title];
        if(s[i].level == 2){
            m+=" II";
        }else if(s[i].level == 3){
            m+=" III";
        }else if(s[i].level == 4){
            m+=" IV";
        }
        c+=m;

    }
    c += "\n\n"+d.co_semester[1];
    gv.subject_num += (int)(rnd_r(5,8));
    if(gv.subject_num>=100){
        gv.subject_num = 100;
    }
    generate_subjects();
    print_update(c,d.bt_semester);
}

/* turn pass event for almost every action
*/
void gameManager::game_turn_pass(){
    // Gradually increase level
    gv.level *= 1.009;
    // Reset sugang time
    gv.s_time = gv.s_time_full;
    // player data update
    pl.stat_update();

    // Calculate semester
    if(gv.turn%40==39){
        calculate_semester();
    }
    // Game Over Check
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

/// Sugang

/* add people to sugang
*/
void gameManager::sugang_time_pass(double timepass){
    for(int i=0;i<gv.subject_num;i++){
        for(int j =0;j<timepass/2;j++){
            //Add people to each subjects
            int p = (int)(((s[i].attend_hope-s[i].attend_people)/16)*rnd_r(0.8,1.2));
            if(p==0 && rnd_d()>0.8){
                p++;
            }
            s[i].attend_people+=p;
        }
        // set no more over
        if(s[i].attend_people>s[i].attend_limit){
            s[i].attend_people=s[i].attend_limit;
        }
        // random empty seat
        if(s[i].attend_people==s[i].attend_limit){
            if(rnd_d()>0.95+0.05*(s[i].attend_hope-s[i].attend_limit)/s[i].attend_limit){
                s[i].attend_people-=1;
            }
        }
    }

}

/* Decrase sugang time
 */
void gameManager::sugang_time_decrease(double min, double max){
    double st = rnd_r(min,max);
    gv.s_time -= (int)(st);   // Decrease Time
    sugang_time_pass(st);
    print_sugang_apply(gv.gamestate-100);
}

/* apply subjects
 *
 */
void gameManager::sugang_apply(int index){
    // Apply
    bool AppDeapp = true;
    for(int i=0;i<SUBJECTS_MAX;i++){
        if(pl.get_subjects()[i] == index){
            pl.get_subjects()[i] = -1;
            s[index].attend_people--;
            AppDeapp = false;
        }
    }
    if(AppDeapp){
        bool apply = true;
        // check timetable
        for(int i=0;i<SUBJECTS_MAX;i++){
            if(pl.get_subjects()[i]==-1){
                continue;
            }
            for(int j=0;j<s[pl.get_subjects()[i]].credit;j++){
                for(int k=0;k<s[index].credit;k++){
                    if(s[pl.get_subjects()[i]].timetable[j]==s[index].timetable[k]){
                        apply = false;
                    }
                    if(!apply){
                        break;}
                }
                if(!apply){
                    break;}
            }
            if(!apply){
                break;}
        }

        // sugang hope people
        double success = 0;
        if(s[index].attend_hope<s[index].attend_limit){
            success = 1;
        }else{
            success = ((double)s[index].attend_limit/(double)s[index].attend_hope)*((double)s[index].attend_limit/(double)s[index].attend_hope);
        }
        if(rnd_d()>success){
            apply = false;
        }
        // sugang possible
        if(s[index].attend_people>=s[index].attend_limit){
            apply = false;
        }
        // message update and add sugang
        if(apply){
            for(int i = 0;i<SUBJECTS_MAX;i++){
                if(pl.get_subjects()[i]==-1){
                    pl.set_subjects(index,i);
                    break;
                }
            }
            s[index].attend_people++;
        }
    }
}


/// Print Functions

/* print sugang data
 * Printing subject datas
 */
void gameManager::print_sugang_data(){
    std::string c;
    c+=d.co_s_watch;
    c+="\n시간        수강희망/수강제한  분류    과목명";
    for (int i=0;i<gv.subject_num;i++){
        c+="\n";
        c+=print_subject_data(i,2);
    }
    print_update(c,d.bt_s_watch);
}

/* print sugang apply
 * Printing subject apply data
 */
void gameManager::print_sugang_apply(int index){
    //Console message - current time, applied subjects
    std::string c = d.co_s_apply[0];
    c+=std::to_string(gv.s_time/60)+":"+std::to_string(gv.s_time%60);
    c+=d.co_s_apply[1];
    c+="\n시간        수강인원/수강제한  분류    과목명";
    for (int i=0;i<SUBJECTS_MAX;i++){
        int p = pl.get_subjects()[i];
        // Continue if player's subject data is unavailable
        if (p<0){
            continue;}
        c+="\n";
        c+=print_subject_data(p,1);
    }
    //Button design - subject 1~7, next, out
    std::string k[9] = d.bt_s_apply;
    for (int i=0;i<7;i++){
        int p = (index-1)*7+i;
        // Disable button if there are no subject data
        if(p>=gv.subject_num){
            k[i] = "";
            continue;
        }
        std::string b;
        // Add Apply or deapply
        bool apply = false;
        for(int j=0;j<SUBJECTS_MAX;j++){
            if(pl.get_subjects()[j]==p){
                b+= "수강취소 ";
                apply = true;
                break;
            }
        }
        if(!apply){
            b+= "수강신청 ";
        }
        // Add data to button
        b+=print_subject_data(p,1);

        // Add text to button
        k[i] = b;
    }
    print_update(c,k);
}

/* print sugang data
 *
 */
std::string gameManager::print_subject_data(int i, int mode){
    std::string c;
    for(int j=0;j<s[i].credit;j++){
        c+=d.sb_day[s[i].timetable[j]/4]+d.sb_time[s[i].timetable[j]%4]+" ";}
    for(int j=s[i].credit;j<=2;j++){
        c+="　　　 ";}
    if(mode == 1){
        std::string tmp = std::to_string(s[i].attend_people)+" / "+std::to_string(s[i].attend_limit);
        c+=tmp;
        for(int i =tmp.length();i<=9;i++){
            c+=" ";
        }
    }
    else{
        std::string tmp = std::to_string(s[i].attend_hope)+" / "+std::to_string(s[i].attend_limit);
        c+=tmp;
        for(int i =tmp.length();i<=9;i++){
            c+=" ";
        }
    }
    c+=d.sb_category[s[i].category]+" ";
/*
    c+=std::to_string(s[i].workload[0])+" "+std::to_string(s[i].workload[1])+" ";
    c+=std::to_string(s[i].workload[2])+" "+std::to_string(s[i].workload[3])+" ";
    c+=std::to_string(s[i].workload[0]/pl.get_stats()[2]+s[i].workload[1]/pl.get_stats()[3]+s[i].workload[2]/pl.get_stats()[4]+s[i].workload[3]/pl.get_stats()[5])+" ";
*/
    // Subject name
    std::string m = d.subjects[s[i].title];
    if(s[i].level == 2){
        m+=" II";
    }else if(s[i].level == 3){
        m+=" III";
    }else if(s[i].level == 4){
        m+=" IV";
    }
    c+=m;
    return c;
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


/* generating subjects
 * depends on global level
 */
void gameManager::generate_subjects(){
    for(int i=0;i<gv.subject_num;i++){
        // set the category - if it is necessary, it is harder
        if(rnd_d()<0.35){
            s[i].category = 0;
        }else{
            s[i].category = 1;
        }
        // set the area of the subject - gives bonus burden
        // 1 - no special 2 - SCIE 3 - CODE 4 - LITE 5 - SOCI
        double die = rnd_d();
        if(die<0.2){s[i].area = 1;
        }else if(die<0.4){s[i].area = 2;
        }else if(die<0.6){s[i].area = 3;
        }else if(die<0.8){s[i].area = 4;
        }else{s[i].area = 5;}

        // set the level of the subject
        int year = (int)(gv.turn/40)+1;
        double rol = rnd_d();
        if(year == 1){
            if(rol<0.65){s[i].level = 1;}
            else if(rol<0.85){s[i].level=2;}
            else if(rol<0.95){s[i].level=3;}
            else            {s[i].level=4;}
        }else if(year == 2){
            if(rol<0.4){s[i].level = 1;}
            else if(rol<0.7){s[i].level=2;}
            else if(rol<0.9){s[i].level=3;}
            else            {s[i].level=4;}
        }else if(year == 3){
            if(rol<0.2){s[i].level = 1;}
            else if(rol<0.5){s[i].level=2;}
            else if(rol<0.8){s[i].level=3;}
            else            {s[i].level=4;}
        }else if(year == 4){
            if(rol<0.1){s[i].level = 1;}
            else if(rol<0.3){s[i].level=2;}
            else if(rol<0.6){s[i].level=3;}
            else            {s[i].level=4;}
        }else if(year == 5){
            if(rol>0.05){s[i].level = 1;}
            else if(rol>0.2){s[i].level=2;}
            else if(rol>0.5){s[i].level=3;}
            else            {s[i].level=4;}
        }else{
            if(rol<0.05){s[i].level = 1;}
            else if(rol<0.15){s[i].level=2;}
            else if(rol<0.35){s[i].level=3;}
            else            {s[i].level=4;}
        }

        // set the title of subjects
        s[i].title = (int)(rnd_d()*20+20*(s[i].area-1));

        // set the credit - amount of timetable
        s[i].credit = (int)(rnd_d()*3)+1;

        // set the timetables of subjects - based on credit
        int* a = rnd_ia(20,s[i].credit);
        for(int j=0;j<s[i].credit;j++){
            s[i].timetable[j] = a[j];
        }
        // set the attend limit - completely random bet 40~160, decrease with level
        s[i].attend_limit = (int)(rnd_r(40,160)/s[i].level);

        // set the basic workload - will effect on health deduction
        int basic_workload = 250*gv.level*((double)s[i].level/3+0.67);
        for(int j=0;j<4;j++){
            s[i].workload[j] = (int)(rnd_r(0.8,1.2)*basic_workload);
        }
        // add the area workload
        if(s[i].area>=2){
            s[i].workload[s[i].area-2] += (int)(rnd_r(1.0,3.0)*basic_workload);
        }
        // set the additional workload if it is necessary
        for(int j=0;j<4;j++){
            s[i].workload[j] *=rnd_r(1.2,1.5);
        }
        // set the additional workload if it has more timetable
        for(int j=0;j<s[i].credit;j++){
            s[i].workload[j] *=1.41;
        }

        // MAX WORKLOAD VALUE : basic*2.33*g.level*(1.2+3)*1.5 >
        // MIN WORKLOAD VALUE : basic*1*g.level*0.8 => 160

        // set the attend hope - necessary is harder to enroll
        if(s[i].category==0){
            s[i].attend_hope = (int)(s[i].attend_limit * (rnd_r(0.9,1.2)));
        }else{
            s[i].attend_hope = (int)(s[i].attend_limit * (rnd_r(0.5,1.7)));
        }
        // set the attended people = 0;
        s[i].attend_people = 0;
    }
}

#include "game.h"
#include "functions.h"
#include "player.h"

gameManager::gameManager(){
    this->turn = 32;
    this->subject_number = 40;
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
    switch(this->gamestate){
    case 0:
        this->gamestate ++;        // To Intro 2
        print_update(d.co_intro02,d.bt_intro);
        break;
    case 1:
        this->gamestate ++;        // To Intro 3
        print_update(d.co_intro03,d.bt_intro);
        break;
    case 2:
        this->gamestate ++;        // To Intro 4
        print_update(d.co_intro04,d.bt_intro);
        break;
    case 3:
        this->gamestate = 20;      // To Main
        print_update(d.co_main,d.bt_main);
        break;
    case 20:                                            // Main
        this->gamestate += input;
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
            meet_friend();this->gamestate = 31;break;       // To Meet Friend
        case 2:
            club_room();this->gamestate = 31;break;         // To Club Room
        case 3:
            visit_professor();this->gamestate = 31;break;   // To Visit Professor
        case 4:
            wander_around();this->gamestate = 31;break;     // To Wander around
        case 5:
            work();this->gamestate = 31;break;              // To Work
        case 9:
            this->gamestate = 20;print_update(d.co_main,d.bt_main);break; // Back to Main
        default: break;
        }
        break;
    case 22:                                            // Sugang
        switch(input){
        case 1:                                             // To Login
            if((this->turn/4)%10<=7){                       // Back to Main if Day<8
                this->gamestate = 20;
                print_update(d.co_main, d.bt_main);
            }
            else{                                           // Login Successful
                this->gamestate = 101;
                print_sugang_apply(this->gamestate - 100);
            }
            break;
        case 2:                                             // View Sugang Data
            this->gamestate = 100;
            print_sugang_data();
            break;
        case 9:                                             // Back To Main
            this->gamestate = 20;
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 23:                                                // Store (Not Available)
        //print_update(d.co_store,d.bt_store);
        this->gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
                                                        // Sugang Login
    case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115:
        switch(input){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            sugang_apply((this->gamestate-101)*7+input-1);  // Apply to subject
            this->sugang_time -= (int)(rnd_r(10.0,13.0));   // Decrease Time
            sugang_time_decrease(10.0,13.0);
            print_sugang_apply(this->gamestate-100);
            if(this->sugang_time <= 0){
                this->sugang_time = this->sugang_time_full;
                this->gamestate = 20;
                game_turn_pass();
                print_update(d.co_main,d.bt_main);
            }
            break;
        case 8:                                             // View Next Subject
            if(this->gamestate >= (100 + this->subject_number/7 + 1)){
                this->gamestate = 100;
            }
            this->gamestate += 1;
            sugang_time_decrease(1.0,3.0);
            if(this->sugang_time <= 0){
                this->sugang_time = this->sugang_time_full;
                this->gamestate = 20;
                game_turn_pass();
                print_update(d.co_main,d.bt_main);
            }
            break;
        case 9:
            this->gamestate = 20;                           // To Main Menu, spend turn
            game_turn_pass();
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 44:
        break;
    case 24: case 25: case 26: case 27:case 31: case 100:   // Default Cases
    default:
        this->gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    }
}

/* turn pass event for almost every action
*/
void gameManager::game_turn_pass(){
    this->turn ++;
    this->level *= 1.009;
    pl.set_life_f(pl.get_stats()[0]*100+1000);

    // Game Over Check
    if(pl.get_life()<=0){
        pl.set_life(0);
        this->gamestate = 44;
        std::string c="";
        for(int i=0;i<6;i++){
            c+=d.co_gameover[i];}
        print_update(c,d.bt_gameover);
    }
}

/// Sugang

/* add people to sugang
*/
void gameManager::sugang_time_pass(double timepass){
    for(int i=0;i<this->subject_number;i++){
        s[i].attend_people+=(int)(timepass);


        if(s[i].attend_people>s[i].attend_limit){
            s[i].attend_people=s[i].attend_limit;
        }
    }

}

/* Decrase sugang time
 */
void gameManager::sugang_time_decrease(double min, double max){
    double st = rnd_r(min,max);
    this->sugang_time -= (int)(st);   // Decrease Time
    sugang_time_pass(st);
    print_sugang_apply(this->gamestate-100);
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
    c+="\n과목명\t\t\t시간\t수강희망/수강제한  분류";
    for (int i=0;i<subject_number;i++){
        c+="\n";
        c+=print_subject_data_hope(i);
        c+=d.sb_category[s[i].category];
    }
    print_update(c,d.bt_s_watch);
}

/* print sugang apply
 * Printing subject apply data
 */
void gameManager::print_sugang_apply(int index){
    //Console message - current time, applied subjects
    std::string c = d.co_s_apply[0];
    c+=std::to_string(this->sugang_time/60)+":"+std::to_string(this->sugang_time%60);
    c+=d.co_s_apply[1];
    c+="\n과목명\t\t\t시간\t수강인원/수강제한  분류";
    for (int i=0;i<SUBJECTS_MAX;i++){
        int p = pl.get_subjects()[i];
        // Continue if player's subject data is unavailable
        if (p<0){
            continue;}
        c+="\n";
        c+=print_subject_data_people(p);
        c+=d.sb_category[s[p].category];
    }
    //Button design - subject 1~7, next, out
    std::string k[9] = d.bt_s_apply;
    for (int i=0;i<7;i++){
        int p = (index-1)*7+i;
        // Disable button if there are no subject data
        if(p>=this->subject_number){
            k[i] = "";
            continue;
        }
        std::string b;
        // Add data to button
        b+=print_subject_data_people(p);
        b+=d.sb_category[s[p].category];
        // Add Apply or deapply
        bool apply = false;
        for(int j=0;j<SUBJECTS_MAX;j++){
            if(pl.get_subjects()[j]==p){
                b+= " 수강취소";
                apply = true;
                break;
            }
        }
        if(!apply){
            b+= " 수강신청";
        }
        // Add text to button
        k[i] = b;
    }
    print_update(c,k);
}

/* print sugang data
 *
 */
std::string gameManager::print_subject_data_people(int i){
    std::string c;
    std::string m = s[i].title;
    c+=s[i].title;
    for(int i=m.length();i<45;i++){
        c+=" ";}
    c+="\t";
    for(int j=0;j<s[i].credit;j++){
        c+=d.sb_day[s[i].timetable[j]/4]+d.sb_time[s[i].timetable[j]%4]+" ";}
    for(int j=s[i].credit;j<=2;j++){
        c+="　　　 ";}
    std::string tmp = std::to_string(s[i].attend_people)+"/"+std::to_string(s[i].attend_limit);
    c+=tmp;
    for(int i = tmp.length(); i < 10; i++){
        c+=" ";}
    return c;
}

/* print sugang data
 *
 */
std::string gameManager::print_subject_data_hope(int i){
    std::string c;
    std::string m = s[i].title;
    c+=s[i].title;
    for(int i=m.length();i<45;i++){
        c+=" ";}
    c+="\t";
    for(int j=0;j<s[i].credit;j++){
        c+=d.sb_day[s[i].timetable[j]/4]+d.sb_time[s[i].timetable[j]%4]+" ";}
    for(int j=s[i].credit;j<=2;j++){
        c+="　　　 ";}
    std::string tmp = std::to_string(s[i].attend_hope)+"/"+std::to_string(s[i].attend_limit);
    c+=tmp;
    for(int i = tmp.length(); i < 10; i++){
        c+=" ";}
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


/// Actions that deplete turn

/* main - outside - meet friend
 * 70% get subject information
 * 10% ~~
*/
void gameManager::meet_friend(){
    int act = (int)(rnd_r(0,100));
    //Console string initialize
    std::string co ="";

    switch(act){
    case 1: case 2: case 3:
        pl.add_life(-this->level*700*(rnd_d()/4+7/8));
        pl.add_money(-this->level*20000*(rnd_d()/2+0.75));
        co += d.co_meet_friend[act];
        break;
    case 4: case 5: case 6:
    case 7: case 8: case 9:
        break;
    }
    print_update(co,d.co_meet_friend);
}

/* main - rest
 * decrease health
 * add money
*/
void gameManager::work(){
    // Decrease health
    int l = (int)(-this->level*200*(rnd_r(0.75,1.25)));
    pl.add_life(l);
    // Increase money (round up by 100)
    int m = (int)(+this->level*500*(rnd_r(0.75,1.25)))*100;
    pl.add_money(m);
    // Update console and button message
    std::string co ="";
    co += d.co_work;
    co += "\n";
    co += "\n"+d.msg_money+std::to_string(m)+d.msg_add;
    co += "\n"+d.msg_life+std::to_string(-l)+d.msg_sub;
    print_update(co,d.bt_work);
    // End turn
    game_turn_pass();
}

/* main - rest
 * increase health
*/
void gameManager::rest(){
    // update console message and button message
    print_update(d.co_rest,d.bt_rest);
    // Add Health
    pl.add_life((int)(pl.get_stats()[1]*100*rnd_r(0.9,1.2)));
    // End turn
    game_turn_pass();
}

/* main - study
 * increase random study stat
 * lose helath
*/
void gameManager::study(){    
    // Lose Health
    int l = (int)(-this->level*150*rnd_r(0.75,1.25));
    pl.add_life(l);
    // Increasement value
    int s = (int)(rnd_r(1,3));
    // Choose random study stat
    int w = (int)(rnd_r(2,6));
    pl.add_stats(s,w);
    // Print console message and button
    std::string co ="";
    co += d.co_study[(int)(rnd_d()*5)];
    co += "\n";
    co += "\n"+d.msg_stats[w]+std::to_string(s)+d.msg_add;
    co += "\n"+d.msg_life+std::to_string(-l)+d.msg_sub;
    print_update(co,d.bt_study);
    // End turn
    game_turn_pass();
}

/* main - exercise
 * increase health stat and recovery stat
 * lose helath
*/
void gameManager::exercise(){
    // Lose Health
    int l = (int)(-this->level*200*rnd_r(0.75,1.25));
    pl.add_life(l);
    // Increase Maximum health
    int s1 = (int)(rnd_r(2,4));
    pl.add_stats(s1,0);
    // Increase Recovery
    int s2 = (int)(rnd_r(1,3));
    pl.add_stats(s2,1);
    // Print console message and button
    std::string co ="";
    co += d.co_exercise[(int)(rnd_d()*5)];
    co += "\n";
    co += "\n"+d.msg_stats[0]+std::to_string(s1)+d.msg_add;
    co += "\n"+d.msg_stats[1]+std::to_string(s2)+d.msg_add;
    co += "\n"+d.msg_life+std::to_string(-l)+d.msg_sub;
    print_update(co,d.bt_exercise);
    // End turn
    game_turn_pass();
}

void gameManager::store(){};
void gameManager::visit_professor(){};
void gameManager::club_room(){};
void gameManager::wander_around(){};

void gameManager::sugang(){};
void gameManager::calculate_semester(){};

/* generating subjects
 * depends on global level
 */
void gameManager::generate_subjects(){
    for(int i=0;i<subject_number;i++){
        // set the category
        if(i<subject_number/3){
            s[i].category = 0;}
        else{
            s[i].category = 1;}

        double rol = rnd_d();

        if(rol>0.5){
            s[i].level = 1;}
        else if(rol>0.3){
            s[i].level = 2;}
        else if(rol>0.1){
            s[i].level = 3;}
        else if(rol>0.0){
            s[i].level = 4;}

        // set the title of subjects
        /// set the basic name
        s[i].title = d.subjects[(int)(rnd_d()*100)];
        /// add I or II
        if(s[i].level == 2){
            s[i].title += " II";
        }
        if(s[i].level == 3){
            s[i].title += " III";
        }
        if(s[i].level == 4){
            s[i].title += " IV";
        }
        if(s[i].level == 5){
            s[i].title += " V";
        }
        // set the credit - amount of timetable
        s[i].credit = (int)(rnd_d()*3)+1;

        // set the timetables of subjects - based on credit
        /// Pick the each subject - not perfect since there might be same class - need to be fixed
        int* a = rnd_ia(20,s[i].credit);

        for(int j=0;j<s[i].credit;j++){
            s[i].timetable[j] = a[j];
        }
        // set the attend limit - completely random bet 20~100
        s[i].attend_limit = (int)(rnd_d()*80+20);
        // set the workload - will effect on health deduction
        int basic_workload = 1500;

        for(int j=0;j<4;j++){
            s[i].workload[j] = (int)(rnd_d()*basic_workload*this->level);
        }
        s[i].attend_hope = (int)(s[i].attend_limit * (rnd_d()*0.4+0.85));
    }
}

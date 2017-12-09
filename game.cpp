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

}

// gamestate
// 0~19 : intro
// 20 : Main Turn
// 21 : Go outside
// 22 : Connect Internet
// 23 : Store
// 24 : Rest at home

void gameManager::proceed(int input){
    switch(this->gamestate){
    case 0:
        this->gamestate ++;
        print_update(d.co_intro02,d.bt_intro);
        break;
    case 1:
        this->gamestate ++;
        print_update(d.co_intro03,d.bt_intro);
        break;
    case 2:
        this->gamestate ++;
        print_update(d.co_intro04,d.bt_intro);
        break;
    case 3:
        this->gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    case 20:
        this->gamestate += input;
        switch(input){
        case 1:
            print_update(d.co_outside,d.bt_outside);break;
        case 2:
            print_update(d.co_sugang,d.bt_sugang);break;
        case 3:
            print_update(d.co_store,d.bt_store);break;
        case 4:
            rest();break;
        case 5:
            study();break;
        default:
            break;
        }
        break;
    case 21:
        switch(input){
        case 1:
            meet_friend();
            this->gamestate = 31;
            break;
        case 2:
            club_room();
            this->gamestate = 31;
            break;
        case 3:
            visit_professor();
            this->gamestate = 31;
            break;
        case 4:
            wander_around();
            this->gamestate = 31;
            break;
        case 5:
            work();
            this->gamestate = 31;
            break;
        case 9:
            this->gamestate = 20;
            print_update(d.co_main,d.bt_main);
            break;
        default:
            break;
        }
        break;
    case 22:
        switch(input){
        case 1:
            //수강신청
            if((this->turn/4)%10<=7){
                this->gamestate = 20;
                print_update(d.co_main, d.bt_main);
            }
            else{
                this->gamestate = 101;
                print_sugang_apply(this->gamestate - 100);
            }
            break;
        case 2:
            this->gamestate = 100;
            print_sugang_data();
            break;
        case 9:
            this->gamestate = 20;
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 23:
        print_update(d.co_store,d.bt_store);
        break;
    case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110: case 111: case 112:
        switch(input){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            // Apply to subject
            break;
        case 8:
            // To Next Menu
            if(this->gamestate == 100 + this->subject_number/7 + 1){
                this->gamestate = 100;
            }
            this->gamestate += 1;
            print_sugang_apply(this->gamestate-100);
            break;
        case 9:
            // To Main Menu, spend turn
            this->gamestate = 20;
            game_turn_pass();
            print_update(d.co_main,d.bt_main);
            break;
        }
        break;
    case 24: case 25: case 31: case 100:
    default:
        this->gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    }
}

void gameManager::print_update(std::string co, std::string* bt){
    this->console = co;
    for(int i=0;i<BUTTON_LENGTH;i++){this->button[i]=bt[i];}
    if(co==""){
        this->console = "ERROR";
        for(int i=0;i<9;i++){this->button[i]="";}
    }
    //Debuging Mode
    this->console += "\n\n"+std::to_string(gamestate);
    /*
    for (int i=0;i<subject_number;i++){
        this->console += "\nT:"+std::to_string(s[i].timetable[0])+" "+std::to_string(s[i].timetable[1])+" "+std::to_string(s[i].timetable[2]);
        this->console += " L: "+std::to_string(s[i].attend_limit);
        this->console += " C: "+std::to_string(s[i].category);
        this->console += " W:";
        for(int j=0;j<6;j++){
            this->console += " "+std::to_string(s[i].workload[j]);
        }
        this->console += " N:"+s[i].title+" C:"+std::to_string(s[i].credit);

    }*/
}
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
        s[i].attend_hope = (int)(s[i].attend_limit * (rnd_d()*0.4+0.8));
    }
}

void gameManager::print_sugang_data(){
    std::string c;
    c+=d.co_s_watch;
    c+="\n과목명\t\t\t시간\t수강희망/수강제한  분류";

    for (int i=0;i<subject_number;i++){
        c+="\n";
        c+=print_subject_data(i);
        c+=d.sb_category[s[i].category];
    }
    print_update(c,d.bt_s_watch);
}

std::string gameManager::print_subject_data(int i){
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

void gameManager::print_sugang_apply(int index){
    //Console message - current time, applied subjects
    std::string c = d.co_s_apply[0];
    c+=std::to_string(this->sugang_time/60)+":"+std::to_string(this->sugang_time%60);
    c+=d.co_s_apply[1];
    for (int i=0;i<SUBJECTS_MAX;i++){
        int p = pl.get_subjects()[i];
        // Continue if player's subject data is unavailable
        if (p<0){
            continue;}
        c+="\n";
        c+=print_subject_data(p);
        c+=d.sb_category[s[p].category];
    }
    //Button design - subject 1~7, next, out
    std::string k[9] = d.bt_s_apply;
    for (int i=0;i<7;i++){
        int p = index*6+i;
        std::string b;
        // Add data to button
        b+=print_subject_data(p);
        b+=d.sb_category[s[p].category];
        // Add Apply or deapply
        bool apply = false;
        for(int j=0;j<SUBJECTS_MAX;j++)
        {
            if(pl.get_subjects()[j]==p){
                b+= " 수강취소";
                apply = true;
                break;
            }
        }
        if(!apply){
            b+= " 수강신청";
        }

        k[i] = b;
    }
    print_update(c,k);
}

void gameManager::game_turn_pass(){
    this->turn ++;
    this->level *= 1.009;
    pl.set_life_f(pl.get_stats()[0]*100+1000);
}

void gameManager::meet_friend(){
    int action = 5;
    int act = (int)(rnd_d()*action);
    //Basic string
    std::string co ="";
    co += d.co_meet_friend[act];

    switch(act){
    case 1:
        pl.add_life(-this->level*700*(rnd_d()/4+7/8));
        pl.add_money(-this->level*20000*(rnd_d()/2+0.75));
        break;
    case 2:
        //수강신청 내용을 공개
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    default:

        break;
    }
    print_update(co,d.co_meet_friend);
}
void gameManager::work(){
    std::string co ="";
    co += d.co_work;
    int l = (int)(-this->level*200*(rnd_d()/2+0.75));
    pl.add_life(l);
    int m = (int)(+this->level*50000*(rnd_d()/2+0.75));
    pl.add_money(m);
    co += "\n";
    co += "\n"+d.msg_money+std::to_string(m)+d.msg_add;
    co += "\n"+d.msg_life+std::to_string(-l)+d.msg_sub;
    print_update(co,d.bt_work);
}

void gameManager::rest(){
    print_update(d.co_rest,d.bt_rest);
    pl.add_life((int)(pl.get_stats()[1]*100*(rnd_d()/2+0.75)));
    game_turn_pass();
}

void gameManager::study(){
    std::string co ="";
    co += d.co_study[(int)(rnd_d()*5)];
    int l = (int)(-this->level*150*(rnd_d()/2+0.75));
    int s = (int)(rnd_d()*1.5+1);
    int w = (int)(rnd_d()*6);
    pl.add_life(l);
    pl.add_stats(s,w);
    co += "\n";
    co += "\n"+d.msg_stats[w]+std::to_string(s)+d.msg_add;
    co += "\n"+d.msg_life+std::to_string(-l)+d.msg_sub;
    print_update(co,d.bt_study);
    game_turn_pass();
}

void gameManager::store(){};
void gameManager::visit_professor(){};
void gameManager::club_room(){};
void gameManager::wander_around(){};

void gameManager::sugang(){};
void gameManager::calculate_semester(){};
void gameManager::game_over(){};

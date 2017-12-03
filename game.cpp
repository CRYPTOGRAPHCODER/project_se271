#include "game.h"

gameManager::gameManager(){

    this->turn = 0;
    generate_subjects();
    for(int i=0;i<BUTTON_LENGTH;i++){
        this->button[i]="";
    }
    print_update(d.co_intro01,d.bt_intro);
}
static std::random_device rd;
static std::mt19937 rng(rd());

double gameManager::rnd_d(){
   std::uniform_real_distribution<double> rand(0.0, 1.0);
   return rand(rng);
}
int* gameManager::rnd_ia(int lim, int coun) {
   int* rnd_a = new int[coun];
   for (int t = 0; t < coun; t++) { rnd_a[t] = 0; };
   for (int i = 0; i < coun; i++) {
      rnd_a[i] = (int)(rnd_d()*lim);
      for (int k = 0; k < i; k++) {
         if (rnd_a[k] == rnd_a[i]) {
            rnd_a[i] = 0;
            i--;
            break;
         }
      }
   }
   return rnd_a;
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
            print_update(d.co_internet,d.bt_internet);break;
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
            this->gamestate = 31;
            print_update(d.co_main,d.bt_main);
            break;
        default:
            break;
        }
        break;
    case 22:
        print_update(d.co_internet,d.bt_internet);
        break;
    case 23:
        print_update(d.co_store,d.bt_store);
        break;
    case 24:
        this->gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    case 25:
        this->gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    case 31:
        this->gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    default:
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
    for (int i=0;i<MAX_SUBJECT;i++){
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
    for(int i=0;i<MAX_SUBJECT;i++){
        // set the category
        if(i<MAX_SUBJECT/3){
            s[i].category = 0;}
        else{
            s[i].category = 1;}

        // set the title of subjects
        /// set the basic name
        s[i].title = d.subjects[(int)(rnd_d()*100)];
        /// add I or II
        if(rnd_d()>0.7){
            s[i].title += " II";
        }
        else if (rnd_d()>0.9){
            s[i].title += " III";
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
        for(int j=0;j<4;j++){
            s[i].workload[j] = (int)(rnd_d()*1500*this->level);
        }

    }
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

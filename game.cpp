#include "game.h"

gameManager::gameManager(){

    this->turn = 0;
    generate_subjects(0);
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
int* get_ia(int lim, int coun) {
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
            print_update(d.co_rest,d.bt_rest);break;
        default:
            break;
        }
        break;
    case 21:
        switch(input){
        case 1:
            meet_friend();
            this->gamestate = 25;
            break;
        case 2:
            club_room();
            this->gamestate = 25;
            break;
        case 3:
            this->gamestate = 25;
            visit_professor();
            break;
        case 4:
            this->gamestate = 25;
            wander_around();
            break;
        case 5:
            this->gamestate = 25;
            work();
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
        print_update(d.co_internet,d.bt_internet);
        break;
    case 23:
        print_update(d.co_store,d.bt_store);
        break;
    case 24:
        rest();
        this->gamestate = 20;
        print_update(d.co_main,d.bt_main);
        break;
    case 25:
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
void gameManager::generate_subjects(double level){
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
        s[i].timetable = rnd_ia(20,s[i].credit);

        // set the attend limit - completely random bet 20~100
        s[i].attend_limit = (int)(rnd_d()*80+20);

        // set the workload - will effect on health deduction
        for(int j=0;j<4;j++){
            s[i].workload[j] = (int)(rnd_d()*2000);
        }

    }
}

void gameManager::game_turn_pass(){
    this->turn ++;
    this->level *= 1.01;
}

void gameManager::rest(){
    pl.add_life(pl.get_stats()[1]*100);
    game_turn_pass();
}

void gameManager::meet_friend(){
    action = 5;
    act = (int)(rnd_d()*action);
    //Basic string
    std::string co ="";
    co += d.co_meet_friend[act];

    switch(act){
    case 1:
        pl.add_life(-this->level*70*(rnd_d()/2+0.75));
        pl.add_money(-this->level*2000*(rnd_d()/2+0.75));
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



void gameManager::store(){};
void gameManager::visit_professor(){};
void gameManager::club_room(){};
void gameManager::wander_around(){};
void gameManager::work(){};
void gameManager::sugang(){};
void gameManager::calculate_semester(){};
void gameManager::game_over(){};

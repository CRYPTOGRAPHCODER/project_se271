#include "player.h"
player::player(){
  this->name = "Waldo";
  //stats : life / recov / science / code / literature / social
  for (int i = 0; i < STATS; i++){
        this->stats[i] = 5;}
  for (int i = 0; i < ITEMS_MAX; i++){
    this->items[i] = 0;}
  for (int i = 0; i < SUBJECTS_MAX; i++){
    this->subjects[i] = -1;}
  this->money = 0;

  this->credit_acquired_ess = 0;
  this->credit_required_ess = 24;
  this->credit_acquired_chs = 0;
  this->credit_required_chs = 36;

  this->score = 0;
  stat_update();
  this->life = this->life_f;
}
player::~player(){
    /*
    delete[] this->stats;
    delete[] this->equipments;
    delete[] this->subjects;*/
}

void player::stat_update(){
    this->life_f = 1000 + stats[0]*50+stats[1]*10;
    if(this->life>this->life_f){
        this->life = this->life_f;
    }
    /*
    this->life_f=1000;
    for(int i =0;i<this->stats[0];i++){
        this->life_f = (int)(this->life_f*1.02);
    }*/

}

bool player::item_check(int index){
    for(int i =0;i < ITEMS_MAX;i++){
        if(this->items[i] == index){
            return true;
        }
    }
    return false;
}

void player::item_delete_find(int index){
    for(int i =0;i < ITEMS_MAX;i++){
        if(this->items[i] == index){
            this->items[i] = 0;
        }
    }
}

void player::item_add(int index){
    bool item = false;
    //instant item effect
    if(index<11){
        switch(index){
        case 1:
            life += 200;
            break;
        case 2:
            life += 1000;
            break;
        case 3:
            life +=(int)(life_f*0.5);
            break;
        case 4:
            life = life_f;
            break;
        case 5:
            stats[0]++;
            break;
        case 6:
            stats[1]++;
            break;
        case 7:
            stats[2]++;
            break;
        case 8:
            stats[3]++;
            break;
        case 9:
            stats[4]++;
            break;
        case 10:
            stats[5]++;
            break;
        }
    }
    else{
        for(int i =0;i < ITEMS_MAX;i++){
            if(this->items[i] == 0){
                this->items[i] = index;
                item = true;
            }
            if(item){
                break;
            }
        }
    }
}
void player::add_score_turn(int turn, double gl){
    for(int i=0;i<6;i++){
        score+=(int)(stats[i]*gl*10);
    }
    score+=(int)(money/1000);
    score+=(int)(life/life_f*gl*1000);
    score+=(int)(100+turn*10);
}

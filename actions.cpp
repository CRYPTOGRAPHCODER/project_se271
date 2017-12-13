#include "game.h"
#include "functions.h"

/// Actions that deplete turn

/* main - outside - meet friend
 * 70% get subject information
 * 10% ~~
*/

void gameManager::meet_friend(){
  //life는 일괄적으로 50곱해줄 것, 돈은 일괄적으로 2000 곱해줄 것
    int act = (int)(rnd_r(0,100));
    //Basic string
    std::string co ="";
    int d1 = (int)(2000*rnd_r(2.0, 4.0)*gv.level);
    co += "\n" + d.msg_money + std::to_string(d1) + d.msg_sub;
    co+=d.co_meet_friend[0];
    pl.add_money(-d1);
}


/* main - work
 * decrease health
 * add money
*/
void gameManager::work(){
    // Decrease health
    int l = (int)(-gv.level*200*(rnd_r(0.75,1.25)));
    pl.add_life(l);
    // Increase money (round up by 100)
    int m = (int)(+gv.level*500*(rnd_r(0.75,1.25)))*100;
    pl.add_money(m);
    // Update console and button message
    std::string co ="";
    co += d.co_work;
    co += "\n";
    co += "\n"+d.msg_money+std::to_string(m)+d.msg_add;
    co += "\n"+d.msg_life+std::to_string(-l)+d.msg_sub;
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

/* main - rest
 * increase health
*/
void gameManager::rest(){
    // update console message and button message
    print_update(d.co_rest,d.bt_basic);
    // Add Health
    int add = (int)(((15+pl.get_stats()[1])*rnd_r(0.9,1.2))/100*pl.get_life_f());
    // Item 3
    if(pl.item_check(3)){
        add*=1.3;
    }
    pl.add_life(add);
    // End turn
    game_turn_pass();
}

/* main - study
 * increase random study stat
 * lose helath
*/
void gameManager::study(){
    // Lose Health
    int l = (int)(-gv.level*150*rnd_r(0.75,1.25));
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
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

/* main - exercise
 * increase health stat and recovery stat
 * lose helath
*/
void gameManager::exercise(){
    // Lose Health
    int l = (int)(-gv.level*200*rnd_r(0.75,1.25));
    pl.add_life(l);
    // Increase Maximum health
    int s1 = (int)(rnd_r(2,4));
    pl.add_stats(s1,0);
    // Increase Recovery
    int s2 = (int)(rnd_r(0.3,2.1));
    pl.add_stats(s2,1);
    // Print console message and button
    std::string co ="";
    co += d.co_exercise[(int)(rnd_d()*5)];
    co += "\n";
    co += "\n"+d.msg_stats[0]+std::to_string(s1)+d.msg_add;
    co += "\n"+d.msg_stats[1]+std::to_string(s2)+d.msg_add;
    co += "\n"+d.msg_life+std::to_string(-l)+d.msg_sub;
    print_update(co,d.bt_basic);
    // End turn
    game_turn_pass();
}

void gameManager::store(){};
void gameManager::visit_professor(){};
void gameManager::club_room(){};

void gameManager::wander_around(){
    int act = rnd_r(0,100);
    //Console string initialize
    std::string co ="";

    if(act<5){          // 멍 때리기 - STAT--
        int d1 = (int)(rnd_r(0.5,3)*gv.level);
        pl.add_stats(-d1,2);
        int d2 = (int)(rnd_r(0.5,3)*gv.level);
        pl.add_stats(-d2,3);
        int d3 = (int)(rnd_r(0.5,3)*gv.level);
        pl.add_stats(-d3,4);
        int d4 = (int)(rnd_r(0.5,3)*gv.level);
        pl.add_stats(-d4,5);
        co+=d.co_wander_around[0];
        co+="\n";
        co+="\n"+d.msg_stats[2]+std::to_string(d1)+d.msg_sub;
        co+="\n"+d.msg_stats[3]+std::to_string(d2)+d.msg_sub;
        co+="\n"+d.msg_stats[4]+std::to_string(d3)+d.msg_sub;
        co+="\n"+d.msg_stats[5]+std::to_string(d4)+d.msg_sub;
    }else if(act<9){    // 달리기 선수 - HPST++ HP--;
        int d1 = (int)(rnd_r(2,4)*gv.level);
        pl.add_stats(d1,0);
        int d2 = (int)(rnd_r(0.8,1.2)*d1*100);
        pl.add_life(-d2);
        co+=d.co_wander_around[1];
        co+="\n";
        co+="\n"+d.msg_stats[0]+std::to_string(d1)+d.msg_add;
        co+="\n"+d.msg_life+std::to_string(d2)+d.msg_sub;
    }else if(act<13){   // 전력 질주 - HP--
        int d1 = (int)(rnd_r(0.8,1.2)*300*gv.level);
        pl.add_life(-d1);
        co+=d.co_wander_around[2];
        co+="\n";
        co+="\n"+d.msg_life+std::to_string(d1)+d.msg_sub;
    }else if(act<17){   // 사소한 충돌 - No change
        co+=d.co_wander_around[3];
    }else if(act<21){   // 사소한 충돌 - $+
        int d1 = (int)(rnd_r(0.8,1.2)*100*gv.level*100);
        pl.add_money(d1);
        co+=d.co_wander_around[4];
        co+="\n";
        co+="\n"+d.msg_money+std::to_string(d1)+d.msg_add;
    }else if(act<25){   // 사소한 충돌 - HP---, RECO-
        int d1 = (int)(rnd_r(1,3)*gv.level);
        pl.add_stats(-d1,1);
        int d2 = (int)(rnd_r(4,7)*100*gv.level);
        pl.add_life(-d2);
        co+=d.co_wander_around[5];
        co+="\n";
        co+="\n"+d.msg_stats[0]+std::to_string(d1)+d.msg_sub;
        co+="\n"+d.msg_life+std::to_string(d2)+d.msg_sub;
    }else if(act<30){   // 책의 힘 - LITE++
        int d1 = (int)(rnd_r(2,5)*gv.level);
        pl.add_stats(d1,4);
        co+=d.co_wander_around[6];
        co+="\n";
        co+="\n"+d.msg_stats[4]+std::to_string(d1)+d.msg_add;
    }else if(act<35){   // 책의 힘 - SCIN+ CODE+
        int d1 = (int)(rnd_r(2,3)*gv.level);
        pl.add_stats(d1,2);
        int d2 = (int)(rnd_r(2,3)*gv.level);
        pl.add_stats(d2,3);
        co+=d.co_wander_around[7];
        co+="\n";
        co+="\n"+d.msg_stats[2]+std::to_string(d1)+d.msg_add;
        co+="\n"+d.msg_stats[3]+std::to_string(d2)+d.msg_add;
    }else if(act<40){   // 책의 힘 - No change
        co+=d.co_wander_around[8];
    }else if(act<43){   // 친구의 선물 - Add Item
        co+=d.co_wander_around[9];

    }else if(act<46){   // 친구의 선물 - No change
        co+=d.co_wander_around[10];
    }else if(act<48){   // 도플갱어 - HP-
        int d1 = (int)(rnd_r(4,7)*100*gv.level);
        pl.add_life(-d1);
        co+=d.co_wander_around[11];
        co+="\n";
        co+="\n"+d.msg_life+std::to_string(d1)+d.msg_sub;
    }else if(act<50){   // 도플갱어 all stat**
        co+=d.co_wander_around[12];
        co+="\n";
        for(int j=0;j<6;j++){
            pl.add_stats(pl.get_stats()[j],j);
            co+="\n"+d.msg_stats[j]+std::to_string(pl.get_stats()[j]/2)+d.msg_add;
        }
    }else if(act<55){   // 소매치기 money---
        int d1 = (int)(rnd_r(0.8,1.2)*1000*gv.level*100);
        pl.add_money(-d1);
        co+=d.co_wander_around[13];
        co+="\n";
        co+="\n"+d.msg_money+std::to_string(d1)+d.msg_sub;
    }else if(act<58){   // 강도 item -
        co+=d.co_wander_around[14];

    }else if(act<63){   // 오늘은 내가 요리사 HPST+ RECO+ HP+
        int d1 = (int)(rnd_r(2,4)*gv.level);
        pl.add_stats(d1,0);
        int d2 = (int)(rnd_r(0.5,1.7)*gv.level);
        pl.add_stats(d2,1);
        int d3 = (int)(rnd_r(200,400)*gv.level);
        pl.add_life(d3);
        co+=d.co_wander_around[15];
        co+="\n";
        co+="\n"+d.msg_stats[0]+std::to_string(d1)+d.msg_add;
        co+="\n"+d.msg_stats[1]+std::to_string(d2)+d.msg_add;
        co+="\n"+d.msg_life+std::to_string(d3)+d.msg_add;
    }else if(act<68){   // 오늘은 내가 요리사 HPST- RECO- HP-
        int d1 = (int)(rnd_r(1,3)*gv.level);
        pl.add_stats(-d1,0);
        int d2 = (int)(rnd_r(0,2)*gv.level);
        pl.add_stats(-d2,1);
        int d3 = (int)(rnd_r(100,200)*gv.level);
        pl.add_life(-d3);
        co+=d.co_wander_around[16];
        co+="\n";
        co+="\n"+d.msg_stats[0]+std::to_string(d1)+d.msg_sub;
        co+="\n"+d.msg_stats[1]+std::to_string(d2)+d.msg_sub;
        co+="\n"+d.msg_life+std::to_string(d3)+d.msg_sub;
    }else if(act<73){   // 친구의 질문   SCIE+ CODE+
        int d1 = (int)(rnd_r(2,4)*gv.level);
        pl.add_stats(d1,2);
        int d2 = (int)(rnd_r(2,4)*gv.level);
        pl.add_stats(d2,3);
        co+=d.co_wander_around[17];
        co+="\n";
        co+="\n"+d.msg_stats[2]+std::to_string(d1)+d.msg_add;
        co+="\n"+d.msg_stats[3]+std::to_string(d2)+d.msg_add;
    }else if(act<78){   // 친구의 질문 Nothing
        co+=d.co_wander_around[18];
    }else if(act<82){   // 실험 조언 SCIE- CODE-
        int d1 = (int)(rnd_r(1,3)*gv.level);
        pl.add_stats(-d1,2);
        int d2 = (int)(rnd_r(1,3)*gv.level);
        pl.add_stats(-d2,3);
        co+=d.co_wander_around[19];
        co+="\n";
        co+="\n"+d.msg_stats[2]+std::to_string(d1)+d.msg_sub;
        co+="\n"+d.msg_stats[3]+std::to_string(d2)+d.msg_sub;
    }else if(act<87){   // 목적 없는 사람 Nothing
        co+=d.co_wander_around[20];
    }else if(act<90){   // 특강 ITEM+
        co+=d.co_wander_around[21];

    }else if(act<95){   // 특강 HP+
        int d3 = (int)(rnd_r(200,400)*gv.level);
        pl.add_life(d3);
        co+=d.co_wander_around[22];
        co+="\n";
        co+="\n"+d.msg_life+std::to_string(d3)+d.msg_add;
    }else{              // 의미 없는 토론
        int d1 = (int)(rnd_r(1,3)*gv.level);
        pl.add_stats(-d1,4);
        int d2 = (int)(rnd_r(1,3)*gv.level);
        pl.add_stats(-d2,5);
        co+=d.co_wander_around[23];
        co+="\n";
        co+="\n"+d.msg_stats[4]+std::to_string(d1)+d.msg_sub;
        co+="\n"+d.msg_stats[5]+std::to_string(d2)+d.msg_sub;
    }
    print_update(co,d.bt_wander_around);
    // End turn
    game_turn_pass();
}

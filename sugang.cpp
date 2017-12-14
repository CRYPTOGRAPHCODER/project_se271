#include "game.h"
#include "functions.h"

/// Sugang

/* add people to sugang
*/
void gameManager::sugang_time_pass(double timepass){
    if(pl.item_check(17)){
        timepass*=0.5;
    }
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
}

/* apply subjects
 *
 */
void gameManager::sugang_apply(int index){
    // Apply
    bool AppDeapp = true;
    bool apply = true;
    for(int i=0;i<SUBJECTS_MAX;i++){
        if(pl.get_subjects()[i] == index){
            pl.get_subjects()[i] = -1;
            s[index].attend_people--;
            AppDeapp = false;
        }
    }
    if(AppDeapp){
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
    if(!AppDeapp){
        print_sugang_apply(gv.gamestate-100,'c');
    }else if(apply){

        print_sugang_apply(gv.gamestate-100,'s');
    }else{
        print_sugang_apply(gv.gamestate-100,'f');
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

/* print my sugang data
 * Printing subject datas
 */
void gameManager::print_sugang_my_data(){
    std::string c;
    c+=d.co_s_my;
    c+="\n시간        수강희망/수강제한  분류    과목명";
    for (int i=0;i<SUBJECTS_MAX;i++){
        if(pl.get_subjects()[i]==-1){
            continue;
        }
        c+="\n";
        c+=print_subject_data(pl.get_subjects()[i],2);
    }
    print_update(c,d.bt_s_my);
}

/* print sugang apply
 * Printing subject apply data
 */
void gameManager::print_sugang_apply(int index, char mode){
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
    if(mode=='n'){

    }
    else if(mode == 'c'){
        c+="\n"+d.co_sugang_cancel;
    }
    else if(mode == 's'){
        c+="\n"+d.co_sugang_success;
    }
    else if(mode == 'f'){
        c+="\n"+d.co_sugang_fail;
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
        int basic_workload = 170*gv.level*((double)s[i].level/3+0.67);
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
            for(int k=0;k<4;k++){
                s[i].workload[k] *=1.5;
            }
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

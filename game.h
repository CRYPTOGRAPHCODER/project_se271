#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <cstdio>
#include <random>
#include <time.h>

#include "windows.h"
#include "player.h"

constexpr int MAX_SUBJECT = 100;
constexpr int DATA_LENGTH = 100;
constexpr int BUTTON_LENGTH = 9;

struct subject{
public:
  std::string title;
  int timetable[3] = {0,0,0};
  int credit;
  int workload[4] = {0,0,0,0};
  int attend_limit;
  int attend_hope;
  int attend_people;
  int category;
};

struct data
{
    std::string co_ = "";
    std::string bt_[9] = {"","","","","","","","",""};

    std::string co_init = "-";
    std::string bt_init[9] = {"다음","","","","","","","",""};


    std::string co_intro01 = "합격을 축하드립니다! 당신은 길고 긴 수험 생활을 끝내고 대학교에 진학하였습니다.";
    std::string bt_intro[9] = {"다음","","","","","","","",""};
    std::string co_intro02 = "기본적인 조작 방법에 대해서 설명하겠습니다.\n본 게임에서 모든 유효한 조작은 아래 9개의 버튼을 눌러서 사용합니다.";
    std::string bt_intro02[9] = {"다음","","","","","","","",""};
    std::string co_intro03 = "왼쪽의 정보창은 현재의 스탯을 표시합니다.\n아래는 메모장으로 자유롭게 내용을 작성해도 무방합니다.";
    std::string bt_intro03[9] = {"다음","","","","","","","",""};
    std::string co_intro04 = "그렇다면, 게임을 시작하겠습니다. 4년 (이상)의 기간동안 무사히 살아남아 졸업까지 해 보세요!";
    std::string bt_intro04[9] = {"다음","","","","","","","",""};

    std::string co_main = "어디로 갈까요?";
    std::string bt_main[9] = {"밖으로 나가기","컴퓨터 키기","상점으로 가기","방에서 휴식","공부하기","","","",""};
    std::string co_outside = "밖으로 나왔습니다. 어디로 갈까요?";
    std::string bt_outside[9] = {"친구를 만나기","동아리방 가기","교수님 만나기","주변을 정처없이 돌아다니기","일하러 가기","","","","집으로 돌아가기"};
    std::string co_internet = "컴퓨터를 켰습니다. 어디에 들어갈까요?";
    std::string bt_internet[9] = {"수강신청!","학부생 홈페이지","페이스북","학부생 커뮤니티","","","","","컴퓨터 끄기"};
    std::string co_store = "상점에 도착했습니다.";
    std::string bt_store[9] = {"","","","","","","","",""};
    std::string co_rest = "집에서 휴식합니다. 체력을 회복합니다.";
    std::string bt_rest[9] = {"다음","","","","","","","",""};
    std::string co_meet_friend[5] = {"-",
                                     "친구를 만났더니, 갑자기 친구가 인생 고민을 털어놓기 시작합니다.\n수강신청도 중요하지만, 친구의 고민만큼 중요한 것은 또 없죠. 고민을 들어주고, 내친김에 술도 한 잔 사 줍니다.",
                                     "친구가 수강 신청 과목에 대해서 흥미로운 이야기를 해 줍니다.",
                                     "친구가 오늘은 노래방이 어떠냐고 물어봅니다. 당연히 가야겠죠?",
                                     "-"};
    std::string bt_meet_friend[9] = {"다음","","","","","","","",""};

    std::string co_work = "당신은 열심히 일했습니다.";
    std::string bt_work[9] = {"다음","","","","","","","",""};

    std::string co_study[5] = {"당신은 열심히 공부했습니다.",
                               "방학이지만 집중해서 공부했습니다."
                               "게임을 하고 싶은 열망을 누르고 공부했습니다."
                               "오늘은 왠지 공부가 잘 되는군요."
                               "재밌게 공부했습니다."};
    std::string bt_study[9] = {"다음","","","","","","","",""};

    std::string msg_add = "만큼 증가했습니다.";
    std::string msg_sub = "만큼 감소했습니다.";
    std::string msg_money = "돈이 ";
    std::string msg_life = "체력이 ";
    std::string msg_stats[6] = {"체력 스탯이 ",
                                "회복 스탯이 ",
                                "이학 스탯이 ",
                                "공학 스탯이 ",
                                "문학 스탯이 ",
                                "사회 스탯이 "};


    std::string subjects[100] = {"시스템 뇌과학 개론 ","뇌질환 및 뇌의 질병 ","Thesis ","이노베이션경영 개론","융복합 생리학","융복합 영상학 개론","과학과 예술 ","고급 고체물리학","고급 양자역학","고체화학","자성체소재","열역학 ","고분자 개론","촉매화학 ","Thesis ","비교역사학","음악","체육","쓰기·읽기·말하기","동서양 철학의 통시적 이해","English for Science Leaders","융합탐구세미나","Scientific Writing","글로벌리더십 (리더십 실습)","근대 사회와 사상","현대 사회와 윤리","법과 사회","글로벌 정치경제","경제학 입문","과학기술과 현대사회","과학기술사의 주요장면","인문사회과학 특강","조직관리","재무회계","영화와 문학","기술평가 실무","지식재산권 실무","과학기술과 저널리즘 실무","EE:선형시스템 ","CS:운영체제 ","CSE:분산 및 병렬 컴퓨팅 ","EE&CSE:무선 네트워크 ","EE&CSE: 컨벡스 최적화","고급 생화학","세포신호전달과 생명 연속성 ","생물 의학 ","응용유체역학","선형시스템 제어","마이크로/나노공학 ","모터시스템제어","Thesis ","다변수 미적분학","전자기학","전자기학실험","기초화학실험","기초화학실험 ","분자와 생명현상","분자와 생명현상","분자와 생명현상 실험","다변수 미적분학 연습","다변수 미적분학 연습","복합 공학 수학","유전자의 구조와 발현","확률과 통계","복합 공학 수학 연습","복합 공학 수학 연습","확률과 통계(실습)","자동제어시스템","열 및 통계 물리 ","전기역학","유기화학의 이해 ","화학속의 물리학 ","세포와 생명현상","생명과학실험 ","디자인공학","편미분 방정식 ","고급대수 ","위상수학","고체물리 ","응용물리 실험","생체분자론","유기반응의 이해 ","심화화학실험","화학평형과 변화의 이해","생명과학특강  ","생명현상의 정량적 이해 ","인체의 구조와 질병 ","전기전자 공학  ","열유체공학 ","메카트로닉스 ","신경과학  ","데이터베이스개론","빅데이터 분석 및 시각화 개론 ","의공학개론 ","컴퓨터 알고리즘 ","수치해석 ","비선형 동력계","응용수학방법론 ","감염과 면역 ","공학적 설계"};
};

class gameManager{
private:
    // Global variables that indicates turns and player
    // Turn : 10 Days, 4 times
    int turn;
    // Player variable holds data of player
    player pl;
    // Determine state of the game
    // -1, -2 ... game over
    // 0, start of the game
    int gamestate = 0;
    // Define enough number of subjects
    subject s[MAX_SUBJECT];
    // String data to print to console
    std::string console;
    // String data to print to buttons
    std::string button[BUTTON_LENGTH];
    // data
    data d;
    // global level - basic is 10
    double level = 1;
public:
    gameManager();
    ~gameManager();
    double rnd_d();
    int* rnd_ia(int lim,int coun);
    // Each action to proceed
    void proceed(int input);
    // Update console and button text
    void print_update(std::string co, std::string* bt);


    // Generates subjects for each semester
    void generate_subjects();

    // Outside actions
    void meet_friend();
    void visit_professor();
    void club_room();
    void wander_around();
    void work();
    void study();
    // Computer actions
    void sugang();
    // Store
    void store();
    // Rest
    void rest();
    // Handle end of the each turn
    void game_turn_pass();

    void calculate_semester();
    void game_over();



    player get_pl(){return this->pl;}
    int get_turn(){return this->turn;}
    int get_gamestate(){return this->gamestate;}
    std::string get_console(){return this->console;}
    std::string get_button(int i){return this->button[i];}
};



#endif

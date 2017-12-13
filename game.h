#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <cstdio>

#include "windows.h"
#include "player.h"

constexpr int SUBJECT_BUFFER = 100;         // Max number of subjects
constexpr int DATA_LENGTH = 100;
constexpr int BUTTON_LENGTH = 9;            // Amount of the Button

// Struct subject - holds subject's data
struct subject{
public:
  int title;
  int level;
  int timetable[3] = {0,0,0};
  int credit;
  int workload[4] = {0,0,0,0};
  int attend_limit;
  int attend_hope;
  int attend_people;
  int category;
  int area;
};

struct data
{
    std::string bt_basic[9] = {"다음","","","","","","","",""};

    std::string co_init = "-";
    std::string bt_init[9] = {"다음","","","","","","","",""};

    std::string co_intro01 = "게임을 시작합니다.";
    std::string co_intro02 = "합격을 축하드립니다! 당신은 길고 긴 수험 생활을 끝내고 대학교에 진학하였습니다.\n기본적인 조작 방법에 대해서 설명하겠습니다.\n본 게임에서 모든 유효한 조작은 아래 9개의 버튼을 눌러서 사용합니다.";
    std::string co_intro03 = "왼쪽의 정보창은 현재의 스탯을 표시합니다.\n\n가장 위부터 시간, 이름, 체력, 각종 스탯, 아이템, 그리고 돈과 점수, 마지막으로 이수한 학점을 표시하는 막대가 있습니다.\n아래는 메모장으로 자유롭게 내용을 작성해도 무방합니다.";
    std::string co_intro04 = "한 학기는 총 10일로 이루어져 있습니다. 하루는 총 아침, 점심, 저녁, 밤 네 개의 시간대로 분류되며, 8일째 아침부터는 수강신청을 할 수 있습니다.\n단, 수강 가능 과목의 목록은 언제든 확인이 가능하며, 턴을 소모하지 않습니다. 상점 또한 턴을 소모하지 않습니다.";
    std::string co_intro05 = "게임을 클리어하기 위해서는 필수과목과 선택과목에 해당하는 학점을 모두 채우면서 한 학기를 체력이 0 이상 남긴 채 종료하면 됩니다.\n게임 중 언제라도 체력이 0 이하로 내려간다면 게임 오버가 됩니다. 마지막 학기에 마지막 과목을 들은 뒤에도 체력이 0이 된다면, 게임 오버입니다.\n\n필수 과목의 목록은 따로 존재하지 않지만, 다른 과목보다 수강할 때 필요한 에너지가 더 많이 들어갑니다.\n\n그렇다면, 게임을 시작하겠습니다. 4년 (이상)의 기간동안 무사히 살아남아 졸업까지 해 보세요!\n\n 팁 : 실제 과목 명과 예측되는 요구 스탯에는 큰 관련이 없을 수도 있습니다.";

    std::string co_main = "어디로 갈까요?";
    std::string bt_main[9] = {"밖으로 나가기","수강신청","상점으로 가기","방에서 휴식","공부하기","운동하기","","",""};

    std::string co_outside = "밖으로 나왔습니다. 어디로 갈까요?";
    std::string bt_outside[9] = {"친구를 만나기","동아리방 가기","교수님 만나기","주변을 정처없이 돌아다니기","일하러 가기","","","","집으로 돌아가기"};
    std::string co_sugang = "수강신청 페이지에 들어왔습니다.";
    std::string bt_sugang[9] = {"로그인(8일 이후부터 로그인 가능)","과목 정보 보기","수강신청한 과목 보기","","","","","","컴퓨터 끄기"};
    std::string co_store = "상점에 도착했습니다.";
    std::string bt_store[9] = {"","","","","","","","","돌아가기"};
    std::string co_rest = "집에서 휴식합니다. 체력을 회복합니다.";
    std::string co_study[5] = {"당신은 열심히 공부했습니다.",
                               "방학이지만 집중해서 공부했습니다."
                               "게임을 하고 싶은 열망을 누르고 공부했습니다."
                               "오늘은 왠지 공부가 잘 되는군요."
                               "재밌게 공부했습니다."};
    std::string co_exercise[5] = {"당신은 열심히 운동했습니다.",
                               "방학이지만 집중해서 운동했습니다."
                               "게임을 하고 싶은 열망을 누르고 운동했습니다."
                               "오늘은 왠지 운동이 잘 되는군요."
                               "재밌게 운동했습니다."};

    std::string co_meet_friend[30] = {"-"};

    std::string co_work = "당신은 열심히 일했습니다.";

    std::string co_wander_around[24] = {"멍 때리기의 대가 \n\n 당신이 정신 차릴 때에는 이미 시간이 많이 흐른 뒤였습니다. 바보가 된 느낌을 받습니다.",
                                        "달리기 선수 \n\n 당신은 갑자기 뛰고 싶어졌습니다. 천천히, 그리고 꾸준하게 달립니다.",
                                        "전력 질주 \n\n 당신은 갑자기 뛰고 싶어졌습니다. 전력질주를 한 당신은 모든 사람이 지켜보는 것을 보고 여기가 학교 건물 내라는 것을 알게되었습니다.\n당신은 온 힘을 다해 그 곳에서 도망칩니다.",
                                        "사소한 충돌 \n\n 모르는 사람과 부딪힙니다. 아무도 신경쓰지 않고 서로를 지나칩니다. 아무 일도 일어나지 않습니다.",
                                        "사소한 충돌 \n\n 모르는 사람과 부딪힙니다. 그 사람이 사과하고, 당신은 보상을 요구합니다.",
                                        "사소한 충돌 \n\n 모르는 사람과 부딪힙니다. 그 사람이 화가 나 당신에게 싸움을 걸었고, 당신은 싸움에서 집니다.",
                                        "책의 힘 \n\n 도서관에 갔습니다. 감동적 실화에 관한 책을 보고 당신은 눈물을 흘립니다. 문학 스탯이 증가합니다.",
                                        "책의 힘 \n\n 도서관에 갔습니다. 다양한 전공 서적을 읽고 당신은 지식이 늘은 것에 감탄합니다.",
                                        "책의 힘 \n\n 도서관에 갔습니다. 당신은 책을 읽으려고 했지만 집중이 되지 않습니다. 시간을 낭비했지만 당신은 보람을 느낍니다.",
                                        "친구의 선물 \n\n 친구가 두 개의 선물 중 하나를 고르라고 합니다. 당신은 작은 것을 고릅니다. 귀중한 아이템을 얻었습니다.",
                                        "친구의 선물 \n\n 친구가 두 개의 선물 중 하나를 고르라고 합니다. 당신은 큰 것을 고릅니다. 거기에는 아무것도 들어있지 않았고, 당신은 허무함을 느낍니다.",
                                        "도플갱어 \n\n 당신과 매우 비슷하게, 아니 똑같이 생긴 사람을 만납니다. 서로 자신이 진짜라고 우깁니다. 서로 싸우다가 결국 못 본 것으로 하기로 합니다.",
                                        "도플갱어 \n\n 당신과 매우 비슷하게, 아니 똑같이 생긴 사람을 만납니다. 서로 마음이 맞아 협력하려고 합니다. 같은 사람 두 명은 무적이 됩니다.",
                                        "소매치기 \n\n 어떤 사람이 당신을 지나친 후 뜁니다. 수상하게 생각한 당신은 돈이 없어진 것을 깨달았지만, 이미 늦은 뒤였습니다.",
                                        "강도 \n\n 어떤 사람이 당신을 지나친 후 뜁니다. 수상하게 생각한 당신은 아이템이 하나 없어진 것을 깨달았지만, 이미 늦은 뒤였습니다.",
                                        "오늘은 내가 요리사 \n\n 배가 고픈 당신은 휴게실에서 요리를 합니다. 요리를 먹은 당신은 건강해진 느낌을 받습니다.",
                                        "오늘은 내가 요리사 \n\n 배가 고픈 당신은 휴게실에서 요리를 합니다. 요리를 먹은 당신은 속이 이상하다는 것을 느낍니다.",
                                        "친구의 질문 \n\n 친구가 모르는 것을 당신에게 물어봅니다. 당신은 명확하게 그것을 설명해줍니다.",
                                        "친구의 질문 \n\n 친구가 모르는 것을 당신에게 물어봅니다. 당신은 잘 알지 못해 열심히 내용을 찾아봤지만, 진전이 없었습니다.",
                                        "실험 조언 \n\n 친구의 실험을 도와줍니다. /당신은 열심히 했지만, 실수를 해 피해를 주고 말았습니다. 자신감이 떨어집니다.",
                                        "목적 없는 사람 \n\n 정처없이 이곳저곳을 돌아다닙니다. 아무것도 하지 않았지만 시간은 흘렀습니다.",
                                        "특강 \n\n 특강이 있는 것을 안 당신은 특강을 들으러 갑니다. 특강 후 특별 추첨에서 당신이 당첨되었습니다!",
                                        "특강 \n\n 특강이 있는 것을 안 당신은 특강을 들으러 갑니다. 특강은 좋았지만, 졸린 당신에게는 그렇지 않았습니다.",
                                        "의미 없는 토론 \n\n 어떤 두 사람이 책에 대해서 토론을 합니다. 당신도 참여했지만, 곧 의미없음을 알게되고 쓸데 없는 정보들만 늘었음을 깨닫습니다."};
    std::string bt_wander_around[9] = {"다음","","","","","","","",""};

    // Sugang
    std::string co_s_watch = "이번 학기의 수강 가능한 과목 목록입니다.";
    std::string bt_s_watch[9] = {"","","","","","","","","돌아가기"};

    std::string co_s_my = "현재 수강 신청이 된 과목입니다.";
    std::string bt_s_my[9] = {"","","","","","","","","돌아가기"};

    std::string co_s_apply[2] = {"수강하고 싶은 과목에 해당하는 버튼을 눌러 주세요.\n\n새로운 과목을 확인하거나, 수강신청을 시도하면 남은 시간이 감소합니다.\n남은 시간 : ","\n\n현재까지 수강한 과목 목록"};
    std::string bt_s_apply[9] = {"","","","","","","","다음","수강신청 끝내기"};

    std::string co_logout = {"시간 제한이 종료되었습니다."};
    std::string bt_logout[9] = {"","","","","","","","","수강신청 끝내기"};

    std::string sb_day[5] = {"월","화","수","목","금"};
    std::string sb_time[4] = {"아침","점심","오후","저녁"};
    std::string sb_category[2] = {"교선필수","교선선택"};

    std::string co_sugang_fail = "\n\n수강 신청에 실패했습니다.";
    std::string co_sugang_success = "\n\n수강 신청에 성공했습니다.";
    std::string co_sugang_cancel = "\n\n수강 과목을 수강 취소했습니다.";

    // End of Semester
    std::string co_semester[2] = {"한 학기를 무사히 마쳤습니다. 이번 학기에 수강하게 되는 과목은 당신에게 얼마나 어려운 과목일까요?\n",
                                  "이번 학기도 힘냅시다!"};
    std::string bt_semester[9] = {"다음","","","","","","","",""};

    // Game over and Game Clear
    std::string co_gameover[6] = {"\n★★★★　★★★★　★★　★★　★★★★　　　★★　　★　　★　★★★★　★★★★",
                                  "\n★　　　　★　　★　★　★　★　★　　　　　★　　★　★　　★　★　　　　★　　★",
                                  "\n★　★★　★★★★　★　　　★　★★★★　　★　　★　★　★　　★★★★　★★★　",
                                  "\n★　　★　★　　★　★　　　★　★　　　　　★　　★　★★　　　★　　　　★　　★",
                                  "\n★★★★　★　　★　★　　　★　★★★★　　　★★　　★　　　　★★★★　★　　★",
                                  "\n\n게임 오버! 왼쪽의 최종 스코어를 확인해 주세요.\n\n ▶ 새 게임 - Menu -> Game Start\n ▶ 게임 로드 - Menu -> Game Load"};
    std::string bt_gameover[9] = {"","","","","","","","",""};
    std::string co_gameclear[6] = {"\n★★★★　★★★★　★★　★★　★★★★　　★★★　★　　　★★★　★★　　★★",
                                  "\n★　　　　★　　★　★　★　★　★　　　　　★　　　★　　　★　　　★　★　★　★",
                                  "\n★　★★　★★★★　★　　　★　★★★★　　★　　　★　　　★★★　★★★　★★",
                                  "\n★　　★　★　　★　★　　　★　★　　　　　★　　　★　　　★　　　★　★　★　★",
                                  "\n★★★★　★　　★　★　　　★　★★★★　　★★★　★★★　★★★　★　★　★　★",
                                  "\n\n게임 클리어! 당신은 무사히 대학교를 졸업했습니다!\n앞으로 어떤 일들이 기다리고 있을까요?\n\n왼쪽의 최종 스코어를 확인해 주세요.\n\n 2017 SE271 객체지향 프로그래밍 팀 프로젝트\n 이승현, 배지훈, 장호민"};
    std::string bt_gameclear[9] = {"","","","","","","","",""};


    // Stat changing message
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
    std::string msg_item = "아이템 ";
    std::string msg_gain = "을 얻었습니다 ";
    std::string msg_loss = "을 잃었습니다 ";

    // Subject names
    std::string subjects[100] = {"Thesis","음악","체육","English for Leaders","Scientific Writing","디자인공학","감염과 면역","공학적 설계","응용수학방법론","선형대수학","다변수 미적분학","전자기학 실험","분자와 생명현상 실험","응용물리 실험","심화화학 실험","고급대수","위상수학","복합 공학 수학","확률과 통계","편미분 방정식","화학속의 물리학","고전역학","신경과학","고급 고체물리학","고급 양자역학","고체화학","자성체소재","열역학","고분자 개론","촉매화학","고급 생화학","전자기학","생물 의학","응용유체역학","세포신호전달과 생명 연속성","분자와 생명현상","유전자의 구조와 발현","열 및 통계 물리","전기역학","유기화학의 이해","선형시스템","운영체제","분산 및 병렬 컴퓨팅","무선 네트워크","컨벡스 최적화","다변수 미적분학","선형시스템 제어","마이크로/나노공학","모터시스템제어","인공지능","객체지행 프로그래밍","자동제어시스템","프로그래밍","메카트로닉스","전기전자 공학","열유체공학","데이터베이스개론","빅데이터 분석 및 시각화 개론","컴퓨터 알고리즘","수치해석","융복합 영상학 개론","과학과 예술","비교역사학","쓰기·읽기·말하기","동서양 철학의 통시적 이해","과학기술사의 주요장면","인문사회과학 특강","영화와 문학","과학기술과 저널리즘 실무","한국현대문학과 사상","문학과 대중문화","동양의 고전","서양근대문학의 이해","문학과 정신분석","말과 마음","인간 복제와 문학","문학과 사회","도스토예프스키와 톨스토이","언어의 세계","일본 애니메이션의 이해","이노베이션경영 개론","융합탐구세미나","글로벌리더십 (리더십 실습)","근대 사회와 사상","현대 사회와 윤리","법과 사회","글로벌 정치경제","경제학 입문","과학기술과 현대사회","조직관리","재무회계","기술평가 실무","지식재산권 실무","기업과 사회","현대경제의 이해","현대사회와 법","시장경제와 법","민주시민과 헌법","소비자와 시장","공공행정의 이해"};

    // Items
    int item_number = 6;
    std::string items[30] = {"", "고성능 컴퓨터", "보충제", "온돌매트", "전공서적", "인간사료","공대생의 영혼"};
    // 0 : Empty
    // 1 : Computer     = Sugang apply time * 1.5
    // 2 : Vitamin      = heal 50*level hp per each turn
    // 3 : Mat          = increase rest recovery effect by 30%
    /// 4 : Book         = Stat increase effect sometimes doubles;
    // 5 : Human Food   = heal 20*level hp per each turn
    // 6 : Soul of GDS  = revive with 30% health if dies
};

struct global_variables{
    // Turn : 10 Days, 4 times
    int turn;
    // global level - basic is 1
    double level;
    // Determine state of the game
    // -1, -2 ... game over
    // 0, start of the game
    int gamestate = 0;
    // Time limit for sugang apply
    int s_time = 180;
    int s_time_full = 180;
    // Number of subject
    int subject_num;
};

class gameManager{
private:
    // Global variables that indicates game flow - need to save
    global_variables gv;
    // Define enough number of subjects - need to save
    subject s[SUBJECT_BUFFER];
    // String data to print to console
    std::string console;
    // String data to print to buttons
    std::string button[BUTTON_LENGTH];
public:
    // Player variable holds data of player - need to save
    // Public OK since
    player pl;
    // text data
    data d;


    gameManager();
    ~gameManager();
    /*
    double rnd_d();
    int* rnd_ia(int lim,int coun);
    */
    // Each action to proceed
    void proceed(int input);
    // Update console and button text
    void print_update(std::string co, std::string* bt);

    // Generates subjects for each semester
    void generate_subjects();

    // print_update sugang data
    void print_sugang_data();
    void print_sugang_my_data();
    void print_sugang_apply(int index, char mode);
    std::string print_subject_data(int i, int mode);
    void sugang_time_decrease(double min, double max);

    // Outside actions
    void meet_friend();
    void visit_professor();
    void club_room();
    void wander_around();
    void work();
    void study();
    void exercise();
    // Computer actions
    void sugang();
    void sugang_apply(int index);
    void sugang_time_pass(double timepass);
    // Store
    void store();
    // Rest
    void rest();
    // Handle end of the each turn
    void game_turn_pass();
    // Handle end of the semester
    void calculate_semester();



    player get_pl(){return this->pl;}
    void set_pl(player gl){ pl = gl;}
    global_variables get_gv(){return this->gv;}
    void set_gv(global_variables lg) { gv = lg;}
    subject get_subject(int index) {return this->s[index];}
    void set_subject(subject ls, int index) {s[index] = ls;}
    int get_turn(){return gv.turn;}
    int get_gamestate(){return gv.gamestate;}
    std::string get_console(){return this->console;}
    std::string get_button(int i){return this->button[i];}

};



#endif

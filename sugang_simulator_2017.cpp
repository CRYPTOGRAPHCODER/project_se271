#include "sugang_simulator_2017.h"
#include "ui_sugang_simulator_2017.h"


Sugang_Simulator_2017::Sugang_Simulator_2017(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sugang_Simulator_2017)
{
    //Ui Setup
    ui->setupUi(this);
/*
    QFont fon("Courier New",9);
    fon.setStyleHint(QFont::Monospace);
    ui->textbox_console->setfont(fon);
    //QApplication::setFont(font);
*/
    ui->prog_time->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_credit_mandatory->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_hp->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_credit_selective->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");

    //Game Setup
    player_data_update(g.get_pl(),g.get_turn());
    std::string console = "";

    console += "  .d8888b.  888     888  .d8888b.         d8888 888b    888  .d8888b.  ";
    console += "\n d88P  Y88b 888     888 d88P  Y88b       d88888 8888b   888 d88P  Y88b ";
    console += "\n Y88b.      888     888 888    888      d88P888 88888b  888 888    888 ";
    console += "\n  'Y888b.   888     888 888            d88P 888 888Y88b 888 888        ";
    console += "\n     'Y88b. 888     888 888  88888    d88P  888 888 Y88b888 888  88888 ";
    console += "\n       '888 888     888 888    888   d88P   888 888  Y88888 888    888 ";
    console += "\n Y88b  d88P Y88b. .d88P Y88b  d88P  d8888888888 888   Y8888 Y88b  d88P ";
    console += "\n  'Y8888P'   'Y88888P'   'Y8888P88 d88P     888 888    Y888  'Y8888P88 ";
    console += "\n  _______ _____ _______ _     _        _______ _______  _____   ______";
    console += "\n  |______   |   |  |  | |     | |      |_____|    |    |     | |_____/";
    console += "\n  ______| __|__ |  |  | |_____| |_____ |     |    |    |_____| |    \\_";
    console += "\n       2  0  1  7           \"The Realistic life of undergraudates\"";
    console += "\n\n ▶ 새 게임 - Menu -> Game Start";
    console += "\n ▶ 게임 로드 - Menu -> Game Load";

    console_update(console);
    std::string but = "";
    for(int i=0;i<9;i++){
        button_update(but,i);
    }

    ui->actionSave_Game->setEnabled(false);

}

Sugang_Simulator_2017::~Sugang_Simulator_2017()
{
    delete ui;
}

void Sugang_Simulator_2017::on_actionStart_Game_triggered()
{
    ui->actionSave_Game->setEnabled(true);
    g = gameManager();
    update();
}
void Sugang_Simulator_2017::on_actionSave_Game_triggered()
{
    ui->textbox_console->setText("Saving...");
    player SaveData = g.get_pl();
    std::ofstream fout("Savedata.dat", std::ios_base::out|std::ios_base::binary);
    fout.write((char*)&SaveData, sizeof(SaveData));
    fout.close();
}

void Sugang_Simulator_2017::on_actionLoad_Game_triggered()
{
    ui->actionSave_Game->setEnabled(true);
    gameManager LoadData;
    std::ifstream fin("Savedata.dat", std::ios_base::in | std::ios_base::binary);
    if(fin.is_open() == false){
        ui->textbox_console->setText("No Saved File");
    }
    else{
        fin.read((char*)&LoadData, sizeof(LoadData));
        fin.close();
        ui->textbox_console->setText("Loading Complete");
    }
    g = LoadData;
    update();
}


void Sugang_Simulator_2017::player_data_update(player pl,int t){
    ui->text_hp->setText(QString::number(pl.get_life())+"/"+QString::number(pl.get_life_f()));
    ui->text_money->setText("돈     "+QString::number(pl.get_money()));
    ui->text_score->setText("점수     "+QString::number(pl.get_score()));
    ui->text_stats->setText("스탯       체력 "+QString::number(pl.get_stats()[0])+"   회복 "+QString::number(pl.get_stats()[1])
            +"   이학 "+QString::number(pl.get_stats()[2])+"   공학 "+QString::number(pl.get_stats()[3])
            +"   문학 "+QString::number(pl.get_stats()[4])+"   사회 "+QString::number(pl.get_stats()[5]));
    ui->text_name->setText("이름     " +QString::fromStdString(pl.get_name()));
    ui->text_credit_mandatory->setText("필수 "+QString::number(pl.get_credit_required_ess())+"/"+QString::number(pl.get_credit_required_ess()));
    ui->text_credit_selective->setText("선택 "+QString::number(pl.get_credit_required_chs())+"/"+QString::number(pl.get_credit_required_chs()));
    QString tx = "";
    tx="Year "+QString::number(t/40+1)+", Day "+QString::number((t/4)%10+1)+", ";
    switch(t%4+1){
      case 1: tx+="아침";break;
      case 2: tx+="오후";break;
      case 3: tx+="저녁";break;
      case 4: tx+="밤";break;
    }
    tx+=", 턴 " + QString::number(t);
    ui->text_time->setText(tx);

    ui->prog_hp->setMaximum(pl.get_life_f());
    ui->prog_hp->setValue(pl.get_life());
    ui->prog_time->setMaximum(40);
    ui->prog_time->setValue(t%40);
    ui->prog_credit_mandatory->setMaximum(pl.get_credit_required_ess());
    ui->prog_credit_mandatory->setValue(pl.get_credit_acquired_ess());
    ui->prog_credit_selective->setMaximum(pl.get_credit_required_chs());
    ui->prog_credit_selective->setValue(pl.get_credit_acquired_chs());

    if(t/4%10>=7){
        ui->prog_time->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #dd3636; width: 1px;}");
    }
    else{
        ui->prog_time->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");

    }
    if(pl.get_life()<pl.get_life_f()*0.3){
        ui->prog_hp->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #dd3636; width: 1px;}");
    }else{
        ui->prog_hp->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    }
}
void Sugang_Simulator_2017::console_update(std::string text){
    ui->textbox_console->setText(QString::fromStdString(text));
}
void Sugang_Simulator_2017::button_disable(){
    ui->button1->setText(QString::fromStdString(""));
    ui->button2->setText(QString::fromStdString(""));
    ui->button3->setText(QString::fromStdString(""));
    ui->button4->setText(QString::fromStdString(""));
    ui->button5->setText(QString::fromStdString(""));
    ui->button6->setText(QString::fromStdString(""));
    ui->button7->setText(QString::fromStdString(""));
    ui->button8->setText(QString::fromStdString(""));
    ui->button9->setText(QString::fromStdString(""));
    ui->button1->setEnabled(false);
    ui->button2->setEnabled(false);
    ui->button3->setEnabled(false);
    ui->button4->setEnabled(false);
    ui->button5->setEnabled(false);
    ui->button6->setEnabled(false);
    ui->button7->setEnabled(false);
    ui->button8->setEnabled(false);
    ui->button9->setEnabled(false);
}
void Sugang_Simulator_2017::button_update(std::string da, int index){
    switch(index){
    case 0:
        if(da.compare("")==0){ui->button1->setEnabled(false);
        }else{ui->button1->setEnabled(true);}
        ui->button1->setText(QString::fromStdString(da));
    break;
    case 1:
        if(da.compare("")==0){ui->button2->setEnabled(false);
        }else{ui->button2->setEnabled(true);}
        ui->button2->setText(QString::fromStdString(da));
    break;
    case 2:
        if(da.compare("")==0){ui->button3->setEnabled(false);
        }else{ui->button3->setEnabled(true);}
        ui->button3->setText(QString::fromStdString(da));
    break;
    case 3:
        if(da.compare("")==0){ui->button4->setEnabled(false);
        }else{ui->button4->setEnabled(true);}
        ui->button4->setText(QString::fromStdString(da));
    break;
    case 4:
        if(da.compare("")==0){ui->button5->setEnabled(false);
        }else{ui->button5->setEnabled(true);}
        ui->button5->setText(QString::fromStdString(da));
    break;
    case 5:
        if(da.compare("")==0){ui->button6->setEnabled(false);
        }else{ui->button6->setEnabled(true);}
        ui->button6->setText(QString::fromStdString(da));
    break;
    case 6:
        if(da.compare("")==0){ui->button7->setEnabled(false);
        }else{ui->button7->setEnabled(true);}
        ui->button7->setText(QString::fromStdString(da));
    break;
    case 7:
        if(da.compare("")==0){ui->button8->setEnabled(false);
        }else{ui->button8->setEnabled(true);}
        ui->button8->setText(QString::fromStdString(da));
    break;
    case 8:
        if(da.compare("")==0){ui->button9->setEnabled(false);
        }else{ui->button9->setEnabled(true);}
        ui->button9->setText(QString::fromStdString(da));
    break;
    }
}

void Sugang_Simulator_2017::update(){
    button_disable();
    for(int i=0;i<9;i++){
        button_update(g.get_button(i),i);
    }
    console_update(g.get_console());
    player_data_update(g.get_pl(),g.get_turn());

}

void Sugang_Simulator_2017::on_button1_released(){
    g.proceed(1);
    update();
}
void Sugang_Simulator_2017::on_button2_released(){
    g.proceed(2);
    update();
}
void Sugang_Simulator_2017::on_button3_released(){
    g.proceed(3);
    update();
}
void Sugang_Simulator_2017::on_button4_released(){
    g.proceed(4);
    update();
}
void Sugang_Simulator_2017::on_button5_released(){
    g.proceed(5);
    update();
}
void Sugang_Simulator_2017::on_button6_released(){
    g.proceed(6);
    update();
}
void Sugang_Simulator_2017::on_button7_released(){
    g.proceed(7);
    update();
}
void Sugang_Simulator_2017::on_button8_released(){
    g.proceed(8);
    update();
}
void Sugang_Simulator_2017::on_button9_released(){
    g.proceed(9);
    update();
}

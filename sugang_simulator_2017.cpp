#include "sugang_simulator_2017.h"
#include "ui_sugang_simulator_2017.h"

#include "game.h"

Sugang_Simulator_2017::Sugang_Simulator_2017(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sugang_Simulator_2017)
{
    ui->setupUi(this);
    ui->prog_time->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_credit_mandatory->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_hp->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_credit_selective->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");


    player pl;
    int turn = 10;
    player_data_update(pl,turn);
    console_update("ah!");
    //button_update(but);
}

Sugang_Simulator_2017::~Sugang_Simulator_2017()
{
    delete ui;
}

void Sugang_Simulator_2017::on_actionStart_Game_triggered()
{
    //game_init();
}

void Sugang_Simulator_2017::on_actionSave_Game_triggered()
{
    //game_save();
}

void Sugang_Simulator_2017::on_actionLoad_Game_triggered()
{
    //game_load();
}

void Sugang_Simulator_2017::player_data_update(player pl,int t){
    ui->text_hp->setText(QString::number(pl.get_life())+"/"+QString::number(pl.get_life_f()));
    ui->text_money->setText("Money     "+QString::number(pl.get_money()));
    ui->text_name->setText("Name     " +QString::fromStdString(pl.get_name()));
    ui->text_credit_mandatory->setText(QString::number(pl.get_credit_required_ess())+"/"+QString::number(pl.get_credit_required_ess()));
    ui->text_credit_selective->setText(QString::number(pl.get_credit_required_chs())+"/"+QString::number(pl.get_credit_required_chs()));
    QString tx = "";
    tx="Year "+QString::number(t/40+1)+", Day "+QString::number((t/4)%10+1)+", ";
    switch(t%4+1){
      case 1: tx+="Morning";break;
      case 2: tx+="Afternoon";break;
      case 3: tx+="Evening";break;
      case 4: tx+="Night";break;
    }
    ui->text_time->setText(tx);

    ui->prog_hp->setMaximum(pl.get_life_f());
    ui->prog_hp->setValue(pl.get_life());
    ui->prog_time->setMaximum(40);
    ui->prog_time->setValue(t%40);
    ui->prog_credit_mandatory->setMaximum(pl.get_credit_required_ess());
    ui->prog_credit_mandatory->setValue(pl.get_credit_acquired_ess());
    ui->prog_credit_selective->setMaximum(pl.get_credit_required_chs());
    ui->prog_credit_selective->setValue(pl.get_credit_acquired_chs());
}
void Sugang_Simulator_2017::console_update(std::string text){
    ui->textbox_console->setText(QString::fromStdString(text));
}
void Sugang_Simulator_2017::button_update(std::string *da){
    int i = 0;
    ui->button1->setEnabled(false);
    ui->button2->setEnabled(false);
    ui->button3->setEnabled(false);
    ui->button4->setEnabled(false);
    ui->button5->setEnabled(false);
    ui->button6->setEnabled(false);
    ui->button7->setEnabled(false);
    ui->button8->setEnabled(false);
    ui->button9->setEnabled(false);
    while(i<9 || da[i]==""){
        switch(i){
            case 0:
                ui->button1->setText(QString::fromStdString(da[i]));
                ui->button1->setEnabled(true);
            break;
            case 1:
                ui->button2->setText(QString::fromStdString(da[i]));
                ui->button2->setEnabled(true);
            break;
            case 2:
                ui->button3->setText(QString::fromStdString(da[i]));
                ui->button3->setEnabled(true);
            break;
            case 3:
                ui->button4->setText(QString::fromStdString(da[i]));
                ui->button4->setEnabled(true);
            break;
            case 4:
                ui->button5->setText(QString::fromStdString(da[i]));
                ui->button5->setEnabled(true);
            break;
            case 5:
                ui->button6->setText(QString::fromStdString(da[i]));
                ui->button6->setEnabled(true);
            break;
            case 6:
                ui->button7->setText(QString::fromStdString(da[i]));
                ui->button7->setEnabled(true);
            break;
            case 7:
                ui->button8->setText(QString::fromStdString(da[i]));
                ui->button8->setEnabled(true);
            break;
            case 8:
                ui->button9->setText(QString::fromStdString(da[i]));
                ui->button9->setEnabled(true);
        break;
        }
    }
    delete[] da;
}

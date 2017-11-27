#include "sugang_simulator_2017.h"
#include "ui_sugang_simulator_2017.h"

#include "game.h"

Sugang_Simulator_2017::Sugang_Simulator_2017(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sugang_Simulator_2017)
{
    ui->setupUi(this);
    player pl;
    player_data_update(pl);

}

Sugang_Simulator_2017::~Sugang_Simulator_2017()
{
    delete ui;
}

void Sugang_Simulator_2017::on_actionStart_Game_triggered()
{
    game_init();
}

void Sugang_Simulator_2017::on_actionSave_Game_triggered()
{
    game_save();
}

void Sugang_Simulator_2017::on_actionLoad_Game_triggered()
{
    game_load();
}

void Sugang_Simulator_2017::player_data_update(player pl){
    ui->text_hp->setText(QString::number(pl.get_life())+"/"+QString::number(pl.get_life_f()));
    ui->text_money->setText("Money     "+QString::number(pl.get_money()));
    ui->text_name->setText("Name     " +pl.get_name());
    ui->text_credit_mandatory->setText(QString::number(pl.get_credit_required_ess())+"/"+QString::number(pl.get_credit_required_ess()));

}

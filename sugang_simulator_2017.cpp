#include "sugang_simulator_2017.h"
#include "ui_sugang_simulator_2017.h"

Sugang_Simulator_2017::Sugang_Simulator_2017(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sugang_Simulator_2017)
{
    ui->setupUi(this);
}

Sugang_Simulator_2017::~Sugang_Simulator_2017()
{
    delete ui;
}

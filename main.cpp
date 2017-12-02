#include "sugang_simulator_2017.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sugang_Simulator_2017 w;
    w.setFixedSize(1000,560);
    w.show();
    return a.exec();
}

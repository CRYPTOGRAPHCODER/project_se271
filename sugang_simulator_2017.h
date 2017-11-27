#ifndef SUGANG_SIMULATOR_2017_H
#define SUGANG_SIMULATOR_2017_H

#include <QMainWindow>

namespace Ui {
class Sugang_Simulator_2017;
}

class Sugang_Simulator_2017 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sugang_Simulator_2017(QWidget *parent = 0);
    ~Sugang_Simulator_2017();

private:
    Ui::Sugang_Simulator_2017 *ui;

private slots:
    void Main_SlotNewfile();
    void on_actionStart_Game_triggered();
    void on_actionSave_Game_triggered();
    void on_actionLoad_Game_triggered();
};


#endif // SUGANG_SIMULATOR_2017_H

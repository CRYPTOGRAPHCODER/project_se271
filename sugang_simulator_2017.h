#ifndef SUGANG_SIMULATOR_2017_H
#define SUGANG_SIMULATOR_2017_H

#include <QMainWindow>
#include <string>
#include "player.h"
#include "game.h"

namespace Ui {
class Sugang_Simulator_2017;
}
class Sugang_Simulator_2017 : public QMainWindow
{
    Q_OBJECT

private:
    Ui::Sugang_Simulator_2017 *ui;
    gameManager g;
    int selection;

public:
    explicit Sugang_Simulator_2017(QWidget *parent = 0);
    ~Sugang_Simulator_2017();
    void player_data_update(player pl, int  mturn);
    void console_update(std::string text);
    void button_update(std::string da, int index);


private slots:
    void on_actionStart_Game_triggered();
    void on_actionSave_Game_triggered();
    void on_actionLoad_Game_triggered();
    void on_button1_released();
    void on_button2_released();
    void on_button3_released();
    void on_button4_released();
    void on_button5_released();
    void on_button6_released();
    void on_button7_released();
    void on_button8_released();
    void on_button9_released();
    void button_disable();
};


#endif // SUGANG_SIMULATOR_2017_H

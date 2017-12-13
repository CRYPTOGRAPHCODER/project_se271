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
    // Set color and style for each progress bar - we don't need any glowing
    ui->prog_time->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_credit_mandatory->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_hp->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->prog_credit_selective->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");

    // Initialize gameManager
    g = gameManager();

    // Main window of the game
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
    // Update Console
    console_update(console);
    // Update Button
    std::string but = "";
    for(int i=0;i<9;i++){
        button_update(but,i);
    }
    // Disable Save
    ui->actionSave_Game->setEnabled(false);
}

Sugang_Simulator_2017::~Sugang_Simulator_2017()
{
    delete ui;
}

void Sugang_Simulator_2017::on_actionStart_Game_triggered()
{
    if(g.get_turn()>0){
        QMessageBox msgBox;
        msgBox.setText("You have pressed the New Game buttton");
        msgBox.setInformativeText("Do you want to restart the game?\nAny unsaved changes are not saved.");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Yes:
              g = gameManager();
              break;
          case QMessageBox::No:
              break;
          default:
            break;
        }
    }else{
        // Reset gameManager
        g = gameManager();
    }
    // Enable Save
    ui->actionSave_Game->setEnabled(true);
    // Update screen
    update();

}
void Sugang_Simulator_2017::on_actionSave_Game_triggered()
{

    // Save Game
    QMessageBox msgBox;
    msgBox.setText("You have pressed the save buttton");
    msgBox.setInformativeText("Do you want to save your changes?\nSave will be overwritten.");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Save){
        player SaveData1 = g.get_pl();
        global_variables SaveData2 = g.get_gv();
        subject SaveData3[100];
        for(int i = 0; i<SaveData2.subject_num;i++){
                SaveData3[i]=g.get_subject(i);
        }
        SaveData1.string_to_char();
        SaveData1.set_name("");
        std::ofstream fout1("Savedata1.txt");
        std::ofstream fout2("Savedata2.txt");
        std::ofstream fout3("Savedata3.txt");
        fout1.write((char*)&SaveData1, sizeof(SaveData1));
        fout2.write((char*)&SaveData2, sizeof(SaveData2));
        fout3.write((char*)&SaveData3, sizeof(SaveData3));
        fout1.close();
        fout2.close();
        fout3.close();
    }
    // Update Screen
    update();
}

void Sugang_Simulator_2017::on_actionLoad_Game_triggered()
{
    // Load Game
    // Enable Save Button
    ui->actionSave_Game->setEnabled(true);
    QMessageBox msgBox;
    msgBox.setText("Load game?");
    msgBox.setInformativeText("Do you want to load game?\nAny unsaved changes are not saved.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret ==QMessageBox::Yes ){
        player LoadData1;
        global_variables LoadData2;
        subject LoadData3[100];
        std::ifstream fin1("Savedata1.txt");
        std::ifstream fin2("Savedata2.txt");
        std::ifstream fin3("Savedata3.txt");
        if(fin1.is_open() == false){
            ui->textbox_console->setText("No Saved File");
        }
        else{
            fin1.read((char*)&LoadData1, sizeof(LoadData1));
            fin1.close();
            fin2.read((char*)&LoadData2, sizeof(LoadData2));
            fin2.close();
            fin3.read((char*)&LoadData3, sizeof(LoadData3));
            fin3.close();
        }
        g.set_pl(LoadData1);
        g.pl.char_to_string();
        LoadData2.gamestate = 19;
        g.set_gv(LoadData2);
        for(int i=0;i<LoadData2.subject_num;i++){
            g.set_subject(LoadData3[i],i);
        }ui->actionSave_Game->setEnabled(true);
    }
    // Update Screen
    update();
}

/* Updates player's data and some game data
 */
void Sugang_Simulator_2017::player_data_update(player pl,int t){
    g.pl.set_name(ui->textbox_name->toPlainText().toUtf8().constData());
    ui->text_hp->setText(QString::number(pl.get_life())+"/"+QString::number(pl.get_life_f()));
    std::string it = "아이템     ";
    for(int i=0;i<8;i++){
        if(pl.get_items()[i]>0){
            it+=g.d.items[pl.get_items()[i]]+", ";
        }
    }
    ui->text_items->setText(QString::fromStdString(it));
    ui->text_money->setText("돈     "+QString::number(pl.get_money()));
    ui->text_score->setText("점수     "+QString::number(pl.get_score()));
    ui->text_stats->setText("스탯       체력 "+QString::number(pl.get_stats()[0])+"   회복 "+QString::number(pl.get_stats()[1])
            +"   이학 "+QString::number(pl.get_stats()[2])+"   공학 "+QString::number(pl.get_stats()[3])
            +"   문학 "+QString::number(pl.get_stats()[4])+"   사회 "+QString::number(pl.get_stats()[5]));
    ui->text_name->setText("이름     ");
    ui->text_credit_mandatory->setText("필수 "+QString::number(pl.get_credit_acquired_ess())+"/"+QString::number(pl.get_credit_required_ess()));
    ui->text_credit_selective->setText("선택 "+QString::number(pl.get_credit_acquired_chs())+"/"+QString::number(pl.get_credit_required_chs()));
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
/* Update Console textbox
 */
void Sugang_Simulator_2017::console_update(std::string text){
    ui->textbox_console->setText(QString::fromStdString(text));
}
/* Disables(resets) all button
 */
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
/* Update Each button to desired text
 */
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
/* Update every data
 */
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

void Sugang_Simulator_2017::on_textbox_name_textChanged()
{
    g.pl.set_name(ui->textbox_name->toPlainText().toUtf8().constData());
    player_data_update(g.get_pl(),g.get_turn());
}

void Sugang_Simulator_2017::on_actionCredit_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("2017 SE271 Team Project");
    msgBox.setInformativeText("Lee SeungHyun, Jang HoMin, Bae JiHoon\nTroubleshoot : coder@dgist.ac.kr");
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Close);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Close:
          break;
      default:
          break;
    }
}

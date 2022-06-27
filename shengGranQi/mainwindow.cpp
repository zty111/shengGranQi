#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//属性部分

int p_ming, p_wen, p_wu, p_money, p_ti, p_level;
QString p_granjie, p_granzhi, p_name;
int gailv[5] = {25, 25, 25, 25, 0};

//抽卡部分

int randnum[100];
QString num_to_name[5] = {"德", "才", "功", "脏", "运"};
int flagnum = 4;

void set_gailv() {
    for(int i = 0, j = 0, cnt = 0; i < 100; ++i) {
        randnum[i] = j;
        ++cnt;
        if(cnt == gailv[j]) {
            ++j;
            cnt = 0;
        }
    }
}

void MainWindow::on_pushButton_one_clicked()
{
    set_gailv();
    if(!flagnum) {
        flagnum = 1;
        std::srand(std::time(0));
        ui->card_one->setText("");
        ui->card_two->setText("");
        ui->card_three->setText(num_to_name[randnum[std::rand() % 100]]);
        ui->card_four->setText("");
        ui->card_five->setText("");
    }
}

void MainWindow::on_pushButton_five_clicked()
{
    set_gailv();
    if(!flagnum) {
        flagnum = 5;
        std::srand(std::time(0));
        ui->card_one->setText(num_to_name[randnum[std::rand() % 100]]);
        ui->card_two->setText(num_to_name[randnum[std::rand() % 100]]);
        ui->card_three->setText(num_to_name[randnum[std::rand() % 100]]);
        ui->card_four->setText(num_to_name[randnum[std::rand() % 100]]);
        ui->card_five->setText(num_to_name[randnum[std::rand() % 100]]);
    }
}

//翻卡部分

bool luck = false;

int MainWindow::get_same_num(QString text) {
    int ans = 0;
    if(MainWindow::ui->card_one->text() == text) ui->card_one->setText(""), ++ans;
    if(MainWindow::ui->card_two->text() == text) ui->card_two->setText(""), ++ans;
    if(MainWindow::ui->card_three->text() == text) ui->card_three->setText(""), ++ans;
    if(MainWindow::ui->card_four->text() == text) ui->card_four->setText(""), ++ans;
    if(MainWindow::ui->card_five->text() == text) ui->card_five->setText(""), ++ans;
    return ans;
}

QString MainWindow::card_click(QString text, int same_num) {
    QString newtext = "【" + text + "】";
    if(text == "德") {
        flagnum -= same_num;
        if(luck) {
            same_num += 2;
            luck = false;
        }
        if(same_num >= 5)
            ;//sovle_de_five(..., newtext);
        else if(same_num >= 3)
            ;//sovle_de_three(..., newtext);
        else if(same_num >= 1)
            ;//sovle_de_one(..., newtext);
        return newtext;
    } else if(text == "才") {
        flagnum -= same_num;
        if(luck) {
            same_num += 2;
            luck = false;
        }
        if(same_num >= 5)
            ;//sovle_cai_five(..., newtext);
        else if(same_num >= 3)
            ;//sovle_cai_three(..., newtext);
        else if(same_num >= 1)
            ;//sovle_cai_one(..., newtext);
        return newtext;
    } else if(text == "功") {
        flagnum -= same_num;
        if(luck) {
            same_num += 2;
            luck = false;
        }
        if(same_num >= 5)
            ;//sovle_gong_five(..., newtext);
        else if(same_num >= 3)
            ;//sovle_gong_three(..., newtext);
        else if(same_num >= 1)
            ;//sovle_gong_one(..., newtext);
        return newtext;
    } else if(text == "脏") {
        flagnum -= same_num;
        if(luck) {
            same_num += 2;
            luck = false;
        }
        if(same_num >= 5)
            ;//sovle_zang_five(..., newtext);
        else if(same_num >= 3)
            ;//sovle_zang_three(..., newtext);
        else if(same_num >= 1)
            ;//sovle_zang_one(..., newtext);
        return newtext;
    } else if(text == "运") {
        flagnum -= same_num;
        luck = true;
        newtext += "\n\n人生转折点\n强化下次选择";
        return newtext;
    }
    return text;
}

void MainWindow::on_card_one_clicked()
{
    QString text = ui->card_one->text();
    QString newtext = card_click(text, get_same_num(text));
    ui->card_one->setText(newtext);
}

void MainWindow::on_card_two_clicked()
{
    QString text = ui->card_two->text();
    QString newtext = card_click(text, get_same_num(text));
    ui->card_two->setText(newtext);
}

void MainWindow::on_card_three_clicked()
{
    QString text = ui->card_three->text();
    QString newtext = card_click(text, get_same_num(text));
    ui->card_three->setText(newtext);
}

void MainWindow::on_card_four_clicked()
{
    QString text = ui->card_four->text();
    QString newtext = card_click(text, get_same_num(text));
    ui->card_four->setText(newtext);
}

void MainWindow::on_card_five_clicked()
{
    QString text = ui->card_five->text();
    QString newtext = card_click(text, get_same_num(text));
    ui->card_five->setText(newtext);
}

void MainWindow::add_history(QString text) {
    ui->history->append(text);
}

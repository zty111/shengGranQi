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

int p_ming, p_wen, p_wu, p_money, p_ti, p_level, p_year = 18;
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
            solve_de_one(newtext);
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

// ui部分

void MainWindow::add_history(QString text) {
    ui->history->append(text);
}

// 事件部分

QString level_to_name[5] = {"白丁", "", "正七品", "", "正四品"};
QString level_to_gran[5] = {"状元", "", "知县", "", "知府"};

void MainWindow::solve_de_one(QString & text) {
    p_level += 2;
    p_granjie = level_to_name[p_level];
    p_granzhi = level_to_gran[p_level];
    text += "\n\n任职期间\n颇有德行\n升为" + p_granzhi;
    ui->label_granjie->setText(p_granjie);
    ui->label_granzhi->setText(p_granzhi);
    p_ming += 1;
    ui->label_ming->setText(QString::number(p_ming));
    gailv[0] += 1;
    gailv[3] += 1;
    gailv[1] -= 2;
    ui->label_de->setText(QString::number(gailv[0]) + "%");
    ui->label_cai->setText(QString::number(gailv[1]) + "%");
    ui->label_zang->setText(QString::number(gailv[3]) + "%");
    p_year += 1;
    add_history("【" + QString::number(p_year) + "岁】任职期间，颇有德行，升为" + p_granzhi + "。");
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>
#include <QTime>
#include <QDebug>

//美化部分

QString ui_card_origin = "font-size:32px;font-family:STKaiti;background-color:qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:0.5 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));";
QString ui_card_level_1 = "font-size:32px;color:rgb(77, 77, 77);font-family:STKaiti;background-color:qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:0.5 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));";
QString ui_card_level_2 = "font-size:32px;color:rgb(0, 255, 0);font-family:STKaiti;background-color:qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:0.5 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));";
QString ui_card_level_3 = "font-size:32px;color:rgb(255, 215, 0);font-family:STKaiti;background-color:qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:0.5 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));";
QString ui_card_used = "font-size:18px;font-family:STKaiti;background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:0.2 rgba(255, 255, 255, 255), stop:0.8 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));";

//属性部分

int p_ming, p_wen, p_wu, p_money, p_ti, p_level, p_year = 18;
QString p_granjie, p_granzhi, p_name, to_add_history;
int gailv[5] = {25, 25, 25, 25, 0}, cnt[5] = {0, 0, 0, 0, 0};

//随机数

quint32 seed = quint32(QDateTime::currentDateTime().toSecsSinceEpoch());
QRandomGenerator generator(seed);
int randint(int l, int r) {
    return generator.bounded(l, r);
}

//抽卡部分

class Card {
private:
    QString text;
    int level;
    int id;
    int tid;
    QColor color;
    bool flag;
    QPushButton * ui;
public:
    Card() {}
    Card(QPushButton * _ui, int _id): ui(_ui) {
        id = _id;
        tid = -1;
        flag = false;
        update();
    }
    void chouka() {
        // 概率
        int randnum[100];
        QString num_to_name[5] = {"德", "才", "功", "脏", "运"};
        for(int i = 0, j = 0, cnt = 0; i < 100; ++i) {
            randnum[i] = j;
            ++cnt;
            if(cnt == gailv[j]) {
                ++j;
                cnt = 0;
            }
        }
        int rand = randint(0, 100);
        tid = randnum[rand];
        text = num_to_name[tid];
        ++cnt[tid];
        flag = true;
    }
    void update() {
        if(flag) {
            if(cnt[tid] >= 5) level = 3, ui->setStyleSheet(ui_card_level_3);
            else if(cnt[tid] >= 3) level = 2, ui->setStyleSheet(ui_card_level_2);
            else level = 1, ui->setStyleSheet(ui_card_level_1);
            ui->setText(text);
        } else {
            ui->setStyleSheet(ui_card_used);
            ui->setText(text);
        }
    }
    int get_tid() { return tid; }
    bool card_click();
    bool get_flag() { return flag; }
    void move() {
        //动画效果
        flag = false;
        tid = -1;
        text = "";
    }
}card[5];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    card[0] = Card(ui->card_one, 0);
    card[1] = Card(ui->card_two, 1);
    card[2] = Card(ui->card_three, 2);
    card[3] = Card(ui->card_four, 3);
    card[4] = Card(ui->card_five, 4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_one_clicked()
{
    bool flag = true;
    for(int i = 0; i < 5; ++i) if(card[i].get_flag()) flag = false;
    if(flag) {
        for(int i = 0; i < 5; ++i) card[i].move();
        card[2].chouka();
        for(int i = 0; i < 5; ++i) card[i].update();
    }
}

void MainWindow::on_pushButton_five_clicked()
{
    bool flag = true;
    for(int i = 0; i < 5; ++i) if(card[i].get_flag()) flag = false;
    if(flag) {
        for(int i = 0; i < 5; ++i) card[i].chouka();
        for(int i = 0; i < 5; ++i) card[i].update();
    }
}

//翻卡部分

bool luck = false;

QString event_choose(int, int);

bool Card::card_click() {
    if(flag) {
        int res = 0;
        QString newtext;
        if(level == 3) {
            newtext = "【" + text + "x5】";
            res = 4;
            cnt[tid] -= 5;
        } else if(level == 2) {
            newtext = "【" + text + "x3】";
            res = 2;
            cnt[tid] -= 3;
        } else {
            newtext = "【" + text + "x1】";
            cnt[tid] -= 1;
        }

        newtext += "\n\n";
        if(luck) ++level;
        newtext += event_choose(tid, level);

        for(int i = 0; i < 5; ++i)
            if(res > 0 && id != i && card[i].get_tid() == tid) {
                card[i].move();
                --res;
            }
        move();

        text = newtext;

        for(int i = 0; i < 5; ++i)
            card[i].update();
        return true;
    }
    return false;
}

void MainWindow::on_card_one_clicked()
{
    if(card[0].card_click()) updateUI();
}

void MainWindow::on_card_two_clicked()
{
    if(card[1].card_click()) updateUI();
}

void MainWindow::on_card_three_clicked()
{
    if(card[2].card_click()) updateUI();
}

void MainWindow::on_card_four_clicked()
{
    if(card[3].card_click()) updateUI();
}

void MainWindow::on_card_five_clicked()
{
    if(card[4].card_click()) updateUI();
}

// ui部分

void MainWindow::updateUI() {
    ui->label_de->setText(QString::number(gailv[0]) + "%");
    ui->label_cai->setText(QString::number(gailv[1]) + "%");
    ui->label_gong->setText(QString::number(gailv[2]) + "%");
    ui->label_zang->setText(QString::number(gailv[3]) + "%");
    ui->label_yun->setText(QString::number(gailv[4]) + "%");
    ui->label_granjie->setText(p_granjie);
    ui->label_granzhi->setText(p_granzhi);
    ui->label_suishu->setText("岁数：" + QString::number(p_year));
    ui->label_ming->setText(QString::number(p_ming));
    ui->label_wen->setText(QString::number(p_wen));
    ui->label_wu->setText(QString::number(p_wu));
    ui->label_money->setText(QString::number(p_money));
    ui->label_ti->setText(QString::number(p_ti));
    if(to_add_history != "") {
        ui->history->append(to_add_history);
        to_add_history = "";
    }
}

// 事件部分

QString level_to_name[5] = {"白丁", "", "正七品", "", "正四品"};
QString level_to_gran[5] = {"状元", "", "知县", "", "知府"};

QString solve_de_one() {
    p_level += 2;
    p_granjie = level_to_name[p_level];
    p_granzhi = level_to_gran[p_level];
    QString text = "任职期间\n颇有德行\n升为" + p_granzhi;
    p_ming += 1;
    gailv[0] += 1;
    gailv[3] += 1;
    gailv[1] -= 2;
    p_year += 1;
    to_add_history = "【" + QString::number(p_year) + "岁】任职期间，颇有德行，升为" + p_granzhi + "。";
    return text;
}

QString event_choose(int tid, int level) {
    if(level == 1 && tid == 0) return solve_de_one();
    return "";
}

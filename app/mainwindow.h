#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_one_clicked();

    void on_pushButton_five_clicked();

    int get_same_num(QString);

    QString card_click(QString, int);

    void on_card_one_clicked();

    void on_card_two_clicked();

    void on_card_three_clicked();

    void on_card_four_clicked();

    void on_card_five_clicked();

    void add_history(QString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

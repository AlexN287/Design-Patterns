#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtView.h"
#include "ITicTacToe.h"
#include <QString>

class QtView : public QMainWindow
{
    Q_OBJECT

public:
    QtView(QWidget *parent = nullptr);
    ~QtView();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

private:
    Ui::QtViewClass_game ui;
    ITicTacToePtr m_game = ITicTacToe::Produce(EgameType::Implem1);
    void GameLoop(int i, int j, QPushButton* sender);
    QString CharToQString(char c);
};

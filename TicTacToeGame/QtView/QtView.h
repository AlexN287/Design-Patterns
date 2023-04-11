#pragma once

#include <QtWidgets/QMainWindow>
#include "QtTicTacToeListener.h"
#include "ui_QtView.h"
#include "ITicTacToe.h"
#include <QString>
#include "IStrategy.h"
#include "Board.h"

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
    void on_pushButton_playerMode_clicked();
    void on_pushButton_computerMode_clicked();
    void on_pushButton_singlePlayerName_clicked();
    void on_pushButton_easy_clicked();
    void on_pushButton_medium_clicked();
    void on_pushButton_hard_clicked();

private:
    Ui::QtViewClass_game ui;
    void GameLoop(int i, int j, QPushButton* sender);
    QString CharToQString(char c);
    ITicTacToePtr m_game;
    bool computerGame = false;
    IStrategyPtr CPU;
    Board GetBoard();
    void DisableButton(std::pair<int, int> cell);
    int computerMoves = 4;

    QtTicTacToeListener listener;
};

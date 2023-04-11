#include "QtView.h"
#include <QMessageBox>
#include <String>

QtView::QtView(QWidget* parent)
    : QMainWindow(parent)
{
    m_game = ITicTacToe::Produce(EgameType::Implem1);
    m_game->AddTicTacToeListener(&listener);
    ui.setupUi(this);
    ui.stackedWidget->setCurrentIndex(0);
}

QtView::~QtView()
{}


void QtTicTacToeListener::OnGameOver(std::string playerName)
{
    QMessageBox msgBox;
    std::string aux = "PLayer ";
    aux += playerName;
    aux += " is winner";
    msgBox.setText(QString::fromStdString(aux));
    msgBox.exec();
    qApp->exit();
}

void QtTicTacToeListener::OnMakeMove(int i, int j)
{
    //not needed
}

void QtTicTacToeListener::OnTie(bool isTie)
{
    QMessageBox msgBox;
    msgBox.setText("Tie");
    msgBox.exec();
    qApp->exit();
}



void QtView::on_pushButton_clicked()
{
    m_game->SetPlayersName(ui.lineEdit_1->text().toStdString(), ui.lineEdit_2->text().toStdString());
    QString aux = QString::fromStdString(m_game->GetCurrentPlayer());
    ui.label->setText(aux);
    ui.stackedWidget->setCurrentIndex(3);
}

void QtView::on_pushButton_1_clicked()
{
    GameLoop(0, 0, ui.pushButton_1);
}

void QtView::on_pushButton_2_clicked()
{
    GameLoop(0, 1, ui.pushButton_2);
}

void QtView::on_pushButton_3_clicked()
{
    GameLoop(0, 2, ui.pushButton_3);
}

void QtView::on_pushButton_4_clicked()
{
    GameLoop(1, 0, ui.pushButton_4);
}

void QtView::on_pushButton_5_clicked()
{
    GameLoop(1, 1, ui.pushButton_5);
}

void QtView::on_pushButton_6_clicked()
{
    GameLoop(1, 2, ui.pushButton_6);
}

void QtView::on_pushButton_7_clicked()
{
    GameLoop(2, 0, ui.pushButton_7);
}

void QtView::on_pushButton_8_clicked()
{
    GameLoop(2, 1, ui.pushButton_8);
}

void QtView::on_pushButton_9_clicked()
{
    GameLoop(2, 2, ui.pushButton_9);
}

void QtView::on_pushButton_playerMode_clicked()
{
    ui.stackedWidget->setCurrentIndex(1);
}

void QtView::on_pushButton_computerMode_clicked()
{
    ui.stackedWidget->setCurrentIndex(2);
}

void QtView::on_pushButton_singlePlayerName_clicked()
{
    m_game->SetPlayersName(ui.lineEdit_singlePlayerName->text().toStdString(), "CPU");
    QString aux = QString::fromStdString(m_game->GetCurrentPlayer());
    ui.label->setText(aux);
    ui.stackedWidget->setCurrentIndex(4);
    computerGame = true;
}

void QtView::on_pushButton_easy_clicked()
{
    CPU = IStrategy::Produce(EDifficulty::Easy);
    ui.stackedWidget->setCurrentIndex(3);
}

void QtView::on_pushButton_medium_clicked()
{
    CPU = IStrategy::Produce(EDifficulty::Medium);
    ui.stackedWidget->setCurrentIndex(3);
}

void QtView::on_pushButton_hard_clicked()
{
    CPU = IStrategy::Produce(EDifficulty::Hard);
    ui.stackedWidget->setCurrentIndex(3);
}

void QtView::GameLoop(int i, int j, QPushButton* sender)
{
    m_game->NextMove(std::make_pair(i, j));
    sender->setText(CharToQString(m_game->GetValue(i, j)));
    sender->setDisabled(true);
    if (computerGame && computerMoves > 0)
    {
        computerMoves--;
        Board board = GetBoard();
        std::pair<int, int> computerMove = CPU->GetNextMove(board);
        m_game->NextMove(computerMove);
        DisableButton(computerMove);
    }
    QString aux = QString::fromStdString(m_game->GetCurrentPlayer());
    ui.label->setText(aux);
}

QString QtView::CharToQString(char c)
{
    std::string aux_string = "";
    aux_string += c;
    QString aux = QString::fromStdString(aux_string);
    return aux;
}

Board QtView::GetBoard()
{
    Board new_board;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            new_board.SetValue(m_game->GetValue(i, j), i, j);
        }
    }
    return new_board;
}

void QtView::DisableButton(std::pair<int, int> cell)
{
    int i = cell.first;
    int j = cell.second;
    if (i == 0 && j == 0)
    {
        ui.pushButton_1->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_1->setDisabled(true);
        return;
    }
    if (i == 0 && j == 1)
    {
        ui.pushButton_2->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_2->setDisabled(true);
        return;
    }
    if (i == 0 && j == 2)
    {
        ui.pushButton_3->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_3->setDisabled(true);
        return;
    }
    if (i == 1 && j == 0)
    {
        ui.pushButton_4->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_4->setDisabled(true);
        return;
    }
    if (i == 1 && j == 1)
    {
        ui.pushButton_5->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_5->setDisabled(true);
        return;
    }
    if (i == 1 && j == 2)
    {
        ui.pushButton_6->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_6->setDisabled(true);
        return;
    }
    if (i == 2 && j == 0)
    {
        ui.pushButton_7->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_7->setDisabled(true);
        return;
    }
    if (i == 2 && j == 1)
    {
        ui.pushButton_8->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_8->setDisabled(true);
        return;
    }
    if (i == 2 && j == 2)
    {
        ui.pushButton_9->setText(CharToQString(m_game->GetValue(i, j)));
        ui.pushButton_9->setDisabled(true);
        return;
    }
}


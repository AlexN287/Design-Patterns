#include "QtView.h"
#include <QMessageBox>
#include "QtTicTacToeListener.h"
#include <String>

QtView::QtView(QWidget* parent)
    : QMainWindow(parent)
{
    m_game = ITicTacToe::Produce(EgameType::Implem1);
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
    ui.stackedWidget->setCurrentIndex(1);
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

void QtView::GameLoop(int i, int j, QPushButton* sender)
{
    QtTicTacToeListener listener;
    m_game->AddTicTacToeListener(&listener);
    m_game->NextMove(std::make_pair(i, j));
    sender->setText(CharToQString(m_game->GetValue(i, j)));
    /*
    if (m_game->CheckWin() == true)
    {
        QMessageBox msgBox;
        QString aux = "PLayer ";
        aux += ui.label->text();
        aux += " is winner";
        msgBox.setText(aux);
        msgBox.exec();
        qApp->exit();
    }
    if (m_game->IsTie() == true)
    {
        QMessageBox msgBox;
        msgBox.setText("Tie");
        msgBox.exec();
        qApp->exit();
    }
    */
    QString aux = QString::fromStdString(m_game->GetCurrentPlayer());
    ui.label->setText(aux);
    m_game->RemoveTicTacToeListener(&listener);
}

QString QtView::CharToQString(char c)
{
    std::string aux_string = "";
    aux_string += c;
    QString aux = QString::fromStdString(aux_string);
    return aux;
}


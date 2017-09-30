#include "blackjack.h"
#include "ui_blackjack.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QCloseEvent>
#include <QDebug>
#include <QToolBar>
#include <QMessageBox>

BlackJack::BlackJack(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::BlackJack),
    deck() ,player(new Hand(this)), dealer(new Hand(this)),
    playerView(new HandView(player, this)),
    dealerView(new HandView(dealer, this)),
    actionGroup(new QActionGroup(this)), pScore(0), dScore(0)
{
    ui->setupUi(this);    

    actionGroup->addAction(ui->action_Deal_Hand);
    actionGroup->addAction(ui->action_Hit_ME);
    actionGroup->addAction(ui->action_New_Game);
    actionGroup->addAction(ui->action_Quit);
    actionGroup->addAction(ui->action_Stay);
    actionGroup->addAction(ui->action_Shuffle_Deck);

    ui->action_Hit_ME->setEnabled(false);
    ui->action_Stay->setEnabled(false);
    ui->action_Deal_Hand->setEnabled(false);

    QToolBar* toolbar = new QToolBar("Choice ToolBar", this);
    toolbar->addActions(actionGroup->actions());
    this->addToolBar(Qt::RightToolBarArea, toolbar);

    ui->cardPlayerLayout->addWidget(playerView);
    ui->cardDealerLayout->addWidget(dealerView);

    QObject::connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(actionEvent(QAction*)));
}

BlackJack::~BlackJack()
{
    delete ui;
}

void BlackJack::deal(){
    *player << deck.pick();
    *player << deck.pick();
    ui->spinBoxCardLeft->setValue(deck.length());
}

void BlackJack::actionEvent(QAction *event){
    QString name = event->objectName();
    qDebug() << name;

    if(name == "action_Hit_ME"){
        int playerScore;
        *player << deck.pick();
        playerScore = handScore(player);

        if(playerScore > 21){
            QMessageBox::information(this, "BlackJack", "BUSTED! You lose.");
            ui->action_Hit_ME->setEnabled(false);
            ui->action_Stay->setEnabled(false);
            if(deck.length() < 10)
                ui->action_Deal_Hand->setEnabled(false);
            else
                ui->action_Deal_Hand->setEnabled(true);
            dScore++;
            ui->labelScore->setText(QString("%1:%2").arg(dScore).arg(pScore));
        }
        ui->spinBoxCardLeft->setValue(deck.length());
    }

    if(name == "action_New_Game"){
        deck.reset();
        while ( Card* p = player->findChild<Card*>())
            delete p;
        while ( Card* d = dealer->findChild<Card*>())
            delete d;
        ui->action_Deal_Hand->setEnabled(true);
        ui->spinBoxCardLeft->setValue(deck.length());
        ui->labelDealerScore->setText("");
        ui->labelPlayerScore->setText("");
        pScore = 0;
        dScore = 0;
        ui->labelScore->setText(QString("%1:%2").arg(dScore).arg(pScore));
    }

    if(name == "action_Deal_Hand"){
        while ( Card* p = player->findChild<Card*>())
            delete p;
        while ( Card* d = dealer->findChild<Card*>())
            delete d;
        ui->labelDealerScore->setText("");
        ui->labelPlayerScore->setText("");
        deal();
        ui->action_Deal_Hand->setEnabled(false);
        ui->action_Shuffle_Deck->setEnabled(false);
        ui->action_Hit_ME->setEnabled(true);
        ui->action_Stay->setEnabled(true);
    }

    if(name == "action_Stay"){
        int playerScore = handScore(player);
        int dealerScore = 0;

        while(dealerScore < 18){
            Card* card = deck.pick();
            *dealer << card;
            dealerScore = handScore(dealer);
            ui->spinBoxCardLeft->setValue(deck.length());
        }

        ui->labelDealerScore->setText(QString("Hand score: %1").arg(dealerScore));
        ui->labelPlayerScore->setText(QString("Hand score: %1").arg(playerScore));
        QString winner = (dealerScore >= playerScore && dealerScore <= 21) ? "Dealer wins!" : "Player wins!";
        QMessageBox::information(this, "BlackJack", winner);
        if(winner == "Dealer wins!")
            dScore++;
        else
            pScore++;
        ui->labelScore->setText(QString("%1:%2").arg(dScore).arg(pScore));

        ui->action_Stay->setEnabled(false);
        ui->action_Hit_ME->setEnabled(false);
        ui->action_Shuffle_Deck->setEnabled(true);
        if(deck.length() < 10)
            ui->action_Deal_Hand->setEnabled(false);
        else
            ui->action_Deal_Hand->setEnabled(true);
    }

    if(name == "action_Shuffle_Deck"){
        deck.reset();
        while ( Card* p = player->findChild<Card*>())
            delete p;
        while ( Card* d = dealer->findChild<Card*>())
            delete d;
        ui->action_Deal_Hand->setEnabled(true);
        ui->spinBoxCardLeft->setValue(deck.length());
    }
}

void BlackJack::closeEvent(QCloseEvent *event){
    event->accept();
}

int BlackJack::handScore(Hand *hand){
    int score = 0;
    bool ace = false;
    QList<Card*> cards = hand->findChildren<Card*>();
    for(int i = 0; i < cards.length(); i++){
        score += cards.at(i)->value();
        if(cards.at(i)->isAce())
            ace = true;
    }
    if(ace && (score + 10) <= 21)
            score += 10;
    return score;
}


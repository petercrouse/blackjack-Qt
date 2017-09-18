#include "blackjack.h"
#include "ui_blackjack.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QCloseEvent>
#include <QDebug>

BlackJack::BlackJack(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::BlackJack),
    deck() ,player(new Hand(this)), dealer(new Hand(this)),
    playerView(new HandView(player, this)),
    dealerView(new HandView(dealer, this)),
    actionGroup(new QActionGroup(this))
{
    ui->setupUi(this);

    actionGroup->addAction(ui->action_Deal_Hand);
    actionGroup->addAction(ui->action_Hit_ME);
    actionGroup->addAction(ui->action_New_Game);
    actionGroup->addAction(ui->action_Quit);
    actionGroup->addAction(ui->action_Shuffle_Deck);
    actionGroup->addAction(ui->action_Stay);

    deal();

    ui->playerLayout->addWidget(playerView);
    ui->dealerLayout->addWidget(dealerView);

    QObject::connect(dealer, SIGNAL(handChanged()), dealerView, SLOT(rescanHand()));

}

BlackJack::~BlackJack()
{
    delete ui;
}

void BlackJack::deal(){
    *player << deck.pick();
    qDebug() << player->findChildren<Card*>();
    *player << deck.pick();
    qDebug() << player->findChildren<Card*>();
}

void BlackJack::actionEvent(QAction *event){
    QString name = event->objectName();
    if(name == "action_Hit_ME"){
        *player << deck.pick();
    }

}

void BlackJack::closeEvent(QCloseEvent *event){
    event->accept();
}




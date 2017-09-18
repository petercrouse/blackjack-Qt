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
        *player << deck.pick();
        ui->spinBoxCardLeft->setValue(deck.length());
    }
    if(name == "action_New_Game"){
        deck.reset();
        while ( Card* c = player->findChild<Card*>())
            delete c;
        deal();
    }

}

void BlackJack::closeEvent(QCloseEvent *event){
    event->accept();
}




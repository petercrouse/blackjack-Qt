#include "blackjack.h"
#include "ui_blackjack.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QCloseEvent>
#include <QDebug>
#include <QToolBar>

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
    actionGroup->addAction(ui->action_Stay);

    ui->action_Hit_ME->setEnabled(false);
    ui->action_Stay->setEnabled(false);
    ui->action_Deal_Hand->setEnabled(false);

    QToolBar* toolbar = new QToolBar("Choice ToolBar", this);
    toolbar->addActions(actionGroup->actions());
    this->addToolBar(Qt::RightToolBarArea, toolbar);

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
        while ( Card* p = player->findChild<Card*>())
            delete p;
        while ( Card* d = dealer->findChild<Card*>())
            delete d;
    }
    if(name == "action_Deal_Hand"){
        deal();
    }
    if(name == "Stay"){
        int score = 0;
        QList<Card*> cards = player->findChildren<Card*>();
        for(int i = 0; i < cards.length(); i++){
            score += cards.at(i)->value();
        }
    }

}

void BlackJack::closeEvent(QCloseEvent *event){
    event->accept();
}




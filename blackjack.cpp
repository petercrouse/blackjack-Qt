#include "blackjack.h"
#include "ui_blackjack.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QCloseEvent>
#include <QDebug>
#include <QToolBar>
#include <QMessageBox>
#include <QSettings>

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
    toolbar->setObjectName("choiceToolbar");
    toolbar->addActions(actionGroup->actions());
    this->addToolBar(Qt::RightToolBarArea, toolbar);

    ui->cardPlayerLayout->addWidget(playerView);
    ui->cardDealerLayout->addWidget(dealerView);

    readSettings();

    QObject::connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(actionEvent(QAction*)));
}

BlackJack::~BlackJack()
{
    delete ui;
}

void BlackJack::deal(){
    for(int i = 0; i < 2; i++){
        Card* card = deck.pick();
        drawCard(card, card->name());
        *player << card;
    }
    for(int i = 0; i < 2; i++){
        Card* card = deck.pick();
        drawCard(card, "cb");
        *dealer << card;
    }
    ui->spinBoxCardLeft->setValue(deck.length());
}

void BlackJack::actionEvent(QAction *event){
    QString name = event->objectName();

    if(name == "action_Hit_ME"){
        int playerScore;
        Card* card = deck.pick();
        drawCard(card, card->name());
        *player << card;
        playerScore = player->handValue();

        if(playerScore > 21){
            QMessageBox::information(this, "BlackJack", "BUSTED! You lose.");
            ui->action_Hit_ME->setEnabled(false);
            ui->action_Stay->setEnabled(false);
            dScore++;
        }

        if(playerScore <= 21 && player->findChildren<Card*>().length() >= 5){
            QMessageBox::information(this, "BlackJack", "Player wins!");
            ui->action_Deal_Hand->setEnabled(true);
            ui->action_Hit_ME->setEnabled(false);
            ui->action_Stay->setEnabled(false);
            pScore++;

        }

        if(deck.length() < 10)
            ui->action_Deal_Hand->setEnabled(false);
        else
            ui->action_Deal_Hand->setEnabled(true);

        ui->labelScore->setText(QString("%1:%2").arg(dScore).arg(pScore));
        ui->spinBoxCardLeft->setValue(deck.length());
    }

    if(name == "action_New_Game"){
        deck.reset();
        player->clearHand();
        dealer->clearHand();
        ui->action_Deal_Hand->setEnabled(true);
        ui->spinBoxCardLeft->setValue(deck.length());
        ui->labelDealerScore->setText("");
        ui->labelPlayerScore->setText("");
        pScore = 0;
        dScore = 0;
        ui->labelScore->setText(QString("%1:%2").arg(dScore).arg(pScore));
    }

    if(name == "action_Deal_Hand"){
        player->clearHand();
        dealer->clearHand();
        ui->labelDealerScore->setText("");
        ui->labelPlayerScore->setText("");
        deal();
        ui->action_Deal_Hand->setEnabled(false);
        ui->action_Hit_ME->setEnabled(true);
        ui->action_Stay->setEnabled(true);
    }

    if(name == "action_Stay"){
        int playerScore = player->handValue();
        int dealerScore = dealer->handValue();

        //changes cardback image of dealer to cardface
        QList<Card*> cards = dealer->findChildren<Card*>();
        for(int i = 0; i < cards.length(); i++)
            drawCard(cards.at(i), cards.at(i)->name());

        while(dealerScore < 18){
            Card* card = deck.pick();
            drawCard(card, card->name());
            *dealer << card;
            dealerScore = dealer->handValue();
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

    if(name == "action_Quit")

        QApplication::closeAllWindows();
}

void BlackJack::closeEvent(QCloseEvent *event){
    writeSettings();
    event->accept();
}

void BlackJack::drawCard(Card *card, QString name){
    QPixmap pix(QString(":/images/%1.png").arg(name));
    card->label()->setPixmap(pix);
}

void BlackJack::writeSettings() {
    /* Save postion/size of main window */
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("state", saveState());
}

void BlackJack::readSettings() {
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    QByteArray state = settings.value("state", QByteArray()).toByteArray();
    restoreState(state);
    resize(size);
    move(pos);
}

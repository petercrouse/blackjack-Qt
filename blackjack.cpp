#include "blackjack.h"
#include "ui_blackjack.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

BlackJack::BlackJack(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::BlackJack),
    deck(new Deck(this)) ,player(new Hand("player", this)),
    dealer(new Hand("dealer", this)),
    playerView(new HandView(this, player)),
    dealerView(new HandView(this, dealer))
{
    ui->setupUi(this);

}

BlackJack::~BlackJack()
{
    delete ui;
}

void BlackJack::deal(){
    *player << deck->pick();
    *player << deck->pick();
}

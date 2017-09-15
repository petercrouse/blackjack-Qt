#include "handview.h"
#include "card.h"
#include <QPixmap>
#include <QList>
#include <QLabel>
#include <QDebug>

HandView::HandView(QWidget *parent, Hand* hand) : QWidget(parent)
{
    setModel(hand);
}

void HandView::setModel(Hand *hand){
    QList<Card*> cards = hand->findChildren<Card*>();
    for(int i = 0; i < cards.length(); i++){
        QLabel* lbl = cards.at(i)->label();
        QString n = cards.at(i)->name();
        QPixmap pix(QString(":/images/%1.png").arg(n));
        lbl->setPixmap(pix);
    }
}

void HandView::rescanHand(Hand* hand){
    QList<Card*> cards = hand->findChildren<Card*>();
    for(int i = 0; i < cards.length(); i++){
        QLabel* lbl = cards.at(i)->label();
        QString n = cards.at(i)->name();
        QPixmap pix(QString(":/images/%1.png").arg(n));
        lbl->setPixmap(pix);
    }

}

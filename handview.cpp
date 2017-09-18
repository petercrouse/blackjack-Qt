#include "handview.h"
#include "card.h"
#include <QPixmap>
#include <QList>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>

HandView::HandView(Hand *hand, QWidget *parent) : QWidget(parent), m_hand(hand),
    cardView(new QVBoxLayout(this))
{
    cardView->setSpacing(1);
    for(int i = 0; i < m_hand->findChildren<Card*>().length(); i++){
        QLabel* lbl = m_hand->findChildren<Card*>().at(i)->label();
        cardView->addWidget(lbl);
    }
    this->setLayout(cardView);

    QObject::connect(m_hand, &Hand::handChanged, this, &HandView::rescanHand);
}

void HandView::setModel(Hand* hand){
    m_hand = hand;
}

void HandView::rescanHand(){
    for(int i = 0; i < m_hand->findChildren<Card*>().length(); i++){
        QLabel* lbl = m_hand->findChildren<Card*>().at(i)->label();
        cardView->addWidget(lbl);
    }
    this->setLayout(cardView);
}


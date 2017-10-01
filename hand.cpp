#include "hand.h"
#include <QDebug>

Hand::Hand(QObject *parent): QObject(parent)
{

}

Hand& Hand::operator <<(Card* card){
    card->setParent(this);
    emit handChanged();
    return *this;
}

int Hand::handValue() const {
    int score = 0;
    bool ace = false;
    QList<Card*> cards = findChildren<Card*>();
    for(int i = 0; i < cards.length(); i++){
        score += cards.at(i)->value();
        if(cards.at(i)->isAce())
            ace = true;
    }
    if(ace && (score + 10) <= 21)
            score += 10;
    return score;
}

void Hand::clearHand(){
    while (Card* c = findChild<Card*>())
        delete c;
}

#include "hand.h"
#include "card.h"

Hand::Hand(QString name, QObject* parent): QObject(parent)
{
    setObjectName(name);
}

Hand::~Hand(){

}

Hand& Hand::operator <<(Card* card){
    card->setParent(this);
    emit handChanged(this);
    return *this;
}

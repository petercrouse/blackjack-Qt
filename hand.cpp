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

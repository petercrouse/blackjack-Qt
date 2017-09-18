#ifndef HAND_H
#define HAND_H
#include "card.h"
#include <QList>
#include <QObject>

class Deck;

class Hand: public QObject
{
    Q_OBJECT
public:
    explicit Hand(QObject* parent = 0);
    Hand& operator <<(Card* card);
signals:
    void handChanged();
};

#endif // HAND_H

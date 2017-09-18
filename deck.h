#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <QTextStream>
#include <QDate>
#include <QObject>

class Deck: public QList<Card*>
{
public:
    Deck();
    ~Deck();
    void Shuffle();
    void reset();
    Card* pick();
    QString toString();
    int cardsLeft() const;
};

#endif // DECK_H

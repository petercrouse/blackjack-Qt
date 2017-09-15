#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <QTextStream>
#include <QDate>

class Deck: public QObject
{
    Q_OBJECT
public:
    explicit Deck(QObject* parent = 0);
    virtual ~Deck();
    void Shuffle();
    void reset();
    Card* pick();
    QString toString();
    int cardsLeft() const;
};

#endif // DECK_H

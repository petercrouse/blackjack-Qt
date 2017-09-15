#ifndef HAND_H
#define HAND_H
#include <QObject>

class Card;
class Deck;

class Hand: public QObject
{
    Q_OBJECT
public:
    explicit Hand(QString name, QObject* parent = 0);
    virtual ~Hand();
    Hand& operator <<(Card* card);
signals:
    void handChanged(Hand* hand);
};

#endif // HAND_H

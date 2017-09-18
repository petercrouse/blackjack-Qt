#include "deck.h"

Deck::Deck()
{
    reset();
}

Deck::~Deck()
{
    qDeleteAll(*this);
}

void Deck::Shuffle(){
    reset();
}

Card* Deck::pick()
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    int card = qrand() % this->length();
    return this->takeAt(card);
}

void Deck::reset()
{
    this->clear();
    Card* newCard;
    int suits = 4, cards = 13;
    for(int i = 0; i < suits; i++)
        for(int j = 0; j < cards; j++){
            newCard = new Card(QString("%1%2").arg(Card::sFaces.at(j)).arg(Card::sSuits.at(i)));
            this->append(newCard);
        }
}

QString Deck::toString()
{
    QString cards;
    QTextStream stream(&cards);
    for(int i = 0; i < this->length(); i++)
        stream << this->at(i)->name() << endl;
    return cards;
}

int Deck::cardsLeft() const{
    return this->length();
}

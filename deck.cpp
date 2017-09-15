#include "deck.h"

Deck::Deck(QObject* parent): QObject(parent)
{
    reset();
}

Deck::~Deck()
{

}

void Deck::Shuffle(){
    reset();
}

Card* Deck::pick()
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    int card = qrand() % this->children().length();
    return this->findChildren<Card*>().at(card);
}

void Deck::reset()
{
    Card* newCard;
    int suits = 4, cards = 13;
    for(int i = 0; i < suits; i++)
        for(int j = 0; j < cards; j++){
            newCard = new Card(QString("%1%2").arg(Card::sFaces.at(j)).arg(Card::sSuits.at(i)));
            newCard->setParent(this);
        }
}

QString Deck::toString()
{
    QString cards;
    QTextStream stream(&cards);
    for(int i = 0; i < this->findChildren<Card*>().length(); i++)
        stream << this->findChildren<Card*>().at(i)->name() << endl;
    return cards;
}

int Deck::cardsLeft() const{
    return this->findChildren<Card*>().length();
}

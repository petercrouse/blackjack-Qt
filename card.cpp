#include "card.h"
#include <QLabel>

QStringList Card::sFaces = {"a", "2", "3", "4", "5", "6", "7", "8", "9", "t", "j", "q", "k"};
QStringList Card::sSuits = {"c", "s", "h", "d"};

Card::Card(QString name): m_label(new QLabel()), m_name(name)
{

}

const QString& Card::name()
{
    return m_name;
}

QLabel* Card::label() const
{
    return m_label;
}

int Card::value() const
{
    QChar card = m_name.at(0);
    char c = card.toLatin1();
    int value;

    if (c == 't' || c == 'j' || c == 'q' || c == 'k')
        value = 10;
    else
        value = static_cast<int> (c);
    return value;
}

bool Card::isAce() const
{
    return m_name.startsWith('a', Qt::CaseInsensitive);
}

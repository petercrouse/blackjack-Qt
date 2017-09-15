#ifndef CARD_H
#define CARD_H
#include <QString>
#include <QObject>

class QLabel;

class Card: public QObject
{
    Q_OBJECT
private:
    QLabel* m_label;
    QString m_name;
public:
    Card(QString name);
    const QString& name();
    QLabel* label() const;
    int value() const;
    bool isAce() const;
    static QStringList sFaces;
    static QStringList sSuits;
};

#endif // CARD_H

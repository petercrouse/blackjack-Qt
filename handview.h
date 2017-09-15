#ifndef HANDVIEW_H
#define HANDVIEW_H
#include "hand.h"
#include <QWidget>

class QImage;
class Card;

class HandView : public QWidget
{
    Q_OBJECT
public:
    explicit HandView(QWidget *parent = nullptr, Hand* hand = 0);
    void setModel(Hand* hand);
public slots:
    void rescanHand(Hand *hand);
};

#endif // HANDVIEW_H

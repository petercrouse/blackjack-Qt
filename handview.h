#ifndef HANDVIEW_H
#define HANDVIEW_H
#include "hand.h"
#include <QWidget>

class Card;
class QVBoxLayout;

class HandView : public QWidget
{
    Q_OBJECT
public:
    explicit HandView(Hand* hand = 0, QWidget *parent = nullptr);
    void setModel(Hand* hand);
public slots:
    void rescanHand();
private:
    Hand* m_hand;
    QVBoxLayout* cardView;
};

#endif // HANDVIEW_H

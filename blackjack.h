#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "deck.h"
#include "handview.h"
#include <QMainWindow>

namespace Ui {
class BlackJack;
}

class BlackJack : public QMainWindow
{
    Q_OBJECT
public:
    explicit BlackJack(QWidget *parent = 0);
    ~BlackJack();
    void loadSettings();
//    void closeEvent(QCloseEvent *event);
    void deal();
    void actionEvent(QAction *event);
private:
    Ui::BlackJack *ui;
    Deck* deck;
    Hand* player;
    Hand* dealer;
    HandView* playerView;
    HandView* dealerView;
};

#endif // BLACKJACK_H

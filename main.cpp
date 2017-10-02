#include "blackjack.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("blackjack");
    a.setOrganizationDomain("blackjack.lol");
    a.setApplicationName("blackjack21");
    BlackJack w;
    w.show();

    return a.exec();
}

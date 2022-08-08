#include "mainsend2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSend2 w;
    w.show();

    return a.exec();
}

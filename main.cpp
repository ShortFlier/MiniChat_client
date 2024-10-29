
#include <QApplication>

#include "wapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WApplication* wapp=WApplication::getInstance();

    return a.exec();
}

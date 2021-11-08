#include "projet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    projet w;
    w.show();
    return a.exec();
}

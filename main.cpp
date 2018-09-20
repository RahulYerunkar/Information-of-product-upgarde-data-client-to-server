#include "product.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    product w;
    w.show();
    w.Connect();

    return a.exec();
}

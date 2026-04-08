#include "dummy.hpp"

// Qt
#include <QDebug>

// just for tests
int Dummy::dummy(int a, int b) {
    qDebug() << tr("This is a test");
    return a+b;
}

#ifndef DUMMY_HPP
#define DUMMY_HPP

#include <QObject>

class Dummy: QObject {
    Q_OBJECT

public:
    int dummy(int, int);
};

#endif // DUMMY_HPP

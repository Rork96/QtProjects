#ifndef TEST_MYCLASS_H
#define TEST_MYCLASS_H

#include <QObject>

class Test_MyClass : public QObject {
    Q_OBJECT
private slots:
    void min_data();
    void max_data();

    void min();
    void max();
};


#endif //TEST_MYCLASS_H

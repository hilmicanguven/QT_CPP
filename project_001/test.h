#ifndef TEST_H
#define TEST_H

#include <QObject>

#include <QDebug>

class Animal : public QObject
{
    Q_OBJECT
public:
    explicit Animal(QObject *parent = nullptr);
    ~Animal(); // Deconstructor

    void message(QString value = ""); //

signals:
};

#endif // TEST_H

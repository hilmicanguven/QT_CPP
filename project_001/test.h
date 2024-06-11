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
    int age;

    void message(QString value = ""); //
    void setAge(int age);

signals:
};

#endif // TEST_H

#ifndef LIBRARYINVENTORY_H
#define LIBRARYINVENTORY_H

#include <QObject>
#include <QMap> /* library items holds as QMap*/
#include <QDebug>
#include <QFile>
#include <QDataStream>

class LibraryInventory : public QObject
{
    Q_OBJECT
public:
    explicit LibraryInventory(QObject *parent = nullptr);

    void addBook(QString name, int quantity);
    void removeBook(QString name, int quantity);
    void listBooks();

signals:

public slots:
    void saveInventory();
    void loadInventory();

private:
    QMap<QString, int> library_items;
};

#endif // LIBRARYINVENTORY_H

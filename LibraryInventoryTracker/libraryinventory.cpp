#include "libraryinventory.h"

LibraryInventory::LibraryInventory(QObject *parent) : QObject{parent}
{
    /* int constructure, library inventory tracker is loaded automatically */
    // we can call slots as normal function because of MOC-meta-object-compilers
    loadInventory();
}

void LibraryInventory::addBook(QString name, int quantity)
{
    if(library_items.contains(name))
    {
        /* increase number of existince ones*/
        library_items[name] += quantity;
    }
    else
    {
        /* first time it is added */
        library_items.insert(name,quantity);
    }

}

void LibraryInventory::removeBook(QString name, int quantity)
{
    if(library_items.contains(name))
    {
        library_items[name] -= quantity;
        if(library_items.value(name) < 0) library_items.remove(name);
        qInfo() << "Item removed";
    }
    else
    {
        qWarning() << "No item of that name!";;
    }

}

void LibraryInventory::listBooks()
{
    qInfo() << "Items:" << library_items.size();
    foreach(QString key, library_items.keys())
    {
        qInfo()<< "Book: " << key << " = " << library_items.value(key);
    }

}

void LibraryInventory::saveInventory()
{
    QFile file("libraryInventory.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not save file:" << file.errorString();
        return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_0);

    int len = library_items.size();
    stream << len;

    qInfo() << "Number of items to save:" << len;

    foreach(QString key, library_items.keys())
    {
        qInfo() << "Saving:" << key;
        stream << key;
        stream << library_items.value(key);
    }

    file.close();

    qInfo() << "File saved";
}

void LibraryInventory::loadInventory()
{
    QFile file("libraryInventory.txt");

    if(!file.exists())
    {
        qWarning() << "File does not exist!";
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not open file:" << file.errorString();
        return;
    }

    // put the data to file in an encoded
    QDataStream stream(&file);
    if(stream.version() != QDataStream::Qt_6_0)
    {
        qCritical() << "Wrong data stream version!";
        file.close();
        return;
    }

    // clear previous library inventory
    library_items.clear();

    int max;
    // first data is number of items in inventory because
    // we first write number of items when we stored to file
    stream >> max;

    qInfo() << "Number of items to load:" << max;

    for(int i = 0; i < max; i ++)
    {
        QString key;
        int qty;
        stream >> key;
        stream >> qty;
        library_items.insert(key,qty);
    }

    file.close();

    qInfo() << "File loaded";
}

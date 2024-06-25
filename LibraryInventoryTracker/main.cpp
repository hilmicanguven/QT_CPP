/*

Simple Library inventory tracker application

Make a class for library inventory

*/

#include <QCoreApplication>
#include <QTextStream>
#include "libraryinventory.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LibraryInventory libraryInventory;

    qInfo() << "Available commands:";
    qInfo() << "add <name> <qty>";
    qInfo() << "remove <name> <qty>";
    qInfo() << "save";
    qInfo() << "load";
    qInfo() << "list";
    qInfo() << "quit";

    QTextStream stream(stdin);

    while(true)
    {
        qInfo() << "Enter a command:";
        QString line = stream.readLine();
        QStringList list = line.split(" ");
        if(list.size() <= 0) break;

        QString command = list.at(0).toUpper();
        if(command == "QUIT")
        {
            //a.exit(0);
            break;
        }

        if(command == "LIST") libraryInventory.listBooks();
        if(command == "LOAD") libraryInventory.loadInventory();
        if(command == "SAVE") libraryInventory.saveInventory();

        if(command == "ADD" || command == "REMOVE")
        {
            if(list.size() < 3)
            {
                qWarning() << "Not enough info";
                continue;
            }

            QString name = list.at(1);
            bool ok;
            int qty;
            qty = list.at(2).toInt(&ok);
            if(!ok)
            {
                qWarning() << "Invalid quantity!";
                continue;
            }

            if(command == "ADD") libraryInventory.addBook(name,qty);
            if(command == "REMOVE") libraryInventory.removeBook(name,qty);

        }

    }

    libraryInventory.saveInventory();
    qInfo() << "Complete";

    //return a.exec();

    return 0;
}

#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

#include "test.h"
#include <QTimer>

#include <QScopedPointer>

#include <iostream>

//Setting in the constuctor
Animal* getAnimal(QObject* parent)
{
    return new Animal(parent);
}

//Setting up after constuctor
Animal* getAnimalWithoutParent()
{
    return new Animal(); //No parent is given
}

//Get a list of pointers
typedef QList<Animal*> AnimalList;

AnimalList getAnimalList(int animal_count)
{
    AnimalList list;
    for(int i = 0 ; i < animal_count; i++)
    {
        list.append(new Animal());
        list.last()->setObjectName("Animal Number: " + QString::number(animal_count));
    }

    return list;
}

//Display Animals List
void displayAnimalList( AnimalList list)
{
    foreach(Animal* animal, list)
    {
        qInfo() << animal;
    }
}



void AnimalStop(QSharedPointer<Animal> ptr)
{
    ptr->message("Animal is stopping");
}

void AnimalWalk(QSharedPointer<Animal> ptr)
{
    ptr->message("Animal is walking");
    AnimalStop(ptr);
}

void AnimalRun(QSharedPointer<Animal> ptr)
{
    ptr->message("Animal is running");
    AnimalWalk(ptr);
}

void AnimalShared(Animal* animal)
{
    QSharedPointer<Animal> ptr (animal);
    ptr->message("Animal Sport is starting");
    AnimalRun(ptr);
    // The ptr
}

void AnimalScoped()
{
    QScopedPointer<Animal> ptr (new Animal());
    ptr->message("Hello from Scoped Pointer");


    //ptr will be deleted at that point
}

int main(int argc, char *argv[])
{
    /* QCoreApplication object 'a' is also QObject */
    QCoreApplication a(argc, argv);

    qInfo() << "Program starts...\n";

    QTimer timer;
    timer.singleShot(1000, &a, &QCoreApplication::quit);

    /* Set Parent during class init/contruction*/
//    Animal* mammal = getAnimal(&a);
//    mammal->setObjectName("Mammal Animal");
    /* This dog class is deleted when main program is finished
     * because it is parent of Animal class */

    /* In this case, parent is set in different way */
//    Animal* cat = getAnimalWithoutParent();
//    cat->setObjectName("Cat Type");
//    cat->setParent(mammal);
    /* This cat class is also deleted because its
     * parent is deleted when &a is deleted */

//    Animal* whale = getAnimalWithoutParent();
//    whale->setObjectName("Blue Whale");
//    whale->setParent(mammal);

//    qInfo() << "Animal List Created...";

    // AnimalList list = getAnimalList(5);
    // displayAnimalList(list);
    // //qDeleteAll(list); //delete entire list
    // qDeleteAll(list.begin(), list.end()); //delete entire list
    // list.clear();//delete list, otherwise program will crashed brcause of bad pointer
    // displayAnimalList(list);
    // qInfo() << "Animal List Deleted ...\n\n";

//    qInfo() << "Scoped Pointers ...";
//    AnimalScoped();

//    qInfo() << "Shared Pointers ...";
    // AnimalShared(new Animal());

//------QString object creating-------
    // QString line("This is a string ");
    // qInfo() << line;

    // QString name = "Hilmi Guven";
    // qInfo() << name;

    // int progress = 100;
    // int total = 200;
    // QString bar = QString("Progress Bar: %1/%2").arg(progress).arg(total);
    // qInfo() << bar;
//------QString object creating-------

//------QString Reading Each Char-------
    // for(int i=0; i < name.length(); i++)
    // {
    //     QChar character = name.at(i);
    //     qInfo() << character;
    // }
//------QString Reading Each Char-------

//------Comparing & Searching-------
    // qInfo() << "Comparison R/*esult" << name.compare("Name Surname", Qt::CaseSensitivity::CaseSensitive);
    // qInfo() << "is String start with ...?"  << name.startsWith("Hilmi", Qt::CaseSensitivity::CaseSensitive);
    // qInfo() << "is String end with ...?"  << name.endsWith("Guven", Qt::CaseSensitivity::CaseSensitive);
    // qInfo() << "is String contains ...?"  << name.contains("mi Gu");
    // qInfo() << "index of string ...*/?"  << name.indexOf("Guven");
//------Comparing & Searching-------

//------Modify & Parsing-------

//------Modify & Parsing-------

//------Conversion------
    // std::cout << "std-> " << name.toStdString() << std::endl;

    // qInfo() << "UTF8 " << name.toUtf8();
    // qInfo() << "Base64 " << name.toUtf8().toBase64();
    // qInfo() << "Hex " << name.toUtf8().toHex();

//-----QByte Array-----

    QByteArray stuff;
    qInfo() << stuff;   //Empty String

    QByteArray data("Byte Array with Data");
    qInfo() << data;

    QByteArray buffer(10, '-');
    qInfo() << buffer;

    QByteArray person(QString("Hilmi").toLocal8Bit()); // we need to specific type
    qInfo() << person;

    //Sizing the array
    data.reserve(25); //reserve memory for array in size of byte, i.e.25
    data.resize(15); //resize the size of array
    data.truncate(10);//it chops the array. if size is larger than truncate, it gets smaller
    data.clear();//clear and make null

    //modifying/reading/encoding the array
    data.resize(10);
    data.fill('a');

    int first = data.indexOf('a');
    int last = data.lastIndexOf('a');
    int random = data.at(3);

    foreach(auto item, data.split(' '))
    {
        //item
    }


    int value = a.exec();
    qInfo() << "Program end with Exit Code: " << value;

/** @note QString is not QObject!!!
 *  We can not copy QObject during passing function as argument
 *  bu we can copy QStrings can be copied
*/







    return value;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "project_001_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    return a.exec();
}

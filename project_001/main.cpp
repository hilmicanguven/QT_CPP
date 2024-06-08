#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

#include "test.h"
#include <QTimer>

#include <QScopedPointer>


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

    AnimalList list = getAnimalList(5);
    displayAnimalList(list);
    //qDeleteAll(list); //delete entire list
    qDeleteAll(list.begin(), list.end()); //delete entire list
    list.clear();//delete list, otherwise program will crashed brcause of bad pointer
    displayAnimalList(list);
    qInfo() << "Animal List Deleted ...\n\n";

//    qInfo() << "Scoped Pointers ...";
//    AnimalScoped();

//    qInfo() << "Shared Pointers ...";
    AnimalShared(new Animal());

    int value = a.exec();
    qInfo() << "Exit Code: " << value;









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

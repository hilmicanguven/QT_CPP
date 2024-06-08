#include "test.h"

/**
 * @brief Animal::Animal Constructure
 * @param parent
 */
Animal::Animal(QObject *parent) : QObject{parent}
{
    qInfo() << this << "Constructed" << parent;
}

/**
 * @brief Animal::~Animal Desconsructor
 */
Animal::~Animal()
{
    foreach (QObject* child, children())
    {
        qInfo() << this << "Child: " << child << "Deconstructued";
    }

    qInfo() << this << "De-Constructed" << parent();
}

void Animal::message(QString value)
{
    qInfo() << this << value;
}

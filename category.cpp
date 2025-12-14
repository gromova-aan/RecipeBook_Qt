#include "category.h"

Category::Category(const QString& name)
    : m_name(name)
{
}

QString Category::getName() const
{
    return m_name;
}

void Category::setName(const QString& name)
{
    m_name = name;
}

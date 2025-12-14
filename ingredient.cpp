#include "ingredient.h"

Ingredient::Ingredient(const QString& name, const QString& quantity)
    : m_name(name), m_quantity(quantity)
{
}

QString Ingredient::getName() const
{
    return m_name;
}

void Ingredient::setName(const QString& name)
{
    m_name = name;
}

QString Ingredient::getQuantity() const
{
    return m_quantity;
}

void Ingredient::setQuantity(const QString& quantity)
{
    m_quantity = quantity;
}

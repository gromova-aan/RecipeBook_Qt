#include "user.h"

User::User(const QString& name)
    : m_name(name)
{
}

QString User::getName() const
{
    return m_name;
}

void User::setName(const QString& name)
{
    m_name = name;
}

QList<Recipe> User::getRecipes() const
{
    return m_recipes;
}

void User::setRecipes(const QList<Recipe>& recipes)
{
    m_recipes = recipes;
}

void User::addRecipe(const Recipe& recipe)
{
    m_recipes.append(recipe);
}

void User::removeRecipe(int index)
{
    if (index >= 0 && index < m_recipes.size()) {
        m_recipes.removeAt(index);
    }
}







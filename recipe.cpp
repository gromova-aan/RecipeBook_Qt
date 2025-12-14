#include "recipe.h"

Recipe::Recipe(const QString& title)
    : m_title(title), m_isFavorite(false)
{
}

QString Recipe::getTitle() const
{
    return m_title;
}

void Recipe::setTitle(const QString& title)
{
    m_title = title;
}

QString Recipe::getImagePath() const
{
    return m_imagePath;
}

void Recipe::setImagePath(const QString& path)
{
    m_imagePath = path;
}

QList<Ingredient> Recipe::getIngredients() const
{
    return m_ingredients;
}

void Recipe::setIngredients(const QList<Ingredient>& ingredients)
{
    m_ingredients = ingredients;
}

void Recipe::addIngredient(const Ingredient& ingredient)
{
    m_ingredients.append(ingredient);
}

QStringList Recipe::getSteps() const
{
    return m_steps;
}

void Recipe::setSteps(const QStringList& steps)
{
    m_steps = steps;
}

void Recipe::addStep(const QString& step)
{
    m_steps.append(step);
}

QTime Recipe::getCookingTime() const
{
    return m_cookingTime;
}

void Recipe::setCookingTime(const QTime& time)
{
    m_cookingTime = time;
}

Category Recipe::getCategory() const
{
    return m_category;
}

void Recipe::setCategory(const Category& category)
{
    m_category = category;
}

bool Recipe::isFavorite() const
{
    return m_isFavorite;
}

void Recipe::setFavorite(bool favorite)
{
    m_isFavorite = favorite;
}

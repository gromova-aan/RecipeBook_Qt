#include "recipetemplate.h"

RecipeTemplate::RecipeTemplate()
    : m_cookingTime(0, 30) // 30 минут по умолчанию
{
}

RecipeTemplate::RecipeTemplate(const QString& name, const Category& category,
                              const QList<Ingredient>& ingredients, const QStringList& steps,
                              const QTime& cookingTime)
    : m_name(name), m_category(category), m_ingredients(ingredients), m_steps(steps), m_cookingTime(cookingTime)
{
}

QString RecipeTemplate::getName() const
{
    return m_name;
}

Category RecipeTemplate::getCategory() const
{
    return m_category;
}

QList<Ingredient> RecipeTemplate::getIngredients() const
{
    return m_ingredients;
}

QStringList RecipeTemplate::getSteps() const
{
    return m_steps;
}

QTime RecipeTemplate::getCookingTime() const
{
    return m_cookingTime;
}

void RecipeTemplate::setName(const QString& name)
{
    m_name = name;
}

void RecipeTemplate::setCategory(const Category& category)
{
    m_category = category;
}

void RecipeTemplate::setIngredients(const QList<Ingredient>& ingredients)
{
    m_ingredients = ingredients;
}

void RecipeTemplate::setSteps(const QStringList& steps)
{
    m_steps = steps;
}

void RecipeTemplate::setCookingTime(const QTime& cookingTime)
{
    m_cookingTime = cookingTime;
}

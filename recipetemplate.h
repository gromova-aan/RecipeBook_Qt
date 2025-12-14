#ifndef RECIPETEMPLATE_H
#define RECIPETEMPLATE_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QTime>
#include "category.h"
#include "ingredient.h"

class RecipeTemplate
{
public:
    RecipeTemplate();
    RecipeTemplate(const QString& name, const Category& category,
                  const QList<Ingredient>& ingredients, const QStringList& steps,
                  const QTime& cookingTime = QTime(0, 30)); // 30 минут по умолчанию

    QString getName() const;
    Category getCategory() const;
    QList<Ingredient> getIngredients() const;
    QStringList getSteps() const;
    QTime getCookingTime() const;

    void setName(const QString& name);
    void setCategory(const Category& category);
    void setIngredients(const QList<Ingredient>& ingredients);
    void setSteps(const QStringList& steps);
    void setCookingTime(const QTime& cookingTime);

private:
    QString m_name;
    Category m_category;
    QList<Ingredient> m_ingredients;
    QStringList m_steps;
    QTime m_cookingTime;
};

#endif // RECIPETEMPLATE_H

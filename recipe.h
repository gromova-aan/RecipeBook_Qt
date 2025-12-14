#ifndef RECIPE_H
#define RECIPE_H

#include <QString>
#include <QList>
#include <QTime>
#include "ingredient.h"
#include "category.h"

class Recipe
{
public:
    Recipe(const QString& title = "");

    QString getTitle() const;
    void setTitle(const QString& title);

    QString getImagePath() const;
    void setImagePath(const QString& path);

    QList<Ingredient> getIngredients() const;
    void setIngredients(const QList<Ingredient>& ingredients);
    void addIngredient(const Ingredient& ingredient);

    QStringList getSteps() const;
    void setSteps(const QStringList& steps);
    void addStep(const QString& step);

    QTime getCookingTime() const;
    void setCookingTime(const QTime& time);

    Category getCategory() const;
    void setCategory(const Category& category);

    bool isFavorite() const;
    void setFavorite(bool favorite);

private:
    QString m_title;
    QString m_imagePath;
    QList<Ingredient> m_ingredients;
    QStringList m_steps;
    QTime m_cookingTime;
    Category m_category;
    bool m_isFavorite;
};

#endif // RECIPE_H

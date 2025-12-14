#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include "recipe.h"

class User
{
public:
    User(const QString& name = "");

    QString getName() const;
    void setName(const QString& name);

    QList<Recipe> getRecipes() const;
    void setRecipes(const QList<Recipe>& recipes);
    void addRecipe(const Recipe& recipe);
    void removeRecipe(int index);

private:
    QString m_name;
    QList<Recipe> m_recipes;
};

#endif // USER_H







#ifndef RECIPEFILTER_H
#define RECIPEFILTER_H

#include "recipe.h"
#include <QList>

class RecipeFilter
{
public:
    virtual ~RecipeFilter() = default;
    virtual QList<Recipe> filter(const QList<Recipe>& recipes) const = 0;
    virtual QString getName() const = 0;
};

#endif // RECIPEFILTER_H

#ifndef RECIPEFACTORY_H
#define RECIPEFACTORY_H

#include "recipe.h"
#include "category.h"

class RecipeFactory
{
public:
    static Recipe createEmptyRecipe();
    static Recipe createRecipeFromTemplate(const QString& templateName);
    static Recipe createDessertRecipe(const QString& name);
    static Recipe createMainCourseRecipe(const QString& name);

private:
    RecipeFactory() = delete;
};

#endif // RECIPEFACTORY_H

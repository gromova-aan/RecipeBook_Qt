#include "recipefactory.h"

Recipe RecipeFactory::createEmptyRecipe()
{
    return Recipe("Новый рецепт");
}

Recipe RecipeFactory::createRecipeFromTemplate(const QString& templateName)
{
    if (templateName == "Десерт") {
        return createDessertRecipe("Новый десерт");
    } else if (templateName == "Основное блюдо") {
        return createMainCourseRecipe("Новое основное блюдо");
    }

    return createEmptyRecipe();
}

Recipe RecipeFactory::createDessertRecipe(const QString& name)
{
    Recipe recipe(name);
    recipe.setCategory(Category("Десерт"));

    // Добавляем стандартные ингредиенты для десерта
    recipe.addIngredient(Ingredient("Сахар", "по вкусу"));
    recipe.addIngredient(Ingredient("Мука", "200 г"));

    // Добавляем стандартные шаги
    recipe.addStep("Подготовить ингредиенты");
    recipe.addStep("Смешать все компоненты");
    recipe.addStep("Выпекать до готовности");

    return recipe;
}

Recipe RecipeFactory::createMainCourseRecipe(const QString& name)
{
    Recipe recipe(name);
    recipe.setCategory(Category("Второе"));

    // Добавляем стандартные ингредиенты для основного блюда
    recipe.addIngredient(Ingredient("Соль", "по вкусу"));
    recipe.addIngredient(Ingredient("Перец", "по вкусу"));
    recipe.addIngredient(Ingredient("Масло растительное", "2 ст.л."));

    // Добавляем стандартные шаги
    recipe.addStep("Подготовить продукты");
    recipe.addStep("Обжарить основные ингредиенты");
    recipe.addStep("Довести до готовности");

    return recipe;
}

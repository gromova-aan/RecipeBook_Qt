#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>
#include <QDir>
#include "recipe.h"
#include "user.h"

class DataManager
{
public:
    static DataManager& getInstance();

    // Методы для работы с рецептами (для обратной совместимости)
    bool saveRecipes(const QList<Recipe>& recipes);
    QList<Recipe> loadRecipes();

    // Новые методы для работы с пользователями
    bool saveUserRecipes(const QString& userName, const QList<Recipe>& recipes);
    QList<Recipe> loadUserRecipes(const QString& userName);

    bool exportRecipes(const QList<Recipe>& recipes, const QString& filename);
    QList<Recipe> importRecipes(const QString& filename);

    QString getDataFilePath();
    QString getUserDataFilePath(const QString& userName);

private:
    DataManager();
    ~DataManager() = default;
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

    // Приватные методы для работы с файлами
    bool saveToFile(const QList<Recipe>& recipes, const QString& filename);
    QList<Recipe> loadFromFile(const QString& filename);

    QJsonObject recipeToJson(const Recipe& recipe);
    Recipe jsonToRecipe(const QJsonObject& json);

    QJsonObject ingredientToJson(const Ingredient& ingredient);
    Ingredient jsonToIngredient(const QJsonObject& json);

    QJsonObject categoryToJson(const Category& category);
    Category jsonToCategory(const QJsonObject& json);
};

#endif // DATAMANAGER_H

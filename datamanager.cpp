#include "datamanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QStandardPaths>
#include <QFileInfo>

DataManager& DataManager::getInstance()
{
    static DataManager instance;
    return instance;
}

DataManager::DataManager()
{
    // Создаем папку для данных при первом использовании
    QDir dir;
    dir.mkpath(QFileInfo(getDataFilePath()).absolutePath());
}

QString DataManager::getDataFilePath()
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (dataDir.isEmpty()) {
        dataDir = QDir::currentPath();
    }
    return dataDir + "/recipes.json";
}

QString DataManager::getUserDataFilePath(const QString& userName)
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (dataDir.isEmpty()) {
        dataDir = QDir::currentPath();
    }
    // Создаем безопасное имя файла из имени пользователя
    QString safeUserName = userName;
    // Заменяем все небуквенно-цифровые символы на подчеркивание
    for (int i = 0; i < safeUserName.length(); ++i) {
        if (!safeUserName[i].isLetterOrNumber()) {
            safeUserName[i] = '_';
        }
    }
    return dataDir + "/user_" + safeUserName + "_recipes.json";
}

bool DataManager::saveRecipes(const QList<Recipe>& recipes)
{
    return saveToFile(recipes, getDataFilePath());
}

QList<Recipe> DataManager::loadRecipes()
{
    return loadFromFile(getDataFilePath());
}

bool DataManager::exportRecipes(const QList<Recipe>& recipes, const QString& filename)
{
    return saveToFile(recipes, filename);
}

QList<Recipe> DataManager::importRecipes(const QString& filename)
{
    return loadFromFile(filename);
}

bool DataManager::saveUserRecipes(const QString& userName, const QList<Recipe>& recipes)
{
    QString filePath = getUserDataFilePath(userName);
    // Создаем папку для данных пользователя
    QDir dir;
    dir.mkpath(QFileInfo(filePath).absolutePath());
    return saveToFile(recipes, filePath);
}

QList<Recipe> DataManager::loadUserRecipes(const QString& userName)
{
    QString filePath = getUserDataFilePath(userName);
    return loadFromFile(filePath);
}

bool DataManager::saveToFile(const QList<Recipe>& recipes, const QString& filename)
{
    QJsonArray recipesArray;

    for (const Recipe& recipe : recipes) {
        recipesArray.append(recipeToJson(recipe));
    }

    QJsonObject rootObject;
    rootObject["version"] = "1.0";
    rootObject["recipes"] = recipesArray;

    QJsonDocument doc(rootObject);

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Не удалось открыть файл для записи:" << filename;
        return false;
    }

    file.write(doc.toJson());
    file.close();
    qDebug() << "Рецепты сохранены в:" << filename;
    return true;
}

QList<Recipe> DataManager::loadFromFile(const QString& filename)
{
    QList<Recipe> recipes;

    QFile file(filename);
    if (!file.exists()) {
        qDebug() << "Файл с рецептами не существует, будет создан новый:" << filename;
        return recipes;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл для чтения:" << filename;
        return recipes;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qWarning() << "Неверный JSON формат в файле:" << filename;
        return recipes;
    }

    QJsonObject rootObject = doc.object();
    QJsonArray recipesArray = rootObject["recipes"].toArray();

    for (const QJsonValue& value : recipesArray) {
        Recipe recipe = jsonToRecipe(value.toObject());
        recipes.append(recipe);
    }

    qDebug() << "Загружено рецептов:" << recipes.size();
    return recipes;
}

QJsonObject DataManager::recipeToJson(const Recipe& recipe)
{
    QJsonObject json;
    json["title"] = recipe.getTitle();
    json["imagePath"] = recipe.getImagePath();
    json["cookingTime"] = recipe.getCookingTime().toString("hh:mm");
    json["isFavorite"] = recipe.isFavorite();

    // Категория
    json["category"] = categoryToJson(recipe.getCategory());

    // Ингредиенты
    QJsonArray ingredientsArray;
    for (const Ingredient& ingredient : recipe.getIngredients()) {
        ingredientsArray.append(ingredientToJson(ingredient));
    }
    json["ingredients"] = ingredientsArray;

    // Шаги приготовления
    QJsonArray stepsArray;
    for (const QString& step : recipe.getSteps()) {
        stepsArray.append(step);
    }
    json["steps"] = stepsArray;

    return json;
}

Recipe DataManager::jsonToRecipe(const QJsonObject& json)
{
    Recipe recipe(json["title"].toString());
    recipe.setImagePath(json["imagePath"].toString());
    recipe.setCookingTime(QTime::fromString(json["cookingTime"].toString(), "hh:mm"));
    recipe.setFavorite(json["isFavorite"].toBool());
    recipe.setCategory(jsonToCategory(json["category"].toObject()));

    // Ингредиенты
    QJsonArray ingredientsArray = json["ingredients"].toArray();
    QList<Ingredient> ingredients;
    for (const QJsonValue& value : ingredientsArray) {
        ingredients.append(jsonToIngredient(value.toObject()));
    }
    recipe.setIngredients(ingredients);

    // Шаги приготовления
    QJsonArray stepsArray = json["steps"].toArray();
    QStringList steps;
    for (const QJsonValue& value : stepsArray) {
        steps.append(value.toString());
    }
    recipe.setSteps(steps);

    return recipe;
}

QJsonObject DataManager::ingredientToJson(const Ingredient& ingredient)
{
    QJsonObject json;
    json["name"] = ingredient.getName();
    json["quantity"] = ingredient.getQuantity();
    return json;
}

Ingredient DataManager::jsonToIngredient(const QJsonObject& json)
{
    return Ingredient(json["name"].toString(), json["quantity"].toString());
}

QJsonObject DataManager::categoryToJson(const Category& category)
{
    QJsonObject json;
    json["name"] = category.getName();
    return json;
}

Category DataManager::jsonToCategory(const QJsonObject& json)
{
    return Category(json["name"].toString());
}

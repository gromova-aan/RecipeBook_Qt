#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recipedialog.h"
#include "recipefactory.h"
#include "favouritesmanager.h"
#include "datamanager.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent, const QString& userName)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_userName(userName)
    , m_showingFavorites(false)
{
    ui->setupUi(this);

    // Устанавливаем заголовок с именем пользователя
    if (!m_userName.isEmpty()) {
        setWindowTitle(QString("Книга рецептов - %1").arg(m_userName));
    }

    // Включаем контекстное меню
    ui->recipesListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->recipesListWidget, &QListWidget::customContextMenuRequested,
            this, &MainWindow::showContextMenu);

    // Загружаем рецепты пользователя при запуске
    if (!m_userName.isEmpty()) {
        m_recipes = DataManager::getInstance().loadUserRecipes(m_userName);
    } else {
        // Для обратной совместимости, если имя пользователя не указано
        m_recipes = DataManager::getInstance().loadRecipes();
    }

    updateRecipesList();

    connect(ui->recipesListWidget, &QListWidget::currentRowChanged,
            this, &MainWindow::on_recipesListWidget_currentRowChanged);
    connect(ui->timeFilterComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::on_timeFilterComboBox_currentTextChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Сохраняем рецепты при закрытии приложения
    if (!m_userName.isEmpty()) {
        DataManager::getInstance().saveUserRecipes(m_userName, m_recipes);
    } else {
        // Для обратной совместимости
        DataManager::getInstance().saveRecipes(m_recipes);
    }
    event->accept();
}

void MainWindow::on_addRecipeButton_clicked()
{
    RecipeDialog dialog(this);
    Recipe newRecipe = RecipeFactory::createEmptyRecipe();
    dialog.setRecipe(newRecipe);

    if (dialog.exec() == QDialog::Accepted) {
        Recipe recipe = dialog.getRecipe();
        m_recipes.append(recipe);
        updateRecipesList();

        if (recipe.isFavorite()) {
            FavouritesManager::getInstance().addToFavorites(recipe);
        }

        // Автосохранение при добавлении рецепта
        if (!m_userName.isEmpty()) {
            DataManager::getInstance().saveUserRecipes(m_userName, m_recipes);
        } else {
            DataManager::getInstance().saveRecipes(m_recipes);
        }
    }
}

void MainWindow::on_favoritesButton_clicked()
{
    m_showingFavorites = !m_showingFavorites;
    m_favoritesFilter.setShowOnlyFavorites(m_showingFavorites);

    if (m_showingFavorites) {
        ui->favoritesButton->setText("Все рецепты");
    } else {
        ui->favoritesButton->setText("⭐ Избранное");
    }

    applyFilters();
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    applyFilters();
}

void MainWindow::on_categoryComboBox_currentTextChanged(const QString &text)
{
    m_categoryFilter.setCategory(text);
    applyFilters();
}

void MainWindow::on_recipesListWidget_currentRowChanged(int currentRow)
{
    if (currentRow >= 0 && currentRow < m_filteredRecipes.size()) {
        showRecipeDetails(m_filteredRecipes[currentRow]);
    }
}

void MainWindow::on_actionImport_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Импорт рецептов", "", "JSON Files (*.json)");

    if (!fileName.isEmpty()) {
        QList<Recipe> importedRecipes = DataManager::getInstance().importRecipes(fileName);
        if (!importedRecipes.isEmpty()) {
            m_recipes.append(importedRecipes);
            updateRecipesList();
            if (!m_userName.isEmpty()) {
                DataManager::getInstance().saveUserRecipes(m_userName, m_recipes);
            } else {
                DataManager::getInstance().saveRecipes(m_recipes);
            } // Сохраняем объединенный список
            QMessageBox::information(this, "Импорт",
                                     QString("Успешно импортировано %1 рецептов").arg(importedRecipes.size()));
        } else {
            QMessageBox::warning(this, "Импорт", "Не удалось импортировать рецепты");
        }
    }
}

void MainWindow::on_actionExport_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Экспорт рецептов", "recipes_export.json", "JSON Files (*.json)");

    if (!fileName.isEmpty()) {
        if (DataManager::getInstance().exportRecipes(m_recipes, fileName)) {
            QMessageBox::information(this, "Экспорт", "Рецепты успешно экспортированы");
        } else {
            QMessageBox::warning(this, "Экспорт", "Не удалось экспортировать рецепты");
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    bool success;
    if (!m_userName.isEmpty()) {
        success = DataManager::getInstance().saveUserRecipes(m_userName, m_recipes);
    } else {
        success = DataManager::getInstance().saveRecipes(m_recipes);
    }

    if (success) {
        QMessageBox::information(this, "Сохранение", "Рецепты успешно сохранены");
    } else {
        QMessageBox::warning(this, "Сохранение", "Не удалось сохранить рецепты");
    }
}

void MainWindow::on_actionLoad_triggered()
{
    if (QMessageBox::question(this, "Загрузка",
                              "Загрузить сохраненные рецепты? Текущие данные будут потеряны.") == QMessageBox::Yes) {

        QList<Recipe> loadedRecipes;
        if (!m_userName.isEmpty()) {
            loadedRecipes = DataManager::getInstance().loadUserRecipes(m_userName);
        } else {
            loadedRecipes = DataManager::getInstance().loadRecipes();
        }
        if (!loadedRecipes.isEmpty()) {
            m_recipes = loadedRecipes;
            updateRecipesList();
            QMessageBox::information(this, "Загрузка",
                                     QString("Успешно загружено %1 рецептов").arg(loadedRecipes.size()));
        } else {
            QMessageBox::information(this, "Загрузка", "Нет сохраненных рецептов");
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::updateRecipesList()
{
    applyFilters();
}

void MainWindow::showRecipeDetails(const Recipe& recipe)
{
    QString details;
    details += QString("<h1>%1</h1>").arg(recipe.getTitle());
    details += QString("<p><b>Категория:</b> %1</p>").arg(recipe.getCategory().getName());

    if (recipe.getCookingTime().isValid() && !recipe.getCookingTime().isNull()) {
        details += QString("<p><b>Время приготовления:</b> %1</p>").arg(recipe.getCookingTime().toString("hh:mm"));
    }

    if (recipe.isFavorite()) {
        details += "<p><b>⭐ В избранном</b></p>";
    }

    // Отображаем изображение вместо пути
    if (!recipe.getImagePath().isEmpty()) {
        details += QString("<p style=\"text-align: center;\"><img src=\"%1\" style=\"max-width:300px; max-height:300px; display: block; margin: 0 auto;\"/></p>")
                       .arg(recipe.getImagePath());
    }

    if (!recipe.getIngredients().isEmpty()) {
        details += "<h2>Ингредиенты:</h2><ul>";
        for (const Ingredient& ingredient : recipe.getIngredients()) {
            details += QString("<li>%1 - %2</li>").arg(ingredient.getName()).arg(ingredient.getQuantity());
        }
        details += "</ul>";
    }

    if (!recipe.getSteps().isEmpty()) {
        details += "<h2>Шаги приготовления:</h2><ol>";
        for (const QString& step : recipe.getSteps()) {
            details += QString("<li>%1</li>").arg(step);
        }
        details += "</ol>";
    }

    ui->recipeTextBrowser->setHtml(details);
}

// метод для обработки фильтра по времени
void MainWindow::on_timeFilterComboBox_currentTextChanged(const QString &text)
{
    if (text == "Любое время") {
        m_timeFilter.setMaxMinutes(0);
    } else if (text == "До 30 минут") {
        m_timeFilter.setMaxMinutes(30);
    } else if (text == "До 1 часа") {
        m_timeFilter.setMaxMinutes(60);
    } else if (text == "До 2 часов") {
        m_timeFilter.setMaxMinutes(120);
    } else if (text == "Более 2 часов") {
        m_timeFilter.setMaxMinutes(1000); // Большое число для "более 2 часов"
    }

    applyFilters();
}


// Обновляем метод applyFilters для правильной работы с временем
void MainWindow::applyFilters()
{
    m_filteredRecipes = m_recipes;

    // Применяем фильтры в определенном порядке
    m_filteredRecipes = m_categoryFilter.filter(m_filteredRecipes);
    m_filteredRecipes = m_timeFilter.filter(m_filteredRecipes);
    m_filteredRecipes = m_favoritesFilter.filter(m_filteredRecipes);

    // Специальная обработка для "Более 2 часов"
    QString timeFilterText = ui->timeFilterComboBox->currentText();
    if (timeFilterText == "Более 2 часов") {
        QList<Recipe> timeFiltered;
        for (const Recipe& recipe : m_filteredRecipes) {
            if (recipe.getCookingTime().isValid() &&
                recipe.getCookingTime().hour() * 60 + recipe.getCookingTime().minute() > 120) {
                timeFiltered.append(recipe);
            }
        }
        m_filteredRecipes = timeFiltered;
    }

    // Фильтр по поисковому запросу
    QString searchText = ui->searchLineEdit->text().toLower();
    if (!searchText.isEmpty()) {
        QList<Recipe> searchFiltered;
        for (const Recipe& recipe : m_filteredRecipes) {
            // Поиск в названии
            if (recipe.getTitle().toLower().contains(searchText)) {
                searchFiltered.append(recipe);
                continue;
            }

            // Поиск в ингредиентах
            bool foundInIngredients = false;
            for (const Ingredient& ingredient : recipe.getIngredients()) {
                if (ingredient.getName().toLower().contains(searchText)) {
                    searchFiltered.append(recipe);
                    foundInIngredients = true;
                    break;
                }
            }

            if (foundInIngredients) continue;

            // Поиск в шагах
            for (const QString& step : recipe.getSteps()) {
                if (step.toLower().contains(searchText)) {
                    searchFiltered.append(recipe);
                    break;
                }
            }
        }
        m_filteredRecipes = searchFiltered;
    }

    // Обновляем список
    ui->recipesListWidget->clear();
    for (const Recipe& recipe : m_filteredRecipes) {
        QString itemText = recipe.getTitle();
        if (recipe.isFavorite()) {
            itemText += " ⭐";
        }

        // Добавляем время приготовления в список
        if (recipe.getCookingTime().isValid()) {
            itemText += QString(" (%1)").arg(recipe.getCookingTime().toString("hh:mm"));
        }

        ui->recipesListWidget->addItem(itemText);
    }

    if (!m_filteredRecipes.isEmpty()) {
        ui->recipesListWidget->setCurrentRow(0);
    } else {
        ui->recipeTextBrowser->clear();
        if (m_recipes.isEmpty()) {
            ui->recipeTextBrowser->setHtml("<h2>Добро пожаловать в Книгу рецептов!</h2>"
                                           "<p>Для начала работы:</p>"
                                           "<ul>"
                                           "<li>Нажмите кнопку <b>«Добавить рецепт»</b> чтобы создать свой первый рецепт</li>"
                                           "<li>Используйте <b>поиск</b> для быстрого поиска рецептов</li>"
                                           "<li>Фильтруйте рецепты по <b>категориям</b> и <b>времени</b></li>"
                                           "<li>Добавляйте понравившиеся рецепты в <b>избранное</b></li>"
                                           "</ul>");
        } else {
            ui->recipeTextBrowser->setHtml("<p>Рецепты не найдены по текущим критериям поиска.</p>");
        }
    }
}

void MainWindow::showContextMenu(const QPoint& pos)
{
    QListWidgetItem* item = ui->recipesListWidget->itemAt(pos);
    if (!item) return;

    QMenu contextMenu(this);
    QAction* editAction = contextMenu.addAction("Редактировать");
    QAction* deleteAction = contextMenu.addAction("Удалить");

    int currentRow = ui->recipesListWidget->currentRow();
    if (currentRow >= 0 && currentRow < m_filteredRecipes.size()) {
        Recipe& recipe = m_filteredRecipes[currentRow];
        QAction* toggleFavoriteAction = contextMenu.addAction(
            recipe.isFavorite() ? "Убрать из избранного" : "Добавить в избранное");

        connect(toggleFavoriteAction, &QAction::triggered, this, [this, &recipe, currentRow]() {
            FavouritesManager::getInstance().toggleFavorite(recipe);

            // Обновляем статус избранного в основном списке рецептов
            for (int i = 0; i < m_recipes.size(); ++i) {
                if (m_recipes[i].getTitle() == recipe.getTitle()) {
                    m_recipes[i].setFavorite(recipe.isFavorite());
                    break;
                }
            }

            updateRecipesList();
            if (!m_userName.isEmpty()) {
                DataManager::getInstance().saveUserRecipes(m_userName, m_recipes);
            } else {
                DataManager::getInstance().saveRecipes(m_recipes);
            } // Сохраняем изменения
        });
    }

    connect(editAction, &QAction::triggered, this, &MainWindow::onEditRecipe);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::onDeleteRecipe);

    contextMenu.exec(ui->recipesListWidget->mapToGlobal(pos));
}

void MainWindow::onEditRecipe()
{
    int currentRow = ui->recipesListWidget->currentRow();
    if (currentRow >= 0 && currentRow < m_filteredRecipes.size()) {
        RecipeDialog dialog(this);
        dialog.setRecipe(m_filteredRecipes[currentRow]);

        if (dialog.exec() == QDialog::Accepted) {
            Recipe updatedRecipe = dialog.getRecipe();

            // Находим и обновляем оригинальный рецепт в основном списке
            for (int i = 0; i < m_recipes.size(); ++i) {
                if (m_recipes[i].getTitle() == m_filteredRecipes[currentRow].getTitle()) {
                    m_recipes[i] = updatedRecipe;
                    break;
                }
            }

            updateRecipesList();
            // Автосохранение после редактирования
            if (!m_userName.isEmpty()) {
                DataManager::getInstance().saveUserRecipes(m_userName, m_recipes);
            } else {
                DataManager::getInstance().saveRecipes(m_recipes);
            }
        }
    }
}

void MainWindow::onDeleteRecipe()
{
    int currentRow = ui->recipesListWidget->currentRow();
    if (currentRow >= 0 && currentRow < m_filteredRecipes.size()) {
        QString recipeTitle = m_filteredRecipes[currentRow].getTitle();

        if (QMessageBox::question(this, "Удаление",
                                  QString("Удалить рецепт \"%1\"?").arg(recipeTitle)) == QMessageBox::Yes) {

            // Удаляем из основного списка
            for (int i = 0; i < m_recipes.size(); ++i) {
                if (m_recipes[i].getTitle() == recipeTitle) {
                    m_recipes.removeAt(i);
                    break;
                }
            }

            // Удаляем из избранного
            FavouritesManager::getInstance().removeFromFavorites(m_filteredRecipes[currentRow]);

            updateRecipesList();
            // Автосохранение после удаления
            if (!m_userName.isEmpty()) {
                DataManager::getInstance().saveUserRecipes(m_userName, m_recipes);
            } else {
                DataManager::getInstance().saveRecipes(m_recipes);
            }
        }
    }
}



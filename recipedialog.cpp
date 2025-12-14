#include "recipedialog.h"
#include "ui_recipedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include "recipetemplatefactory.h"

RecipeDialog::RecipeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeDialog)
{
    ui->setupUi(this);

    // Убираем стандартные кнопки OK/Cancel, так как у нас свои
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Подключаем кнопки вручную
    connect(ui->saveButton, &QPushButton::clicked, this, &RecipeDialog::on_saveButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &RecipeDialog::on_cancelButton_clicked);

    // Подключаем сигналы для работы с шаблонами
    connect(ui->categoryComboBox, &QComboBox::currentTextChanged,
            this, &RecipeDialog::on_categoryComboBox_currentTextChanged);
    connect(ui->templateComboBox, &QComboBox::currentTextChanged,
            this, &RecipeDialog::on_templateComboBox_currentTextChanged);

    // Инициализируем список шаблонов
    on_categoryComboBox_currentTextChanged(ui->categoryComboBox->currentText());
}

RecipeDialog::~RecipeDialog()
{
    delete ui;
}

void RecipeDialog::setRecipe(const Recipe& recipe)
{
    m_recipe = recipe;

    ui->titleLineEdit->setText(recipe.getTitle());

    // Устанавливаем категорию
    int index = ui->categoryComboBox->findText(recipe.getCategory().getName());
    if (index >= 0) {
        ui->categoryComboBox->setCurrentIndex(index);
    }

    ui->timeEdit->setTime(recipe.getCookingTime());
    ui->imagePathLineEdit->setText(recipe.getImagePath());
    ui->favoriteCheckBox->setChecked(recipe.isFavorite());

    // Заполняем список ингредиентов
    ui->ingredientsListWidget->clear();
    for (const Ingredient& ingredient : recipe.getIngredients()) {
        ui->ingredientsListWidget->addItem(
            QString("%1 - %2").arg(ingredient.getName()).arg(ingredient.getQuantity())
            );
    }

    // Заполняем список шагов
    ui->stepsListWidget->clear();
    for (const QString& step : recipe.getSteps()) {
        ui->stepsListWidget->addItem(step);
    }
}

Recipe RecipeDialog::getRecipe() const
{
    return m_recipe;
}

void RecipeDialog::updateRecipeFromForm()
{
    m_recipe.setTitle(ui->titleLineEdit->text());
    m_recipe.setCategory(Category(ui->categoryComboBox->currentText()));
    m_recipe.setCookingTime(ui->timeEdit->time());
    m_recipe.setImagePath(ui->imagePathLineEdit->text());
    m_recipe.setFavorite(ui->favoriteCheckBox->isChecked());

    // Обновляем ингредиенты из списка
    QList<Ingredient> ingredients;
    for (int i = 0; i < ui->ingredientsListWidget->count(); ++i) {
        QString itemText = ui->ingredientsListWidget->item(i)->text();
        QStringList parts = itemText.split(" - ");
        if (parts.size() >= 2) {
            ingredients.append(Ingredient(parts[0], parts[1]));
        } else if (parts.size() == 1) {
            ingredients.append(Ingredient(parts[0], ""));
        }
    }
    m_recipe.setIngredients(ingredients);

    // Обновляем шаги из списка
    QStringList steps;
    for (int i = 0; i < ui->stepsListWidget->count(); ++i) {
        steps.append(ui->stepsListWidget->item(i)->text());
    }
    m_recipe.setSteps(steps);
}

void RecipeDialog::on_addIngredientButton_clicked()
{
    QString name = ui->ingredientNameLineEdit->text().trimmed();
    QString quantity = ui->ingredientQuantityLineEdit->text().trimmed();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название ингредиента");
        return;
    }

    ui->ingredientsListWidget->addItem(QString("%1 - %2").arg(name).arg(quantity));
    ui->ingredientNameLineEdit->clear();
    ui->ingredientQuantityLineEdit->clear();

    // Автофокус на поле названия
    ui->ingredientNameLineEdit->setFocus();
}

void RecipeDialog::on_removeIngredientButton_clicked()
{
    int row = ui->ingredientsListWidget->currentRow();
    if (row >= 0) {
        delete ui->ingredientsListWidget->takeItem(row);
    }
}

void RecipeDialog::on_addStepButton_clicked()
{
    QString step = ui->stepLineEdit->text().trimmed();

    if (step.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите шаг приготовления");
        return;
    }

    ui->stepsListWidget->addItem(step);
    ui->stepLineEdit->clear();
    ui->stepLineEdit->setFocus();
}

void RecipeDialog::on_removeStepButton_clicked()
{
    int row = ui->stepsListWidget->currentRow();
    if (row >= 0) {
        delete ui->stepsListWidget->takeItem(row);
    }
}

void RecipeDialog::on_browseImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Выберите изображение", "", "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!fileName.isEmpty()) {
        ui->imagePathLineEdit->setText(fileName);
    }
}

void RecipeDialog::on_saveButton_clicked()
{
    QString title = ui->titleLineEdit->text().trimmed();
    if (title.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название рецепта");
        return;
    }

    if (ui->ingredientsListWidget->count() == 0) {
        QMessageBox::warning(this, "Ошибка", "Добавьте хотя бы один ингредиент");
        return;
    }

    if (ui->stepsListWidget->count() == 0) {
        QMessageBox::warning(this, "Ошибка", "Добавьте хотя бы один шаг приготовления");
        return;
    }

    updateRecipeFromForm();
    accept();
}

void RecipeDialog::on_cancelButton_clicked()
{
    reject();
}

void RecipeDialog::on_categoryComboBox_currentTextChanged(const QString& text)
{
    // Загружаем общие шаблоны и шаблоны для выбранной категории
    QList<RecipeTemplate> generalTemplates = RecipeTemplateFactory::getInstance().getGeneralTemplates();
    Category selectedCategory(text);
    QList<RecipeTemplate> categoryTemplates = RecipeTemplateFactory::getInstance().getTemplatesForCategory(selectedCategory);

    // Очищаем список шаблонов
    ui->templateComboBox->clear();
    ui->templateComboBox->addItem("Без шаблона");

    // Добавляем общие шаблоны
    for (const RecipeTemplate& template_ : generalTemplates) {
        ui->templateComboBox->addItem(template_.getName());
    }

    // Добавляем шаблоны для выбранной категории
    for (const RecipeTemplate& template_ : categoryTemplates) {
        ui->templateComboBox->addItem(template_.getName());
    }
}

void RecipeDialog::on_templateComboBox_currentTextChanged(const QString& text)
{
    if (text == "Без шаблона" || text.isEmpty()) {
        return;
    }

    // Получаем выбранный шаблон
    RecipeTemplate selectedTemplate = RecipeTemplateFactory::getInstance().getTemplateByName(text);

    if (selectedTemplate.getName().isEmpty()) {
        return;
    }

    // Заполняем форму данными из шаблона
    ui->titleLineEdit->setText(selectedTemplate.getName());

    // Устанавливаем категорию
    int categoryIndex = ui->categoryComboBox->findText(selectedTemplate.getCategory().getName());
    if (categoryIndex >= 0) {
        ui->categoryComboBox->setCurrentIndex(categoryIndex);
    }

    // Заполняем ингредиенты
    ui->ingredientsListWidget->clear();
    for (const Ingredient& ingredient : selectedTemplate.getIngredients()) {
        ui->ingredientsListWidget->addItem(
            QString("%1 - %2").arg(ingredient.getName()).arg(ingredient.getQuantity())
        );
    }

    // Заполняем шаги
    ui->stepsListWidget->clear();
    for (const QString& step : selectedTemplate.getSteps()) {
        ui->stepsListWidget->addItem(step);
    }

    // Устанавливаем время приготовления
    ui->timeEdit->setTime(selectedTemplate.getCookingTime());
}

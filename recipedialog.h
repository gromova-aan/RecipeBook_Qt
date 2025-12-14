#ifndef RECIPEDIALOG_H
#define RECIPEDIALOG_H

#include <QDialog>
#include "recipe.h"
#include "recipetemplatefactory.h"

namespace Ui {
class RecipeDialog;
}

class RecipeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeDialog(QWidget *parent = nullptr);
    ~RecipeDialog();

    void setRecipe(const Recipe& recipe);
    Recipe getRecipe() const;

private slots:
    void on_addIngredientButton_clicked();
    void on_removeIngredientButton_clicked();
    void on_addStepButton_clicked();
    void on_removeStepButton_clicked();
    void on_browseImageButton_clicked();
    void on_saveButton_clicked();
    void on_cancelButton_clicked();
    void on_categoryComboBox_currentTextChanged(const QString& text);
    void on_templateComboBox_currentTextChanged(const QString& text);

private:
    Ui::RecipeDialog *ui;
    Recipe m_recipe;

    void updateRecipeFromForm();
};

#endif // RECIPEDIALOG_H

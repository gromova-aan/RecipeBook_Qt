#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QCloseEvent>
#include "recipe.h"
#include "recipefilter.h"
#include "categoryfilter.h"
#include "timefilter.h"
#include "favoritesfilter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, const QString& userName = QString());
    ~MainWindow();

private slots:
    void on_addRecipeButton_clicked();
    void on_favoritesButton_clicked();
    void on_searchLineEdit_textChanged(const QString &text);
    void on_categoryComboBox_currentTextChanged(const QString &text);
    void on_recipesListWidget_currentRowChanged(int currentRow);

    void on_actionImport_triggered();
    void on_actionExport_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionExit_triggered();

    void updateRecipesList();
    void showRecipeDetails(const Recipe& recipe);
    void onEditRecipe();
    void onDeleteRecipe();
    void showContextMenu(const QPoint& pos);

    void on_timeFilterComboBox_currentTextChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    QList<Recipe> m_recipes;
    QList<Recipe> m_filteredRecipes;
    QString m_userName;

    // Фильтры
    CategoryFilter m_categoryFilter;
    TimeFilter m_timeFilter;
    FavoritesFilter m_favoritesFilter;

    bool m_showingFavorites;

    void applyFilters();
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H

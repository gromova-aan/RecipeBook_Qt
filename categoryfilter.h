#ifndef CATEGORYFILTER_H
#define CATEGORYFILTER_H

#include "recipefilter.h"

class CategoryFilter : public RecipeFilter
{
public:
    CategoryFilter(const QString& category = "");

    QList<Recipe> filter(const QList<Recipe>& recipes) const override;
    QString getName() const override;

    void setCategory(const QString& category);
    QString getCategory() const;

private:
    QString m_category;
};

#endif // CATEGORYFILTER_H

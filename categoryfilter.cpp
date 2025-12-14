#include "categoryfilter.h"

CategoryFilter::CategoryFilter(const QString& category)
    : m_category(category)
{
}

QList<Recipe> CategoryFilter::filter(const QList<Recipe>& recipes) const
{
    if (m_category.isEmpty() || m_category == "Все категории") {
        return recipes;
    }

    QList<Recipe> filtered;
    for (const Recipe& recipe : recipes) {
        if (recipe.getCategory().getName() == m_category) {
            filtered.append(recipe);
        }
    }
    return filtered;
}

QString CategoryFilter::getName() const
{
    return "Фильтр по категории: " + m_category;
}

void CategoryFilter::setCategory(const QString& category)
{
    m_category = category;
}

QString CategoryFilter::getCategory() const
{
    return m_category;
}

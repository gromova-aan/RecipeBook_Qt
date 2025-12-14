#include "favoritesfilter.h"

FavoritesFilter::FavoritesFilter(bool showOnlyFavorites)
    : m_showOnlyFavorites(showOnlyFavorites)
{
}

QList<Recipe> FavoritesFilter::filter(const QList<Recipe>& recipes) const
{
    if (!m_showOnlyFavorites) {
        return recipes;
    }

    QList<Recipe> filtered;
    for (const Recipe& recipe : recipes) {
        if (recipe.isFavorite()) {
            filtered.append(recipe);
        }
    }
    return filtered;
}

QString FavoritesFilter::getName() const
{
    return m_showOnlyFavorites ? "Только избранные" : "Все рецепты";
}

void FavoritesFilter::setShowOnlyFavorites(bool show)
{
    m_showOnlyFavorites = show;
}

bool FavoritesFilter::getShowOnlyFavorites() const
{
    return m_showOnlyFavorites;
}

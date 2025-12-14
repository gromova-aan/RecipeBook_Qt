#include "favouritesmanager.h"

FavouritesManager& FavouritesManager::getInstance()
{
    static FavouritesManager instance;
    return instance;
}

void FavouritesManager::addToFavorites(const Recipe& recipe)
{
    if (!isFavorite(recipe)) {
        m_favorites.append(recipe);
    }
}

void FavouritesManager::removeFromFavorites(const Recipe& recipe)
{
    for (int i = 0; i < m_favorites.size(); ++i) {
        if (m_favorites[i].getTitle() == recipe.getTitle()) {
            m_favorites.removeAt(i);
            break;
        }
    }
}

bool FavouritesManager::isFavorite(const Recipe& recipe) const
{
    for (const Recipe& fav : m_favorites) {
        if (fav.getTitle() == recipe.getTitle()) {
            return true;
        }
    }
    return false;
}

QList<Recipe> FavouritesManager::getFavorites() const
{
    return m_favorites;
}

void FavouritesManager::toggleFavorite(Recipe& recipe)
{
    if (isFavorite(recipe)) {
        removeFromFavorites(recipe);
        recipe.setFavorite(false);
    } else {
        addToFavorites(recipe);
        recipe.setFavorite(true);
    }
}

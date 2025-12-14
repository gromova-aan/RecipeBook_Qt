#ifndef FAVOURITESMANAGER_H
#define FAVOURITESMANAGER_H

#include "recipe.h"
#include <QList>
#include <QObject>

class FavouritesManager : public QObject
{
    Q_OBJECT

public:
    static FavouritesManager& getInstance();

    void addToFavorites(const Recipe& recipe);
    void removeFromFavorites(const Recipe& recipe);
    bool isFavorite(const Recipe& recipe) const;
    QList<Recipe> getFavorites() const;

    void toggleFavorite(Recipe& recipe);

private:
    FavouritesManager() = default;
    ~FavouritesManager() = default;
    FavouritesManager(const FavouritesManager&) = delete;
    FavouritesManager& operator=(const FavouritesManager&) = delete;

    QList<Recipe> m_favorites;
};

#endif // FAVOURITESMANAGER_H

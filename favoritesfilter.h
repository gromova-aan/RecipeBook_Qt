#ifndef FAVORITESFILTER_H
#define FAVORITESFILTER_H

#include "recipefilter.h"

class FavoritesFilter : public RecipeFilter
{
public:
    FavoritesFilter(bool showOnlyFavorites = false);

    QList<Recipe> filter(const QList<Recipe>& recipes) const override;
    QString getName() const override;

    void setShowOnlyFavorites(bool show);
    bool getShowOnlyFavorites() const;

private:
    bool m_showOnlyFavorites;
};

#endif // FAVORITESFILTER_H

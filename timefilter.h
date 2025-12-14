#ifndef TIMEFILTER_H
#define TIMEFILTER_H

#include "recipefilter.h"
#include <QTime>

class TimeFilter : public RecipeFilter
{
public:
    TimeFilter(int maxMinutes = 0);

    QList<Recipe> filter(const QList<Recipe>& recipes) const override;
    QString getName() const override;

    void setMaxMinutes(int minutes);
    int getMaxMinutes() const;

private:
    int m_maxMinutes;
};

#endif // TIMEFILTER_H

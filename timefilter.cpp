#include "timefilter.h"

TimeFilter::TimeFilter(int maxMinutes)
    : m_maxMinutes(maxMinutes)
{
}

QList<Recipe> TimeFilter::filter(const QList<Recipe>& recipes) const
{
    if (m_maxMinutes <= 0) {
        return recipes;
    }

    QList<Recipe> filtered;
    for (const Recipe& recipe : recipes) {
        if (recipe.getCookingTime().isValid() && !recipe.getCookingTime().isNull()) {
            int totalMinutes = recipe.getCookingTime().hour() * 60 + recipe.getCookingTime().minute();
            if (totalMinutes <= m_maxMinutes) {
                filtered.append(recipe);
            }
        }
    }
    return filtered;
}

QString TimeFilter::getName() const
{
    if (m_maxMinutes <= 0) {
        return "Любое время";
    }
    return QString("Фильтр по времени: до %1 мин").arg(m_maxMinutes);
}

void TimeFilter::setMaxMinutes(int minutes)
{
    m_maxMinutes = minutes;
}

int TimeFilter::getMaxMinutes() const
{
    return m_maxMinutes;
}

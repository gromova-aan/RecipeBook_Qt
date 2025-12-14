#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>

class Ingredient
{
public:
    Ingredient(const QString& name = "", const QString& quantity = "");

    QString getName() const;
    void setName(const QString& name);

    QString getQuantity() const;
    void setQuantity(const QString& quantity);

private:
    QString m_name;
    QString m_quantity;
};

#endif // INGREDIENT_H

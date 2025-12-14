#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category
{
public:
    Category(const QString& name = "");

    QString getName() const;
    void setName(const QString& name);

private:
    QString m_name;
};

#endif // CATEGORY_H

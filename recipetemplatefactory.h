#ifndef RECIPETEMPLATEFACTORY_H
#define RECIPETEMPLATEFACTORY_H

#include <QList>
#include "recipetemplate.h"

class RecipeTemplateFactory
{
public:
    static RecipeTemplateFactory& getInstance();

    QList<RecipeTemplate> getTemplatesForCategory(const Category& category) const;
    QList<RecipeTemplate> getGeneralTemplates() const;
    QList<RecipeTemplate> getAllTemplates() const;
    RecipeTemplate getTemplateByName(const QString& name) const;

private:
    RecipeTemplateFactory();
    ~RecipeTemplateFactory();

    RecipeTemplateFactory(const RecipeTemplateFactory&) = delete;
    RecipeTemplateFactory& operator=(const RecipeTemplateFactory&) = delete;

    void initializeTemplates();

    QList<RecipeTemplate> m_templates;
};

#endif // RECIPETEMPLATEFACTORY_H

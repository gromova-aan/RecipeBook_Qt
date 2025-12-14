#include "recipetemplatefactory.h"
#include "category.h"
#include "ingredient.h"

RecipeTemplateFactory& RecipeTemplateFactory::getInstance()
{
    static RecipeTemplateFactory instance;
    return instance;
}

RecipeTemplateFactory::RecipeTemplateFactory()
{
    initializeTemplates();
}

RecipeTemplateFactory::~RecipeTemplateFactory()
{
}

QList<RecipeTemplate> RecipeTemplateFactory::getGeneralTemplates() const
{
    QList<RecipeTemplate> generalTemplates;

    // Общий шаблон супа
    QList<Ingredient> soupIngredients = {
        Ingredient("Вода", "2 л"),
        Ingredient("Картофель", "3 шт"),
        Ingredient("Морковь", "1 шт"),
        Ingredient("Лук", "1 шт"),
        Ingredient("Соль", "по вкусу"),
        Ingredient("Перец", "по вкусу")
    };
    QStringList soupSteps = {
        "Налить воду в кастрюлю и поставить на огонь",
        "Очистить и нарезать овощи",
        "Добавить овощи в кипящую воду",
        "Посолить и поперчить",
        "Варить 25-30 минут до готовности овощей"
    };
    generalTemplates.append(RecipeTemplate("Простой суп", Category("Первое"), soupIngredients, soupSteps, QTime(0, 35)));

    // Общий шаблон кекса
    QList<Ingredient> cakeIngredients = {
        Ingredient("Мука", "2 стакана"),
        Ingredient("Сахар", "1 стакан"),
        Ingredient("Яйца", "3 шт"),
        Ingredient("Масло сливочное", "100 г"),
        Ingredient("Молоко", "100 мл"),
        Ingredient("Ванилин", "1 ч.л."),
        Ingredient("Разрыхлитель", "1 ч.л.")
    };
    QStringList cakeSteps = {
        "Разогреть духовку до 180°C",
        "Смешать сухие ингредиенты (мука, сахар, разрыхлитель)",
        "Взбить яйца с маслом и молоком",
        "Соединить сухие и жидкие ингредиенты",
        "Вылить тесто в форму",
        "Выпекать 35-40 минут до золотистой корочки"
    };
    generalTemplates.append(RecipeTemplate("Простой кекс", Category("Десерт"), cakeIngredients, cakeSteps, QTime(0, 45)));

    // Общий шаблон салата
    QList<Ingredient> saladIngredients = {
        Ingredient("Огурцы", "2 шт"),
        Ingredient("Помидоры", "2 шт"),
        Ingredient("Лук", "1 шт"),
        Ingredient("Растительное масло", "2 ст.л."),
        Ingredient("Уксус", "1 ст.л."),
        Ingredient("Соль", "по вкусу")
    };
    QStringList saladSteps = {
        "Очистить и нарезать овощи",
        "Смешать нарезанные овощи в салатнице",
        "Посолить по вкусу",
        "Добавить растительное масло и уксус",
        "Перемешать и дать настояться 10 минут"
    };
    generalTemplates.append(RecipeTemplate("Простой салат", Category("Салат"), saladIngredients, saladSteps, QTime(0, 15)));

    // Общий шаблон пасты
    QList<Ingredient> pastaIngredients = {
        Ingredient("Паста", "400 г"),
        Ingredient("Вода", "3 л"),
        Ingredient("Соль", "1 ст.л."),
        Ingredient("Оливковое масло", "2 ст.л.")
    };
    QStringList pastaSteps = {
        "В большой кастрюле довести воду до кипения",
        "Добавить соль в кипящую воду",
        "Засыпать пасту и варить согласно инструкции на упаковке",
        "Слить воду, оставив 1 стакан отвара",
        "Добавить оливковое масло и перемешать"
    };
    generalTemplates.append(RecipeTemplate("Отварная паста", Category("Второе"), pastaIngredients, pastaSteps, QTime(0, 15)));

    // Общий шаблон чая
    QList<Ingredient> teaIngredients = {
        Ingredient("Чай листовой или пакетированный", "1 ч.л. или 1 пакетик"),
        Ingredient("Вода кипяченая", "200 мл"),
        Ingredient("Сахар", "по вкусу"),
        Ingredient("Лимон", "по вкусу")
    };
    QStringList teaSteps = {
        "Вскипятить воду",
        "Залить чай кипятком в чашке",
        "Дать настояться 3-5 минут",
        "Добавить сахар и лимон по вкусу",
        "Перемешать и подавать горячим"
    };
    generalTemplates.append(RecipeTemplate("Классический чай", Category("Напиток"), teaIngredients, teaSteps, QTime(0, 5)));

    return generalTemplates;
}

QList<RecipeTemplate> RecipeTemplateFactory::getTemplatesForCategory(const Category& category) const
{
    QList<RecipeTemplate> result;
    for (const RecipeTemplate& template_ : m_templates) {
        if (template_.getCategory().getName() == category.getName()) {
            result.append(template_);
        }
    }
    return result;
}

QList<RecipeTemplate> RecipeTemplateFactory::getAllTemplates() const
{
    return m_templates;
}

RecipeTemplate RecipeTemplateFactory::getTemplateByName(const QString& name) const
{
    for (const RecipeTemplate& template_ : m_templates) {
        if (template_.getName() == name) {
            return template_;
        }
    }
    return RecipeTemplate(); // Возвращаем пустой шаблон, если не найден
}

void RecipeTemplateFactory::initializeTemplates()
{
    // Сначала добавляем общие шаблоны
    QList<RecipeTemplate> generalTemplates = getGeneralTemplates();
    m_templates.append(generalTemplates);
    // Шаблоны для категории "Первое"
    Category firstCourse("Первое");

    // Борщ
    QList<Ingredient> borschIngredients = {
        Ingredient("Свекла", "2 шт"),
        Ingredient("Картофель", "4 шт"),
        Ingredient("Морковь", "1 шт"),
        Ingredient("Лук", "1 шт"),
        Ingredient("Капуста", "300 г"),
        Ingredient("Мясо (говядина)", "500 г"),
        Ingredient("Томатная паста", "2 ст.л."),
        Ingredient("Вода", "2 л")
    };
    QStringList borschSteps = {
        "Подготовьте овощи: очистите и нарежьте свеклу, морковь, лук, картофель и капусту.",
        "В большой кастрюле обжарьте лук и морковь на растительном масле.",
        "Добавьте натертую свеклу и томатную пасту, тушите 5-7 минут.",
        "Залейте бульоном или водой, добавьте картофель и варите 15 минут.",
        "Добавьте капусту и варите еще 10 минут.",
        "Посолите, поперчите, добавьте специи по вкусу.",
        "Дайте настояться 10-15 минут перед подачей."
    };
    m_templates.append(RecipeTemplate("Классический борщ", firstCourse, borschIngredients, borschSteps, QTime(1, 30)));

    // Щи
    QList<Ingredient> schiIngredients = {
        Ingredient("Капуста", "500 г"),
        Ingredient("Картофель", "3 шт"),
        Ingredient("Морковь", "1 шт"),
        Ingredient("Лук", "1 шт"),
        Ingredient("Мясо", "400 г"),
        Ingredient("Вода", "2 л"),
        Ingredient("Лавровый лист", "2 шт")
    };
    QStringList schiSteps = {
        "Подготовьте овощи: очистите и нарежьте капусту, картофель, морковь и лук.",
        "В кастрюле залейте мясо водой и доведите до кипения.",
        "Уберите пену и варите бульон 1 час на среднем огне.",
        "Выньте мясо, отделите от костей и верните в бульон.",
        "Добавьте картофель и варите 10 минут.",
        "Добавьте капусту, морковь и лук, варите еще 15 минут.",
        "Посолите, добавьте лавровый лист и специи."
    };
    m_templates.append(RecipeTemplate("Щи с капустой", firstCourse, schiIngredients, schiSteps, QTime(1, 45)));

    // Шаблоны для категории "Второе"
    Category secondCourse("Второе");

    // Паста Карбонара
    QList<Ingredient> carbonaraIngredients = {
        Ingredient("Спагетти", "400 г"),
        Ingredient("Бекон или гуанчиале", "150 г"),
        Ingredient("Яйца", "3 шт"),
        Ingredient("Пармезан", "100 г"),
        Ingredient("Чеснок", "2 зубчика"),
        Ingredient("Черный перец", "по вкусу"),
        Ingredient("Соль", "по вкусу")
    };
    QStringList carbonaraSteps = {
        "Отварите спагетти в подсоленной воде до состояния al dente.",
        "Обжарьте нарезанный бекон на сковороде до хрустящей корочки.",
        "В миске взбейте яйца с тертым пармезаном.",
        "Добавьте к бекону чеснок и слегка обжарьте.",
        "Смешайте горячие спагетти с беконом.",
        "Снимите с огня и быстро вмешайте яично-сырную смесь.",
        "Посыпьте свежемолотым черным перцем и подавайте."
    };
    m_templates.append(RecipeTemplate("Паста Карбонара", secondCourse, carbonaraIngredients, carbonaraSteps, QTime(0, 25)));

    // Бефстроганов
    QList<Ingredient> beefStroganoffIngredients = {
        Ingredient("Говядина", "500 г"),
        Ingredient("Лук", "2 шт"),
        Ingredient("Мука", "2 ст.л."),
        Ingredient("Сметана", "200 г"),
        Ingredient("Горчица", "1 ст.л."),
        Ingredient("Масло сливочное", "2 ст.л."),
        Ingredient("Бульон", "200 мл"),
        Ingredient("Соль, перец", "по вкусу")
    };
    QStringList beefStroganoffSteps = {
        "Нарежьте говядину тонкими полосками.",
        "Обжарьте мясо на сковороде до золотистой корочки.",
        "Добавьте нарезанный лук и обжарьте до прозрачности.",
        "Посыпьте мукой и перемешайте.",
        "Влейте бульон и тушите 10 минут.",
        "Добавьте сметану и горчицу, перемешайте.",
        "Тушите еще 5-7 минут до готовности."
    };
    m_templates.append(RecipeTemplate("Бефстроганов", secondCourse, beefStroganoffIngredients, beefStroganoffSteps, QTime(0, 40)));

    // Шаблоны для категории "Десерт"
    Category dessert("Десерт");

    // Тирамису
    QList<Ingredient> tiramisuIngredients = {
        Ingredient("Савоярди (дамские пальчики)", "200 г"),
        Ingredient("Маскарпоне", "250 г"),
        Ingredient("Яйца", "3 шт"),
        Ingredient("Сахар", "100 г"),
        Ingredient("Крепкий кофе", "200 мл"),
        Ingredient("Какао-порошок", "2 ст.л."),
        Ingredient("Вино Marsala (или ром)", "2 ст.л.")
    };
    QStringList tiramisuSteps = {
        "Взбейте яичные желтки с сахаром до белой массы.",
        "Добавьте маскарпоне и взбейте до кремообразного состояния.",
        "Взбейте яичные белки в отдельной миске и аккуратно вмешайте в крем.",
        "Смешайте кофе с вином Marsala.",
        "Быстро обмакните печенье в кофе и выложите в форму.",
        "Покройте половиной крема, затем еще слой печенья и крем.",
        "Посыпьте какао-порошком и поставьте в холодильник на 4-6 часов."
    };
    m_templates.append(RecipeTemplate("Классическое тирамису", dessert, tiramisuIngredients, tiramisuSteps, QTime(4, 30)));

    // Шарлотка
    QList<Ingredient> charlotteIngredients = {
        Ingredient("Яблоки", "4 шт"),
        Ingredient("Яйца", "4 шт"),
        Ingredient("Мука", "1 стакан"),
        Ingredient("Сахар", "1 стакан"),
        Ingredient("Ванилин", "1 ч.л."),
        Ingredient("Сода", "0.5 ч.л."),
        Ingredient("Масло сливочное", "для формы")
    };
    QStringList charlotteSteps = {
        "Взбейте яйца с сахаром до пышной массы.",
        "Добавьте муку, ванилин и соду, перемешайте.",
        "Нарежьте яблоки дольками.",
        "Смажьте форму маслом и выложите яблоки.",
        "Залейте тестом и разровняйте.",
        "Выпекайте в разогретой духовке при 180°C 35-40 минут.",
        "Проверьте готовность деревянной палочкой."
    };
    m_templates.append(RecipeTemplate("Яблочная шарлотка", dessert, charlotteIngredients, charlotteSteps, QTime(1, 0)));

    // Шаблоны для категории "Салат"
    Category salad("Салат");

    // Цезарь
    QList<Ingredient> caesarIngredients = {
        Ingredient("Куриное филе", "300 г"),
        Ingredient("Салат ромэн", "200 г"),
        Ingredient("Пармезан", "50 г"),
        Ingredient("Черри", "100 г"),
        Ingredient("Сухарики", "50 г"),
        Ingredient("Чеснок", "2 зубчика"),
        Ingredient("Оливковое масло", "3 ст.л."),
        Ingredient("Лимон", "1 шт")
    };
    QStringList caesarSteps = {
        "Обжарьте куриное филе с чесноком и маслом до готовности.",
        "Порвите салат руками на кусочки.",
        "Нарежьте курицу кубиками, сыр - стружкой.",
        "Разрежьте помидоры пополам.",
        "Смешайте салат, курицу, сыр, помидоры и сухарики.",
        "Заправьте оливковым маслом и лимонным соком.",
        "Посыпьте дополнительно пармезаном."
    };
    m_templates.append(RecipeTemplate("Салат Цезарь", salad, caesarIngredients, caesarSteps, QTime(0, 20)));

    // Шаблоны для категории "Напиток"
    Category drink("Напиток");

    // Компот из сухофруктов
    QList<Ingredient> compoteIngredients = {
        Ingredient("Сухофрукты (курага, чернослив, яблоки)", "200 г"),
        Ingredient("Вода", "2 л"),
        Ingredient("Сахар", "100 г"),
        Ingredient("Лимон", "половина шт")
    };
    QStringList compoteSteps = {
        "Промойте сухофрукты под проточной водой.",
        "Залейте сухофрукты холодной водой и доведите до кипения.",
        "Убавьте огонь и варите 20-25 минут.",
        "Добавьте сахар и нарезанный лимон.",
        "Варите еще 5 минут до полного растворения сахара.",
        "Снимите с огня и дайте настояться 30-40 минут.",
        "Подавайте охлажденным."
    };
    m_templates.append(RecipeTemplate("Компот из сухофруктов", drink, compoteIngredients, compoteSteps, QTime(0, 45)));
}

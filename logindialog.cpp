#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("Вход в RecipeBook");

    // Устанавливаем фокус на поле ввода имени
    ui->nameLineEdit->setFocus();

    // Подключаем сигналы кнопок
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::on_loginButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &LoginDialog::on_cancelButton_clicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getUserName() const
{
    return ui->nameLineEdit->text().trimmed();
}

void LoginDialog::on_loginButton_clicked()
{
    QString name = getUserName();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите ваше имя.");
        return;
    }

    accept(); // Закрываем диалог с результатом Accepted
}

void LoginDialog::on_cancelButton_clicked()
{
    reject(); // Закрываем диалог с результатом Rejected
}

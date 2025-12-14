#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Показываем диалог входа
    LoginDialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) {
        // Пользователь отменил вход
        return 0;
    }

    // Получаем имя пользователя
    QString userName = loginDialog.getUserName();

    // Создаем главное окно с именем пользователя
    MainWindow w(nullptr, userName);
    w.show();

    return a.exec();
}

#include "mainwindow.h"
#include "mainlistwidget.h"
#include <QApplication>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainListWidget w;
    w.show();
    return a.exec();

    // QJsonArray data;
    // QJsonDocument doc(data);
    // QFile file("films.json");
    // if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    //     qWarning() << "Не удалось открыть файл для записи:"
    //                << file.errorString();
    // }
    // file.write(doc.toJson(QJsonDocument::Indented));
    // file.close();
    // qDebug() << "Файл записан успешно";
}

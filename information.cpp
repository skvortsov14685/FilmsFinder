#include "information.h"

Information::Information(QWidget *parent)
    : QWidget(parent) {
    /*private slots:
    void showInf(QString name, int year);
    void closeClicked();
private:
    QLabel* title;
    QLabel* year;
    QLabel* genre;
    QLabel* rate;
    QLabel* director;
    QLabel* time;
    QLabel* rev;
    QPushButton* close;*/

    title = new QLabel("");
    year = new QLabel("");
    genre = new QLabel("");
    rate = new QLabel("");
    director = new QLabel("");
    time = new QLabel("");
    rev = new QLabel("");
    w = new QLabel("");
    l = new QLabel("");
    close = new QPushButton("Закрыть");

    All = new QVBoxLayout();
    All->addWidget(title);
    All->addWidget(year);
    All->addWidget(genre);
    All->addWidget(rate);
    All->addWidget(director);
    All->addWidget(time);
    All->addWidget(rev);
    All->addWidget(w);
    All->addWidget(l);
    All->addWidget(close);

    setLayout(All);

    connect(close, &QPushButton::clicked, this, &Information::closeClicked);
}

void Information::showInf(QString name, int year){

}

void Information::closeClicked(){
    hide();
}

void Information::open(QString name, int y){
    QFile file("films.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл:"
                   << file.errorString();
    }
    QByteArray raw = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(raw);
    // Проверяем, что это массив:
    if (!doc.isArray()) {
        qWarning() << "Ожидался массив";
        return;
    }
    QJsonArray arr = doc.array();
    for (int i = 0; i < arr.count(); i++){
        QJsonObject obj = arr[i].toObject();
        if (obj["title"].toString() == name && obj["year"].toInt() == y){
            title->setText("Название: " + obj["title"].toString());
            year->setText("Год: " + QString::number(obj["year"].toInt()));;
            genre->setText("Жанр: " + obj["genre"].toString());
            rate->setText("Рейтинг: " + QString::number(obj["rate"].toInt()));
            director->setText("Режисёр: " + obj["director"].toString());
            time->setText("Продолжительность: " + QString::number(obj["time"].toInt()));
            rev->setText("Рецензия: " + obj["review"].toString());
            if (obj["watch"].toBool())
                w->setText("Хочу посмотреть: Да");
            else
                w->setText("Хочу посмотреть: Нет");
            if (obj["like"].toBool())
                w->setText("В Избранном: Да");
            else
                w->setText("В избранном: Нет");
            break;
        }
    }
}

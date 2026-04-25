#include "movieadd.h"

MovieAdd::MovieAdd(QWidget *parent)
    : QWidget(parent) {

    titleEdit = new QLineEdit(this);
    yearEdit = new QLineEdit(this);
    genreEdit = new QLineEdit(this);
    rateEdit = new QLineEdit(this);
    directorEdit = new QLineEdit(this);
    timeEdit = new QLineEdit(this);

    form = new QFormLayout();
    form->addRow("Название: ",titleEdit);
    form->addRow("Год: ",yearEdit);
    form->addRow("Жанр: ",genreEdit);
    form->addRow("Рейтинг: ",rateEdit);
    form->addRow("Режисёр: ",directorEdit);
    form->addRow("Длительность: ",timeEdit);

    watch = new QCheckBox("Хочу посмотреть", this);
    like = new QCheckBox("Избранное", this);

    save = new QPushButton("Сохранить");
    exit = new QPushButton("Отменить");
    btns = new QHBoxLayout();
    btns->addWidget(save);
    btns->addWidget(exit);

    rev = new QLabel("Рецензия: ");
    review_edit = new QTextEdit(this);

    All = new QVBoxLayout();
    All->addLayout(form);
    All->addWidget(watch);
    All->addWidget(like);
    All->addWidget(rev);
    All->addWidget(review_edit);
    All->addLayout(btns);

    setLayout(All);

    connect(save, &QPushButton::clicked, this, &MovieAdd::saveCliked);
    connect(exit, &QPushButton::clicked, this, &MovieAdd::exitCliked);
}

void MovieAdd::saveCliked(){
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

    QJsonObject temp;
    if (titleEdit->text() != "" && yearEdit->text() != "" && genreEdit->text() != "" && rateEdit->text() != "" && directorEdit->text() != "" && timeEdit->text() != "" && review_edit->toPlainText() != ""){
        temp["title"] = titleEdit->text();
        temp["year"] = yearEdit->text().toInt();
        temp["genre"] = genreEdit->text();
        temp["rate"] = rateEdit->text().toInt();
        temp["director"] = directorEdit->text();
        temp["time"] = timeEdit->text().toInt();
        temp["review"] = review_edit->toPlainText();
        if (watch->isChecked())
            temp["watch"] = true;
        else
            temp["watch"] = false;
        if (like->isChecked())
            temp["like"] = true;
        else
            temp["like"] = false;
    }
    else{
        QMessageBox::warning(this, "Не все поля заполнены!", "Заполните все поля");
        return;
    }

    for (int i = 0; i < arr.count(); i++){
        QJsonObject obj = arr[i].toObject();
        if (obj["title"].toString() == titleEdit->text() && obj["year"].toInt() == yearEdit->text().toInt()){
            arr.removeAt(i);
        }
    }
    arr.append(temp);

    QJsonDocument doc1(arr);
    QFile file1("films.json");
    if (!file1.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Не удалось открыть файл для записи:"
                   << file1.errorString();
        return;
    }
    file1.write(doc1.toJson(QJsonDocument::Indented));
    file1.close();

    QMessageBox msgBox(this);
    msgBox.setText("Фильм успешно сохранён");
    msgBox.exec();
}

void MovieAdd::exitCliked(){
    hide();
}

void MovieAdd::rewrite(QString name, int year){
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
        if (obj["title"].toString() == name && obj["year"].toInt() == year){
            titleEdit->setText(obj["title"].toString());
            yearEdit->setText(QString::number(obj["year"].toInt()));;
            genreEdit->setText(obj["genre"].toString());
            rateEdit->setText(QString::number(obj["rate"].toInt()));
            directorEdit->setText(obj["director"].toString());
            timeEdit->setText(QString::number(obj["time"].toInt()));
            review_edit->setText(obj["review"].toString());
            if (obj["watch"].toBool())
                watch->setChecked(true);
            else
                watch->setChecked(false);
            if (obj["like"].toBool())
                like->setChecked(true);
            else
                like->setChecked(false);
            break;
        }
    }
}

#include "mainlistwidget.h"

mainListWidget::mainListWidget(QWidget *parent)
    : QWidget(parent) {
    resize(500,400);

    findName = new QLineEdit(this);
    Fname = new QLabel("Поиск по названию",this);
    n = new QHBoxLayout();
    n->addWidget(Fname);
    n->addWidget(findName);

    y = new QLabel("Год");
    startYear = new QSpinBox(this);
    startYear->setRange(1800, 2026);
    startYear->setValue(2000);
    endYear = new QSpinBox(this);
    endYear->setRange(1800, 2026);
    endYear->setValue(2026);

    r = new QLabel("Рейтинг");
    start_rate = new QSpinBox(this);
    start_rate->setRange(1, 100);
    start_rate->setValue(1);
    end_rate = new QSpinBox(this);
    end_rate->setRange(1, 100);
    end_rate->setValue(100);
    yearANDrate = new QHBoxLayout();
    yearANDrate->addWidget(y);
    yearANDrate->addWidget(startYear);
    yearANDrate->addWidget(endYear);
    yearANDrate->addWidget(r);
    yearANDrate->addWidget(start_rate);
    yearANDrate->addWidget(end_rate);

    Fgener = new QLabel("Жанр");
    ganre = new QComboBox(this);
    ganre->addItem("Не помню");
    ganre->addItem("Боевик");
    ganre->addItem("Драма");
    ganre->addItem("Триллер");
    ganre->addItem("Криминал");
    ganre->addItem("Комедия");
    ganre->addItem("Фантастика");
    ganre->addItem("Фэнтези");
    ganre->addItem("Приключения");
    ganre->addItem("Биография");
    ganre->addItem("Ужасы");
    ganre->addItem("Военный");
    ganre->addItem("Вестерн");
    ganre->addItem("Мюзикл");
    ganre->addItem("Мультфильм");
    ganre->addItem("Аниме");
    g = new QHBoxLayout();
    g->addWidget(Fgener);
    g->addWidget(ganre);

    watch = new QCheckBox("Хочу посмотреть", this);
    like = new QCheckBox("Избранное", this);

    finderFilms = new QListWidget(this);

    add = new QPushButton("Добавить", this);
    rewrite = new QPushButton("Редактировать", this);
    del = new QPushButton("Удалить", this);
    import = new QPushButton("Импортировать", this);
    btns = new QHBoxLayout();
    btns->addWidget(add);
    btns->addWidget(rewrite);
    btns->addWidget(del);
    btns->addWidget(import);

    director = new QLineEdit(this);
    dir = new QLabel("Режисёр");
    d = new QHBoxLayout();
    d->addWidget(dir);
    d->addWidget(director);

    time_start = new QSpinBox(this);
    time_start->setRange(1, 1000);
    time_start->setValue(1);
    time_end = new QSpinBox(this);
    time_end->setRange(1, 1000);
    time_end->setValue(1000);
    time = new QLabel("Длительность в минутах");
    t = new QHBoxLayout();
    t->addWidget(time);
    t->addWidget(time_start);
    t->addWidget(time_end);

    All = new QVBoxLayout(this);
    All->addLayout(n);
    All->addLayout(yearANDrate);
    All->addLayout(t);
    All->addLayout(d);
    All->addLayout(g);
    All->addWidget(watch);
    All->addWidget(like);
    All->addWidget(finderFilms);
    All->addLayout(btns);

    addMovie = new MovieAdd();
    inf = new Information();

    setLayout(All);

    connect(add, &QPushButton::clicked, this, &mainListWidget::addClicked);
    connect(rewrite, &QPushButton::clicked, this, &mainListWidget::rewriteClicked);
    connect(del, &QPushButton::clicked, this, &mainListWidget::delClicked);
    connect(import, &QPushButton::clicked, this, &mainListWidget::importClicked);
    connect(finderFilms, &QListWidget::doubleClicked, this, &mainListWidget::showInf);
}

void mainListWidget::showInf(){
    QString text = finderFilms->currentItem()->text();
    QString name = text.split("Название: ").last().split(" |").first();
    int year = (text.split("Год: ").last()).toInt();
    inf->open(name, year);
    inf->show();
}

void mainListWidget::addClicked(){
    addMovie->show();
}

void mainListWidget::rewriteClicked(){
    QString text;
    if (finderFilms->currentItem()) { // Проверка на nullptr, если ничего не выбрано
        text = finderFilms->currentItem()->text();
    }
    else {
        QMessageBox::warning(this, "Элемент не выбран", "Выберите элемент для дозаписи");
        return;
    }

    QString name = text.split("Название: ").last().split(" |").first();
    int year = (text.split("Год: ").last()).toInt();

    addMovie->rewrite(name,year);
    addMovie->show();
}

void mainListWidget::delClicked(){
    QString text;
    if (finderFilms->currentItem()) { // Проверка на nullptr, если ничего не выбрано
        text = finderFilms->currentItem()->text();
    }
    else {
        QMessageBox::warning(this, "Элемент не выбран", "Выберите элемент для удаления");
        return;
    }

    QString name = text.split("Название: ").last().split(" |").first();
    int year = (text.split("Год: ").last()).toInt();

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
            arr.removeAt(i);
        }
    }

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
    msgBox.setText("Фильм успешно удалён");
    msgBox.exec();
}


void mainListWidget::importClicked(){
    QString title = findName->text(), produser = director->text(), genre = ganre->currentText();
    bool a = watch->isChecked(), l = like->isChecked();
    int sy = startYear->value(), ey = endYear->value(), sr = start_rate->value(), er = end_rate->value(), ts = time_start->value(), te = time_end->value();

    if (sy > ey || sr > er || ts > te){
        QMessageBox::warning(this, "Неккоректное значение", "проверьте поля: год, рейтинг, длительность");
    }

    finderFilms->clear();
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

    for (QJsonValue value : arr) {
        QJsonObject obj = value.toObject();
        if (title != "" && title != obj["title"].toString())
            continue;
        if (produser != "" && produser != obj["director"].toString())
            continue;
        if (genre != "Не помню" && genre != obj["genre"].toString())
            continue;
        if (a != obj["watch"].toBool())
            continue;
        if (l != obj["like"].toBool())
            continue;
        if (!(sy <= obj["year"].toInt() && ey >= obj["year"].toInt()))
            continue;
        if (!(sr <= obj["rate"].toInt() && er >= obj["rate"].toInt()))
            continue;
        if (!(ts <= obj["time"].toInt() && te >= obj["time"].toInt()))
            continue;
        finderFilms->addItem("Название: " + obj["title"].toString() + " | Год: " + QString::number(obj["year"].toInt()));
    }
}

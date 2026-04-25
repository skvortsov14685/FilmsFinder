#ifndef MAINLISTWIDGET_H
#define MAINLISTWIDGET_H

#include "movieadd.h"
#include "information.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QFileDialog>

#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QListWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include <QMessageBox>

class MovieAdd;
class Information;

class mainListWidget: public QWidget
{
    Q_OBJECT
public:
    mainListWidget(QWidget *parent = nullptr);
private slots:
    void addClicked();
    void rewriteClicked();
    void delClicked();
    void importClicked();
    void showInf();
private:
    MovieAdd* addMovie = nullptr;
    Information* inf = nullptr;
    QLineEdit* director;
    QLabel* dir;
    QHBoxLayout* d;
    QLineEdit* findName;
    QSpinBox* startYear;
    QSpinBox* endYear;
    QSpinBox* start_rate;
    QSpinBox* end_rate;
    QSpinBox* time_start;
    QSpinBox* time_end;
    QComboBox* ganre;
    QCheckBox* watch;
    QCheckBox* like;
    QListWidget* finderFilms;
    QPushButton* add;
    QPushButton* rewrite;
    QPushButton* del;
    QPushButton* import;
    QVBoxLayout* All;
    QHBoxLayout* btns;
    QHBoxLayout* yearANDrate;
    QHBoxLayout* n;
    QHBoxLayout* g;
    QHBoxLayout* t;
    QLabel* Fname;
    QLabel* y;
    QLabel* r;
    QLabel* Fgener;
    QLabel* time;
};

#endif // MAINLISTWIDGET_H

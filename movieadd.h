#ifndef MOVIEADD_H
#define MOVIEADD_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QFileDialog>

#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QFormLayout>
#include <QMessageBox>
#include <QTextEdit>

class MovieAdd: public QWidget
{
    Q_OBJECT
public:
    MovieAdd(QWidget *parent = nullptr);
    void rewrite(QString name, int year);
private slots:
    void saveCliked();
    void exitCliked();
private:
    QLabel* title;
    QLabel* year;
    QLabel* genre;
    QLabel* rate;
    QLabel* director;
    QLabel* time;
    QLabel* rev;
    QLineEdit* titleEdit;
    QLineEdit* yearEdit;
    QLineEdit* genreEdit;
    QLineEdit* rateEdit;
    QLineEdit* directorEdit;
    QLineEdit* timeEdit;
    QFormLayout* form;
    QPushButton* save;
    QPushButton* exit;
    QVBoxLayout* All;
    QCheckBox* watch;
    QCheckBox* like;
    QHBoxLayout* btns;
    QHBoxLayout* r;
    QTextEdit* review_edit;
};

#endif // MOVIEADD_H

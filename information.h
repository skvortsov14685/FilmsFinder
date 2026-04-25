#ifndef INFORMATION_H
#define INFORMATION_H

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
#include <QLabel>
#include <QWidget>
#include <QFormLayout>
#include <QMessageBox>
#include <QTextEdit>

class Information: public QWidget
{
    Q_OBJECT
public:
    Information(QWidget *parent = nullptr);
    void open(QString name, int year);
private slots:
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
    QLabel* w;
    QLabel* l;
    QPushButton* close;
    QVBoxLayout* All;
};

#endif // INFORMATION_H

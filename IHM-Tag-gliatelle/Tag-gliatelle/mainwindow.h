#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QtCore>

#include <QLabel>

#include <QDirModel>
#include <QTreeView>
#include <QModelIndex>
#include <QFileInfo>
#include <QTabWidget>
#include <QListWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

};

class TabGauche : public QWidget{
    Q_OBJECT
public:
    explicit TabGauche(QWidget *parent = 0);
private:
    QLabel *name = new QLabel("");
    QModelIndex index;
    QDirModel *model;
    QTreeView *tree = new QTreeView();

    QStringListModel *model1;
    QListView *vue1;
    QStringList list1;

    QStringListModel *model2;
    QListView *vue2;
    QStringList list2;

    void readFile(const QJsonObject &json);
    void addTagFile(QJsonObject &json,QString st);

private slots:
    void afficher();
    void ajouterTag();
    void supprimerTag();
};

class TabDroit : public QWidget{
    Q_OBJECT
public:
    TabDroit(QWidget *parent = 0);

private:
    QModelIndex index;
    QStringListModel *model;
    QListView *vue;
    QStringList list;
    QLabel *name = new QLabel("");

    QStringListModel *model1;
    QListView *vue1;
    QStringList list1;

    QStringListModel *model2;
    QListView *vue2;
    QStringList list2;

private slots:
    void afficher();
    void ajouterTag();
    void supprimerTag();


};

#endif // MAINWINDOW_H

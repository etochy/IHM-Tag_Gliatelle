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
    //treeView->currentIndex();

    void ajouterTag();
    void supprimerTag();
private slots:
    void afficher();
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

private slots:
    void afficher();
};

#endif // MAINWINDOW_H

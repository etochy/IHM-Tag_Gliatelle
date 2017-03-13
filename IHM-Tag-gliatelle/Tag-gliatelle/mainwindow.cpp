#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget *zoneCentrale = new QWidget;

    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->addTab(new TabGauche(), "Explorer");
    tabWidget->addTab(new TabDroit(), "Rechercher");

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(tabWidget);
    zoneCentrale->setLayout(layoutPrincipal);
    setCentralWidget(zoneCentrale);

}

MainWindow::~MainWindow()
{

}

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

void TabGauche::afficher(){
    index = tree->currentIndex();
    QFileInfo file =  model->fileInfo(index);
    QString st = "name : "+file.fileName()+
            "\ndate : "+file.lastModified().toString()+
            "\nSize : "+QString::number(file.size())+
            "\nType : "+file.suffix();
    name->setText(st);
}

// -----------------------------------------
TabGauche::TabGauche(QWidget *parent)
    : QWidget(parent)
{
    //---------------------------------------------------
    //QWidget *zoneCentrale = new QWidget;
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;

    //----------------------------------------------------
    QVBoxLayout *layoutCentre = new QVBoxLayout;

    model = new QDirModel(this);
    tree->setModel(model);

    QObject::connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(afficher()));

    layoutCentre->addWidget(tree);


    //----------------------------------------------------
    QVBoxLayout *layoutDroite = new QVBoxLayout;

    QPushButton *button6 = new QPushButton("Coucou6");
    QPushButton *button7 = new QPushButton("Coucou7");

    layoutDroite->addWidget(name);
    layoutDroite->addWidget(button6);
    layoutDroite->addWidget(button7);
    //----------------------------------------------------
    QVBoxLayout *layoutGauche = new QVBoxLayout;

    QPushButton *button1 = new QPushButton("Coucou1");
    QPushButton *button2 = new QPushButton("Coucou2");
    QPushButton *button3 = new QPushButton("Coucou3");
    QPushButton *button4 = new QPushButton("Coucou4");
    QPushButton *button5 = new QPushButton("Coucou5");

    layoutGauche->addWidget(button1);
    layoutGauche->addWidget(button2);
    layoutGauche->addWidget(button3);
    layoutGauche->addWidget(button4);
    layoutGauche->addWidget(button5);

    //----------------------------------------------------
    QHBoxLayout *layoutSecondaire = new QHBoxLayout;

    layoutSecondaire->addLayout(layoutGauche);
    layoutSecondaire->addLayout(layoutCentre);
    layoutSecondaire->addLayout(layoutDroite);

    layoutPrincipal->addLayout(layoutSecondaire);
    setLayout(layoutPrincipal);
    //zoneCentrale->setLayout(layoutPrincipal);
    //setCentralWidget(zoneCentrale);
}

// -----------------------------------------
TabDroit::TabDroit(QWidget *parent)
    : QWidget(parent)
{

}

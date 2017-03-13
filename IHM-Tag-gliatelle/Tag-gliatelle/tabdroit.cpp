#include "mainwindow.h"

TabDroit::TabDroit(QWidget *parent)
    : QWidget(parent)
{

    QHBoxLayout *layoutPrincipal = new QHBoxLayout;

    //----------------
    QVBoxLayout *layoutGauche = new QVBoxLayout;

    QHBoxLayout *layoutRecherche = new QHBoxLayout;
    recherche = new QLineEdit("");
    QPushButton *rechercher = new QPushButton("Rechercher");

    model = new QStringListModel;

    list.push_back("/home/etochy/");
    list.push_back("fichier 2");
    model->setStringList(list);

    vue = new QListView;
    vue->setModel(model);
    vue->setEditTriggers(0);


    QObject::connect(vue, SIGNAL(clicked(QModelIndex)), this, SLOT(afficher()));
    QPushButton *ouvrir = new QPushButton("Ouvrir");

    layoutRecherche->addWidget(recherche);
    layoutRecherche->addWidget(rechercher);
    layoutGauche->addLayout(layoutRecherche);
    layoutGauche->addWidget(vue);
    layoutGauche->addWidget(ouvrir);

    //----------------
    QVBoxLayout *layoutDroit = new QVBoxLayout;

    model1 = new QStringListModel;
    list1.push_back("tagPresent1");
    list1.push_back("tagPresent2");
    model1->setStringList(list1);
    vue1 = new QListView;
    vue1->setModel(model1);
    vue1->setEditTriggers(0);

    model2 = new QStringListModel;
    list2.push_back("tagDispo1");
    list2.push_back("tagDispo2");
    model2->setStringList(list2);
    vue2 = new QListView;
    vue2->setModel(model2);
    vue2->setEditTriggers(0);

    QPushButton *ajouterTag = new QPushButton("Ajouter Tag");
    QPushButton *supprTag = new QPushButton("Supprimer Tag");

    layoutDroit->addWidget(name);
    QLabel *name1 = new QLabel("Tag presents : ");
    layoutDroit->addWidget(name1);
    layoutDroit->addWidget(vue1);
    layoutDroit->addWidget(supprTag);
    QLabel *name2 = new QLabel("Tag disponibles : ");
    layoutDroit->addWidget(name2);
    layoutDroit->addWidget(vue2);
    layoutDroit->addWidget(ajouterTag);
    //----------------

    QObject::connect(ajouterTag, SIGNAL(clicked(bool)), this, SLOT(ajouterTag()));
    QObject::connect(vue1, SIGNAL(activated(QModelIndex)), this, SLOT(supprimerTag()));
    QObject::connect(supprTag, SIGNAL(clicked(bool)), this, SLOT(supprimerTag()));
    QObject::connect(vue2, SIGNAL(activated(QModelIndex)), this, SLOT(ajouterTag()));
    QObject::connect(rechercher, SIGNAL(clicked(bool)), this, SLOT(rechercher()));
    QObject::connect(ouvrir, SIGNAL(clicked(bool)), this, SLOT(ouvrir()));
    //----------------
    layoutPrincipal->addLayout(layoutGauche);
    layoutPrincipal->addLayout(layoutDroit);
    setLayout(layoutPrincipal);
}

void TabDroit::afficher(){

    index = vue->currentIndex();
    fichierCourant = list.at(index.row());

    name->setText(fichierCourant);
    //afficher tag dans vue1
}
void TabDroit::ajouterTag(){
    index = vue2->currentIndex();
    QString st = list2.at(index.row());

    //ajouter tag st
}
void TabDroit::supprimerTag(){
    index = vue1->currentIndex();
    QString st = list1.at(index.row());

    //supprimer tag st de fichier courant
}
void TabDroit::rechercher(){
    QString st = recherche->text();

    //rechercher correspondance
}

void TabDroit::ouvrir(){
    if(fichierCourant == ""){
        QMessageBox::information(this, "Erreur", "Aucun fichier n'a été séléctionné");
    }
    else{
        QDesktopServices::openUrl(fichierCourant);
    }
}

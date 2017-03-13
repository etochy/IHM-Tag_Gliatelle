#include "mainwindow.h"

TabDroit::TabDroit(QWidget *parent)
    : QWidget(parent)
{

    QHBoxLayout *layoutPrincipal = new QHBoxLayout;

    //----------------
    QVBoxLayout *layoutGauche = new QVBoxLayout;

    QHBoxLayout *layoutRecherche = new QHBoxLayout;
    QLineEdit *fileNameEdit = new QLineEdit("Tag 1");
    QPushButton *rechercher = new QPushButton("Rechercher");

    model = new QStringListModel;

    list.push_back("fichier 1");
    list.push_back("fichier 2");
    model->setStringList(list);

    vue = new QListView;
    vue->setModel(model);
    vue->setEditTriggers(0);


    QObject::connect(vue, SIGNAL(clicked(QModelIndex)), this, SLOT(afficher()));
    QPushButton *ouvrir = new QPushButton("Ouvrir");

    layoutRecherche->addWidget(fileNameEdit);
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
    layoutDroit->addWidget(vue1);
    layoutDroit->addWidget(supprTag);
    layoutDroit->addWidget(vue2);
    layoutDroit->addWidget(ajouterTag);
    //----------------
    layoutPrincipal->addLayout(layoutGauche);
    layoutPrincipal->addLayout(layoutDroit);
    setLayout(layoutPrincipal);
}

void TabDroit::afficher(){

    index = vue->currentIndex();
    QString st = list.at(index.row());

    name->setText(st);
}
void TabDroit::ajouterTag(){

}
void TabDroit::supprimerTag(){

}

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

    list.push_back("coucou");
    list.push_back("encule");
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
    QPushButton *addTag = new QPushButton("Ajouter tag");
    layoutDroit->addWidget(addTag);
    layoutDroit->addWidget(name);

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

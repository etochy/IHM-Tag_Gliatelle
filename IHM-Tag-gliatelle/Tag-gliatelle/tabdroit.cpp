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

    name->setText("Fichier : "+fichierCourant);

    QString fileName = "/home/etochy/tagFichier.txt";
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    list1.clear();
    QString ligne;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        QStringList l = ligne.split(";");
        QString str1 = l.at(0);
        if(fichierCourant == str1){
            for(int i=1; i<l.size();++i){
                list1.push_back(l.at(i));
            }
            model1->removeRows( 0, model1->rowCount() );
        }
    }
    model1->setStringList(list1);
    fichier.close();

    majTagsDispo();
}
void TabDroit::ajouterTag(){
    index = vue2->currentIndex();
    QString st = list2.at(index.row());

    //ajouter tag st

    QStringList listTags;
    QString fileName = "/home/etochy/tagFichier.txt";
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);

    QString ligne;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        listTags.push_back(ligne);
    }
    fichier.close();
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux2(&fichier);
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
    flux2.setCodec("UTF-8");
    // Écriture des différentes lignes dans le fichier
    int b = 0;
    for(int i=0; i<listTags.size();++i){
        l.clear();
        QStringList l2 = listTags.at(i).split(";");
        QString str1 = l2.at(0);

        if(fichierCourant == str1){
            flux << listTags.at(i) << ";" << st << endl;
            b = 1;
            l = listTags.at(i).split(";");
        }
        else{
            flux2 << listTags.at(i) << endl;
        }
    }
    if(b == 0){
        flux2 << fichierCourant << ";" << st << endl;
    }
    fichier.close();
    qWarning("avant afficher");
    afficher();
    qWarning("apres afficher");

}
void TabDroit::supprimerTag(){
    index = vue1->currentIndex();
    QString st = list1.at(index.row());

    //supprimer tag st de fichier courant
}
void TabDroit::rechercher(){
    QString st = recherche->text();

    //rechercher correspondance*
    QString fileName = "/home/etochy/tagFichier.txt";
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    list.clear();
    QString ligne;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        QStringList l = ligne.split(";");

        if(ligne.contains(st)){
            list.push_back(l.at(0));
        }
    }
    model->setStringList(list);
    fichier.close();
}

void TabDroit::ouvrir(){
    if(fichierCourant == ""){
        QMessageBox::critical(this, "Erreur", "Aucun fichier n'a été séléctionné");
    }
    else{
        QDesktopServices::openUrl(fichierCourant);
    }
}
void TabDroit::majTagsDispo(){
    qWarning("maj");
    QString fileName = "/home/etochy/tags.txt";
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    list2.clear();
    QString ligne;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        list2.push_back(ligne);
    }
    model2->setStringList(list2);
    fichier.close();

}

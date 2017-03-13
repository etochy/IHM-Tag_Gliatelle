#include "mainwindow.h"

TabGauche::TabGauche(QWidget *parent)
    : QWidget(parent)
{
    //---------------------------------------------------

    //---------------------------------------------------
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;

    //----------------------------------------------------
    QVBoxLayout *layoutCentre = new QVBoxLayout;

    model = new QDirModel(this);
    tree->setModel(model);

    QObject::connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(afficher()));

    layoutCentre->addWidget(tree);


    //----------------------------------------------------
    QVBoxLayout *layoutDroite = new QVBoxLayout;

    QLineEdit *tagedit = new QLineEdit("tag");
    QPushButton *rech = new QPushButton("Rechercher");

    QPushButton *ajouterTag = new QPushButton("Ajouter Tag");
    QPushButton *supprTag = new QPushButton("Supprimer Tag");

    model1 = new QStringListModel;
    model1->setStringList(list1);
    vue1 = new QListView;
    vue1->setModel(model1);
    vue1->setEditTriggers(0);

    model2 = new QStringListModel;
    vue2 = new QListView;
    vue2->setModel(model2);
    vue2->setEditTriggers(0);

    layoutDroite->addWidget(name);

    layoutDroite->addWidget(vue1);
    layoutDroite->addWidget(supprTag);
    layoutDroite->addWidget(vue2);
    layoutDroite->addWidget(ajouterTag);

    //----------------------------------------------------

    QObject::connect(ajouterTag, SIGNAL(clicked(bool)), this, SLOT(ajouterTag()));
    QObject::connect(vue1, SIGNAL(activated(QModelIndex)), this, SLOT(supprimerTag()));
    QObject::connect(supprTag, SIGNAL(clicked(bool)), this, SLOT(supprimerTag()));
    QObject::connect(vue2, SIGNAL(activated(QModelIndex)), this, SLOT(ajouterTag()));

    //----------------------------------------------------
    QHBoxLayout *layoutSecondaire = new QHBoxLayout;

    layoutSecondaire->addLayout(layoutCentre);
    layoutSecondaire->addLayout(layoutDroite);

    layoutPrincipal->addLayout(layoutSecondaire);
    setLayout(layoutPrincipal);
}

void TabGauche::afficher(){
    index = tree->currentIndex();
    QFileInfo file =  model->fileInfo(index);
    QString st = "name : "+file.fileName()+
            "\ndate : "+file.lastModified().toString()+
            "\nSize : "+QString::number(file.size())+
            "\nType : "+file.suffix();
    fichierCourant = file.absoluteFilePath();
    name->setText(st);

    //ajouter tag st
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

void TabGauche::ajouterTag(){
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
        QString str1 = l.at(0);
        if(fichierCourant == str1){
            flux << listTags.at(i) << ";" << st << endl;
            b = 1;
            l = listTags.at(i).split(";");;
        }
        else{
            flux2 << listTags.at(i) << endl;
        }
    }
    if(b == 0){
        flux2 << fichierCourant << ";" << st << endl;
    }
    fichier.close();
    afficher();

}
void TabGauche::supprimerTag(){
    index = vue1->currentIndex();
    QString st = list1.at(index.row());

    //supprimer tag st de fichier courant
}

void TabGauche::majTagsDispo(){
    QString fileName = "/home/etochy/tags.txt";
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    list2.clear();
    QString ligne;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        for(int i=1;i<l.size();++i){
            if(l.at(i) == ligne){
                //do nothing
            }
            else{
                list2.push_back(ligne);
            }
        }
    }
    model2->setStringList( QStringList{} );
    model2->setStringList(list2);
    fichier.close();

}


#include "mainwindow.h"

TabGauche::TabGauche(QWidget *parent)
    : QWidget(parent)
{
    //---------------------------------------------------
    /*
    QFile loadFile(QStringLiteral("/home/etochy/tag.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());*/
    //---------------------------------------------------
    QFile saveFile(QStringLiteral("/home/etochy/tag.json"));

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
    }

    QJsonObject gameObject;
    addTagFile(gameObject,"tg");
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

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

    layoutDroite->addWidget(name);

    layoutDroite->addWidget(vue1);
    layoutDroite->addWidget(supprTag);
    layoutDroite->addWidget(vue2);
    layoutDroite->addWidget(ajouterTag);

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
    name->setText(st);
}
void TabGauche::ajouterTag(){

}
void TabGauche::supprimerTag(){

}

// -----------------------------------------

void TabGauche::readFile(const QJsonObject &json)
{
    /*
    list1.clear();
    QJsonArray array = json["files"].toArray();
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject object = array[i].toObject();
        list1.push_back(object["path"]);
    }*/
}

void TabGauche::addTagFile(QJsonObject &json, QString st)
{
    QJsonArray npcArray;
    list2.clear();
    qWarning("coucou");

    QJsonArray levelArray = json["tags"].toArray();
    for (int i = 0; i < levelArray.size(); ++i) {
        QString st = levelArray[i].toString();
        list2.push_back(st);
        qWarning("coucou");
    }
    for (int i = 0; i < list2.size(); ++i) {
        npcArray.append(list2.at(i));
        qWarning("coucou 2");
    }
    npcArray.append("4");

    json["tags"] = npcArray;
}

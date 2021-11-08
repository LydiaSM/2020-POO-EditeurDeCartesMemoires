#include "projet.h"
#include "ui_projet.h"

projet::projet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::projet)
{
    ui->setupUi(this);
    if (!QDir("Paquets").exists()) { QDir().mkdir("Paquets"); }          //pour creer le dossier contenant tt les paquets
    choisirpaquet();                                                     //pour afficher les paquets deja enregistrés à l'éxécution
}

projet::~projet()
{
    delete ui;
}


void projet::choisirpaquet()                                            //pour choisir un paquet
{
    ui->comboBox->clear();
    ui->comboBox->addItem("Choisir un paquet");

    QDir ok("Paquets");
    QStringList liste= ok.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);
    foreach(const QString &nom, liste)          //pour ajouter tt les dossiers présents dans le dossier Paquets
    {
            ui->comboBox->addItem(nom);
    }
}


void projet::on_pushButton_clicked()                                   //pour ajouter un paquet
{
    QString paquet= QInputDialog::getText(this,tr("Creer un dossier"),"Nom");
    if (!QDir("Paquets/"+paquet).exists()) { QDir().mkdir("Paquets/"+paquet); }
    else
    {
        QMessageBox ok;
        ok.setText("Le paquet existe déjà ou erreur.");
        ok.exec();
    }
    choisirpaquet();
}


void projet::on_pushButton_2_clicked()                                  //pour supprimer un paquet
{
    QString sup=ui->comboBox->currentText();
    QDir ("Paquets/"+sup).removeRecursively();
    choisirpaquet();
}


void projet::choisircarte()                                            //pour choisir une carte mémoire
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("Selectionner une carte memoire");

    QString chemin= ui->comboBox->currentText();
    QDir ok("Paquets/"+chemin);
    QStringList liste= ok.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);
    foreach(const QString &nom, liste)
    {
            ui->comboBox_2->addItem(nom);
    }
}


void projet::on_comboBox_currentIndexChanged()
{
    choisircarte();
    ui->lineEdit->clear();                                              //pour effacer la question
    ui->lineEdit_2->clear();                                            //pour effacer la reponse
}


void projet::on_pushButton_5_clicked()                                //pour ajouter une carte mémoire
{
    bool var;
    QString carte= QInputDialog::getText(this,tr("Creer une carte memoire"),"Nom",QLineEdit::Normal,0,&var);

    if(var==1){
        QString chemin= ui->comboBox->currentText();
        QFile c("Paquets/"+chemin+"/"+carte+".txt");

        if (!c.exists()) { c.open(QIODevice::WriteOnly|QIODevice::Text); }
        else
        {
            QMessageBox ok;
            ok.setText("La carte memoire existe déjà.");
            ok.exec();
        }
        choisircarte();
     }
}

void projet::on_pushButton_4_clicked()                                  //pour supprimer une carte mémoire
{
    QString sup= ui->comboBox->currentText();
    QString supp= ui->comboBox_2->currentText();
    QFile ("Paquets/"+sup+"/"+supp).remove();
    choisircarte();
    ui->lineEdit->clear();                                              //pour effacer la question
    ui->lineEdit_2->clear();                                            //pour effacer la reponse
}


void projet::on_pushButton_7_clicked()                                  //pour modifier la question
{
    if(ui->comboBox_2->currentIndex()!=0){          //si fichier est selectionné
    bool var;
    QString ok= QInputDialog::getText(this,tr("Modifier la quetion"),"Question",QLineEdit::Normal,0,&var);

    if (var==1){                //si une question est modifiée
        QString paquet= ui->comboBox->currentText();
        QString carte= ui->comboBox_2->currentText();
        QFile chemin("Paquets/"+paquet+"/"+carte);

        if(chemin.open(QIODevice::WriteOnly| QIODevice::Text))
        {
            QTextStream flux(&chemin);
            flux<<ok<<endl<<ui->lineEdit_2->text()<<endl;
            chemin.close();
        }
        ui->lineEdit->setText(ok);
    }
    }
}


void projet::on_pushButton_3_clicked()                                     //pour modifier la réponse
{
    if(ui->comboBox_2->currentIndex()!=0){          //si fichier est selectionné
    bool var;
    QString ok= QInputDialog::getText(this,tr("Modifier la reponse"),"Reponse",QLineEdit::Normal,0,&var);

    if (var==1){                //si une réponse est modifiée
        QString paquet= ui->comboBox->currentText();            //pour supprimer la question et la reponse affichées
        QString carte= ui->comboBox_2->currentText();
        QFile chemin("Paquets/"+paquet+"/"+carte);

        if(chemin.open(QIODevice::WriteOnly| QIODevice::Text))
        {
            QTextStream flux(&chemin);
            flux<<ui->lineEdit->text()<<endl<<ok<<endl;
            chemin.close();
        }
        ui->lineEdit_2->setText(ok);
    }
    }
}


void projet::on_comboBox_2_currentIndexChanged()                //pour lire la question et la reponse
{
    QString paquet= ui->comboBox->currentText();
    QString carte= ui->comboBox_2->currentText();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    QFile chemin("Paquets/"+paquet+"/"+carte);

    if(chemin.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        QTextStream flux(&chemin);
        ui->lineEdit->setText(flux.readLine());
        ui->lineEdit_2->setText(flux.readLine());
    }
}

//SMAHI LYDIA
#ifndef PROJET_H
#define PROJET_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class projet; }
QT_END_NAMESPACE

class projet : public QMainWindow
{
    Q_OBJECT

public:
    projet(QWidget *parent = nullptr);
    ~projet();

private slots:

    void choisirpaquet();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void choisircarte();

    void on_comboBox_currentIndexChanged();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_2_currentIndexChanged();

private:
    Ui::projet *ui;
};
#endif // PROJET_H

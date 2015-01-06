#ifndef INTERFACCIA_H
#define INTERFACCIA_H
#include <QtWidgets/QDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QtWidgets/QMessageBox>

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>

#include <locale>

#include "ui_interfaccia.h"
#include "include/localizzazione.hpp"


class Dialogo : public QDialog, public Ui::Dialogo
{
    Q_OBJECT
public:
    Dialogo(QWidget* genitore=0);

    //void resizeEvent ( QResizeEvent * e ) ;
private slots:
    void on_carica_clicked();
    void on_stima_clicked();
    void on_tipo_sift_vlsift_clicked();
    void on_tipo_sift_siftgpu_clicked();
    void salva_configurazione();
    void carica_configurazione();


private:
    void carica_immagine(QString nomefile,QGraphicsView* destinazione);
    void setmappa(const std::string&,const std::string&,const std::string&,const std::string&);
    QString nomeimmagine;
    QWebView *webviewmappa;
    std::string lat_exif;
    std::string lon_exif;

};

class TastoSfoglia : QObject
{
    Q_OBJECT
private slots:
    void on_tasto_clicked()
    {
        nomefile = QFileDialog::getOpenFileName(genitore,("Seleziona file"), "", tr(estensioni.toStdString().c_str()));
        if(testo)
            testo->setText(nomefile);
    }
public:
    void set_estensioni(QString estensioni)
    {
        this->estensioni=estensioni;
    }

    TastoSfoglia(QWidget* genitore,QPushButton* tasto,QLineEdit* testo=NULL):QObject(genitore)
    {
        this->genitore=genitore;
        this->tasto=tasto;
        this->testo=testo;
        this->estensioni=("tutti i file (*.*)");
        QObject::connect(this->tasto,SIGNAL(clicked()),this,SLOT(on_tasto_clicked()));
    }


private:
    QWidget* genitore;
    QPushButton* tasto;
    QLineEdit*   testo;
    QString nomefile;
    QString estensioni;


};


#endif

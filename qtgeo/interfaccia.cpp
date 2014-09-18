#include "interfaccia.h"




Dialogo::Dialogo(QWidget* genitore) : QDialog(genitore)
{

    setupUi(this);
    this->setFixedSize(this->size());
    webviewmappa=new QWebView(mappa);
    //mappa->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //mappa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    webviewmappa->page()->mainFrame()->setScrollBarPolicy( Qt::Vertical, Qt::ScrollBarAlwaysOff );
    webviewmappa->page()->mainFrame()->setScrollBarPolicy( Qt::Horizontal, Qt::ScrollBarAlwaysOff );
    setmappa("40","14","40","14");
   //webviewmappa->setUrl(QUrl("file:///home/andrea/monnezza/qtgeo/mappa.html?x="+lat+"&y="+lon+"&w="+QString::number(mappa->size().width())+"&h="+QString::number(mappa->size().height())));
    //webviewmappa->setUrl(QUrl("file:///home/andrea/monnezza/qtgeo/mappa.html?x=40&y=14&w=200&h=200"));
    //webviewmappa->setGeometry(0,0,mappa->size().width(),mappa->size().height());
    //mappa->fitInView(QRect(0,0,mappa->size().width(),mappa->size().height()),Qt::KeepAspectRatio);

    //webviewmappa->show();
    TastoSfoglia* out_sfoglia=new TastoSfoglia(this,out_tasto,out_input);
    out_sfoglia->set_estensioni("bundler out (*.out)");
    TastoSfoglia* bin_sfoglia=new TastoSfoglia(this,bin_tasto,bin_input);
    bin_sfoglia->set_estensioni("ACG bin (*.bin)");
    TastoSfoglia* cluster_sfoglia=new TastoSfoglia(this,cluster_tasto,cluster_input);
    cluster_sfoglia->set_estensioni(".txt (*.txt)");
    TastoSfoglia* center_sfoglia=new TastoSfoglia(this,center_tasto,center_input);
    center_sfoglia->set_estensioni(".txt (*.txt)");

    QObject::connect(out_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(bin_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(cluster_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(center_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(n_centroidi_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    carica_configurazione();
}


void Dialogo::setmappa(std::string lat,std::string lon, std::string lat_exif, std::string lon_exif)
{
std::string u;
if(lat=="" || lon=="")
    u="file:///home/andrea/monnezza/qtgeo/mappa.html?x_ex="+lat_exif+"&y_ex="+lon_exif+"&w="+std::to_string(mappa->size().width())+"&h="+std::to_string(mappa->size().height());
else
    u="file:///home/andrea/monnezza/qtgeo/mappa.html?x="+lat+"&y="+lon+"&x_ex="+lat_exif+"&y_ex="+lon_exif+"&w="+std::to_string(mappa->size().width())+"&h="+std::to_string(mappa->size().height());
webviewmappa->setUrl(QUrl(QString::fromStdString(u)));
std::cout<<u<<"\n";
}

void Dialogo::carica_configurazione()
{
    std::fstream f("./configurazione",std::ios::in);
    if(!f)
        return;

    std::string s;

    getline(f,s);
    out_input->setText(s.c_str());
    s.clear();
    getline(f,s);
    cluster_input->setText(s.c_str());
    s.clear();
    getline(f,s);
    center_input->setText(s.c_str());
    s.clear();
    getline(f,s);
    bin_input->setText(s.c_str());
    s.clear();
    getline(f,s);
    n_centroidi_input->setText(s.c_str());
    f.close();
}

void Dialogo::salva_configurazione()
{
    std::cout<<"salvo\n";
    std::fstream f("./configurazione",std::ios::out);
    f<<out_input->text().toStdString()<<"\n"<<cluster_input->text().toStdString()<<"\n"<<center_input->text().toStdString()<<"\n"<<bin_input->text().toStdString()<<"\n"<<n_centroidi_input->text().toStdString();
    f.close();


}

void Dialogo::carica_immagine(QString nomeimmagine,QGraphicsView* destinazione)
{
    //carica l'immagine con path nomeimmagine nella QGraphicsView puntata da destinazione

    QPixmap immaginepixmap;
    immaginepixmap.load(nomeimmagine);

    //QGraphicsPixmapItem* oggettopixmap=new QGraphicsPixmapItem(immaginepixmap);

    QGraphicsScene* scena= new QGraphicsScene(this);
    //scena->addItem(oggettopixmap);
    scena->addPixmap(immaginepixmap);

    destinazione->setScene(scena);
    //adatta l'immagine alla finestra
    destinazione->fitInView(scena->itemsBoundingRect(),Qt::KeepAspectRatio);

}


void Dialogo::on_carica_clicked()
{
    nomeimmagine = QFileDialog::getOpenFileName(this,
    tr("Seleziona Immagine"), "", tr("file JPG (*.jpg)"));

    carica_immagine(nomeimmagine, Dialogo::immagine);


    //carico i dati gps exif

    ExifGPS exifgps=readGPS(nomeimmagine.toStdString());
    lat_exif=std::to_string(exifgps.lat);
    lat_exif.replace(lat_exif.find(","),1,".");
    lon_exif=std::to_string(exifgps.lon);
    lon_exif.replace(lon_exif.find(","),1,".");
    std::cout<<lat_exif<<" "<<lon_exif<<endl;
    setmappa("","",lat_exif,lon_exif);
}



void Dialogo::on_stima_clicked()
{
 qDebug()<<"premuto stima";
 localizzazione acg;
 acg.imposta_path(out_input->text().toStdString(),cluster_input->text().toStdString(),center_input->text().toStdString(),bin_input->text().toStdString(),n_centroidi_input->text().toStdString());
 QApplication::setOverrideCursor(Qt::WaitCursor);
 stima->setEnabled(false);
 std::vector<std::string> coordinate=acg.localizza(nomeimmagine.toStdString());
 std::string lon=coordinate.at(0);
 std::string lat=coordinate.at(1);

 setmappa(lat,lon,lat_exif,lon_exif);
 double dist=acg.calcola_distanza(::atof(lat.replace(lat.find("."),1,",").c_str()),::atof(lon.replace(lon.find("."),1,",").c_str()),::atof(lat_exif.replace(lat_exif.find("."),1,",").c_str()),::atof(lon_exif.replace(lon_exif.find("."),1,",").c_str()));
 std::cout<<"distanza: "<<dist<<"\n";
distanza_etichetta->setText(QString(std::to_string(dist).c_str()));

 stima->setEnabled(true);
 QApplication::restoreOverrideCursor();


}





#include "interfaccia.h"




Dialogo::Dialogo(QWidget* genitore) : QDialog(genitore)
{

    std::locale englocale( "en_US.UTF-8");   // get global locale
    std::locale::global(englocale);
    //std::cout.imbue(englocale);  // imbue global locale
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

    on_tipo_sift_vlsift_clicked();

    QObject::connect(out_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(bin_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(cluster_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(center_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(n_centroidi_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    QObject::connect(tmp_input, SIGNAL(textChanged( const QString& )), this, SLOT(salva_configurazione()));
    carica_configurazione();
}


std::string get_path_eseguibile()
{
        char arg1[1024];
        char exepath[1024 + 1] = {0};

        sprintf( arg1, "/proc/%d/exe", getpid() );
        readlink( arg1, exepath, 1024 );

        std::string ritorno(exepath);
        ritorno= ritorno.substr(0,ritorno.find_last_of("/"));
//        std::cout<<ritorno<<"\n";
        return ritorno;
}

void Dialogo::setmappa(const std::string& lat,const std::string& lon, const std::string& lat_exif, const std::string& lon_exif)
{
    std::string path_locale=get_path_eseguibile();
    std::string path_mappa="";
    std::string coord_exif="";
    std::string coord_stimate="";

    if(lat.compare("")!=0 && lon.compare("")!=0)
        coord_stimate="x="+lat+"&y="+lon+"&";
    if(lat_exif.compare("")!=0 && lon_exif.compare("")!=0)
        coord_exif="x_ex="+lat_exif+"&y_ex="+lon_exif;

    path_mappa="file:///"+get_path_eseguibile()+"/../mappa.html?"+coord_stimate+coord_exif+"&w="+std::to_string(mappa->size().width())+"&h="+std::to_string(mappa->size().height());
    webviewmappa->setUrl(QUrl(QString::fromStdString(path_mappa)));
    std::cout<<path_mappa<<"\n";
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
    s.clear();
    getline(f,s);
    tmp_input->setText(s.c_str());
    f.close();
}

void Dialogo::salva_configurazione()
{

    std::cout<<"salvo\n";
    std::fstream f("./configurazione",std::ios::out);
    f<<out_input->text().toStdString()<<"\n"<<cluster_input->text().toStdString()<<"\n"<<center_input->text().toStdString()<<"\n"<<bin_input->text().toStdString()<<"\n"<<n_centroidi_input->text().toStdString()<<"\n"<<tmp_input->text().toStdString();
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

    if(nomeimmagine.isEmpty()) return;
    //carico i dati gps exif
    ExifGPS exifgps;
try
{
    exifgps=readGPS(nomeimmagine.toStdString());
    lat_exif=std::to_string(exifgps.lat);
    lon_exif=std::to_string(exifgps.lon);

    std::cout<<"Coordinate exif in immagine: "<<lat_exif<<" "<<lon_exif<<"\n ";

}
catch(Exiv2::Error& e)
{
    QMessageBox::information(this,tr("ATTENZIONE"),tr(e.what()));
    lat_exif="";
    lon_exif="";
}
    setmappa("","",lat_exif,lon_exif);
    lat_input->setText(lat_exif.c_str());
    lon_input->setText(lon_exif.c_str());

    /*if(lat_exif.find(",")!=lat_exif.npos)
        lat_exif.replace(lat_exif.find(","),1,".");*/

    /*if(lon_exif.find(",")!=lon_exif.npos)
        lon_exif.replace(lon_exif.find(","),1,".");
    std::cout<<lat_exif<<" "<<lon_exif<<endl;
    setmappa("","",lat_exif,lon_exif);*/
}



void Dialogo::on_stima_clicked()
{
    // qDebug()<<"Premuto stima\n";
     //std::cout<<"Se tmp non esiste la creo\n";
     log_text_browser->append(QString("Attendere...\n\n"));
     QApplication::processEvents();
     boost::filesystem::create_directories((tmp_input->text().toStdString()).c_str());
     localizzazione acg;
     acg.imposta_path(out_input->text().toStdString(),cluster_input->text().toStdString(),center_input->text().toStdString(),bin_input->text().toStdString(),n_centroidi_input->text().toStdString(),tmp_input->text().toStdString());
     QApplication::setOverrideCursor(Qt::WaitCursor);
     stima->setEnabled(false);
     char tipo_sift_scelto=0;
     if(tipo_sift_siftgpu->isChecked())
        tipo_sift_scelto=1;

     std::string parametri=parametri_input->text().toStdString();
     std::string log;
try
{
     std::vector<std::string> coordinate=acg.localizza(nomeimmagine.toStdString(),tipo_sift_scelto,parametri,log);
     std::string lon=coordinate.at(0);
     std::string lat=coordinate.at(1);
     setmappa(lat,lon,lat_exif,lon_exif);
     double dist=acg.calcola_distanza(atof(lat.c_str()),atof(lon.c_str()),atof(lat_exif.c_str()),atof(lon_exif.c_str()),log);
     if(lat.compare("")!=0 && lat_exif.compare("")!=0)
     {

        std::cout<<"Distanza: "<<dist<<"\n";
        distanza_etichetta->setText(QString(std::to_string(dist).c_str()));
     }
     else
     {
        distanza_etichetta->setText(QString("NA"));
     }
}
catch(std::exception e)
{
}


     log_text_browser->append(QString(log.c_str()));
     stima->setEnabled(true);
     QApplication::restoreOverrideCursor();


}

void Dialogo::on_tipo_sift_vlsift_clicked()
{
   std::string parametri=" --peak-thresh=3.4 ";
   parametri_input->setText(parametri.c_str());

}

void Dialogo::on_tipo_sift_siftgpu_clicked()
{
    std::string parametri=" -cuda -loweo ";
    parametri_input->setText(parametri.c_str());
}





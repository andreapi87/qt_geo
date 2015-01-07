#include "localizzazione.hpp"


bool file_esiste(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return ifile;
}

void rimuovi_file(const std::string& nome_file)
{
    if(file_esiste(nome_file))
    {
            boost::filesystem::wpath file(nome_file);
            boost::filesystem::remove(file);
    }
}


ExifGPS readGPS(const std::string&  file)
{
    Exiv2::ExifData exifData;
    Exiv2::Image::AutoPtr image;
    try {
    image = Exiv2::ImageFactory::open(file);
    } catch(Exiv2::Error e) {
    fprintf(stderr, "Failed to open file %s.\n", file.c_str());
    // return 0;
    }
    image->readMetadata();
    if (image.get() == NULL)
    {
        fprintf(stderr, "Failed to read file %s.\n", file.c_str());
    // return 0;
    }
    exifData = image->exifData();

    if (exifData.empty())
    {

         std::string error= ": No Exif data found in the file\n";
        throw Exiv2::Error(1, error);
    }

// Exiv2::Exifdatum& gpsVer = exifData["Exif.GPSInfo.GPSVersionID"];
    Exiv2::Exifdatum& latValue = exifData["Exif.GPSInfo.GPSLatitude"];
    Exiv2::Exifdatum& lonValue = exifData["Exif.GPSInfo.GPSLongitude"];
    Exiv2::Exifdatum& latRef = exifData["Exif.GPSInfo.GPSLatitudeRef"];
    Exiv2::Exifdatum& lonRef = exifData["Exif.GPSInfo.GPSLongitudeRef"];



    double lat;
    double lon;
    Exiv2::Rational degrees;
    Exiv2::Rational minutes;
    Exiv2::Rational seconds;
    degrees = latValue.toRational(0);
    minutes = latValue.toRational(1);
    seconds = latValue.toRational(2);
    lat = (double)degrees.first/degrees.second  + ((double)minutes.first/minutes.second/60) + ((double)seconds.first/seconds.second/3600);//((double)degrees.first / (double)degrees.second) + ((double)minutes.first / (minutes.second * 60)) + ((double)seconds.first / 3600);
    if (strcmp(latRef.toString().c_str(), "S") == 0) {
    lat = -lat;
    }
    degrees = lonValue.toRational(0);
    minutes = lonValue.toRational(1);
    seconds = lonValue.toRational(2);
    lon =  (double)degrees.first/degrees.second  + ((double)minutes.first/minutes.second/60) + ((double)seconds.first/seconds.second/3600);///((double)degrees.first / (double)degrees.second) + ((double)minutes.first / (minutes.second * 60)) + ((double)seconds.first / 3600);
    if (strcmp(lonRef.toString().c_str(), "W") == 0)
    {
        lon = -lon;
    }
    ExifGPS gps;
    gps.lat = lat;
    gps.lon = lon;
    gps.altitude = 0;
    std::cout << "EXIF: latitudine: " << latValue.toString() << " latidudineref: " << latRef.toString() << " longitudine: " << lonValue.toString() << " longitudineref: " << lonRef.toString() << std::endl;
    return gps;
}


const std::string get_path_senza_estensione(const std::string& filename)
{

  //std::cout<<"PATH+BASENAME: ";
  const int i = filename.rfind(".",filename.size());
  //std::cout<<filename.substr(0,i)<<"\n";
  return filename.substr(0,i);
}

const std::string get_basename(const std::string& filename)
{

  const int i = filename.rfind("/",filename.size());
  //std::cout<<filename.substr(i+1,filename.size())<<"\n";
  return filename.substr(i+1,filename.size());
}


localizzazione::localizzazione()
{
    boost::filesystem::path full_path( boost::filesystem::current_path() );
    std::string basepath=full_path.string();
    //std::cout<<basepath<<"\n";

    EXEC_JPG2PGM=basepath+"/eseguibili/jpeg2pgm";
    EXEC_JPG2PGM2="convert";
    EXEC_FEAT=basepath+"/eseguibili/sift";
    EXEC_FEAT2=basepath+"/eseguibili/sift2";
    EXEC_FEATGPU=basepath+"/eseguibili/siftGPU";
    EXEC_SIFT2KEY=basepath+"/eseguibili/FromSIFTtoKEY";
    EXEC_COMPDESCASSIGMENT=basepath+"/eseguibili/compute_desc_assignments";
    EXEC_ACGGEOLOCALIZER=basepath+"/eseguibili/acg_localizer_active_search";
    EXEC_SATTLER2CAMERA=basepath+"/eseguibili/conv.sh";
    EXEC_CAMERA2LATLONG=basepath+"/eseguibili/from_sattler_to_lat_long";
    this->PATH_TMP=basepath+"/tmp";
}

void localizzazione::imposta_path(const std::string&  PATH_RICOSTRUZIONE_OUT,const std::string&  PATH_CENTROIDI,const std::string&  PATH_MEDIA_CAM_CENTER,const std::string&  PATH_DESC_ASSIGN,const std::string&  N_CENTROIDI,const std::string& PATH_TMP)
{
 this->PATH_RICOSTRUZIONE_OUT=PATH_RICOSTRUZIONE_OUT;
 this->PATH_CENTROIDI=PATH_CENTROIDI;
 this->PATH_MEDIA_CAM_CENTER=PATH_MEDIA_CAM_CENTER;
 this->PATH_DESC_ASSIGN=PATH_DESC_ASSIGN;
 this->N_CENTROIDI=N_CENTROIDI;
 this->PATH_TMP=PATH_TMP;

}

std::vector<std::string> localizzazione::localizza(const std::string& path_img_jpg,char tipo_sift,const std::string& parametri,std::string& log)
{
        std::string path_file_feat=calcola_sift(path_img_jpg,tipo_sift,parametri,log);
        return acg_localizer(path_file_feat,log);


}

std::string localizzazione::calcola_sift(const std::string& path_img_jpg,char tipo_sift,const std::string& parametri, std::string& log)
{
    std::string fullname_senza_estensione=get_path_senza_estensione(path_img_jpg);
    std::string basename=get_basename(fullname_senza_estensione);
    std::string fullname_out=PATH_TMP+"/"+basename+".key";
    std::string comando;

    rimuovi_file(fullname_out);
    switch(tipo_sift)
    {
    case 0: //VKSIFT SIFT
        log+="Calcolo sift di "+path_img_jpg+" (VLSift)\n\n";


    //CALCOLO PGM
        comando=EXEC_JPG2PGM+" "+path_img_jpg+" "+PATH_TMP+"/"+basename+".pgm >> out.txt 2>errori.txt";
        system(comando.c_str());
    //CALCOLO SIFT
        //parametri=" --peak-thresh=3.4 ";
        comando=EXEC_FEAT+" "+PATH_TMP+"/"+basename+".pgm "+parametri+" -o "+fullname_out+" >> out.txt 2>errori.txt ;";
        log+=comando+"\n\n";
        system(comando.c_str());
        break;
    case 1: //SIFTGPU
        //parametri=" -cuda -loweo ";
        log+="Calcolo sift di "+path_img_jpg+" (siftGPU)\n\n";
        comando=EXEC_FEATGPU+" "+parametri+" -i "+path_img_jpg+" -o "+fullname_out+" >>out.txt 2>errori.txt" ;
        log+=comando+"\n\n";
        system(comando.c_str());

        break;
    }

    //SPOSTO LA JPG IN TEMP
    comando="cp "+path_img_jpg+" "+PATH_TMP+"/";
    system(comando.c_str());

    return fullname_out;
    //acg_localizer(PATH_TMP+"/"+basename+".key");
}

std::vector<std::string> localizzazione::acg_localizer(const std::string& path_img_sift,std::string& log)
{
    if(!file_esiste(path_img_sift))
    {
        log+="FILE SIFT NON GENERATO!IMPOSSIBILE PROSEGUIRE\n\n";
        throw std::bad_exception();
    }
    log+="calcolo geolocalizzazione di "+path_img_sift+"\n";
    std::string fullname_senza_estensione=get_path_senza_estensione(path_img_sift);
    std::string basename=get_basename(fullname_senza_estensione);

    std::string FILE_LIST_KEY=PATH_TMP+"/"+"listquery_"+basename+".txt";
    std::string FILE_LIST_SIFT=PATH_TMP+"/"+"listsift_"+basename+".txt";
    std::string FILE_LOG_SATTLER=PATH_TMP+"/"+basename+"_sattler.txt";
    std::string FILE_CAMERA=PATH_TMP+"/"+basename+".key.camera";
    std::string FILE_COORD_FINAL=PATH_TMP+"/"+basename+"_coord_final.txt";

    rimuovi_file(FILE_LIST_KEY);
    rimuovi_file(FILE_LIST_SIFT);
    rimuovi_file(FILE_LOG_SATTLER);
    rimuovi_file(FILE_CAMERA);
    rimuovi_file(FILE_COORD_FINAL);


    //GENERO FILE NECESSARI
    std::string comando="echo '"+PATH_TMP+"/"+basename+".key' > "+FILE_LIST_KEY;
    system(comando.c_str());
   //exec("echo '$fullname_senza_estensione.sift' > $FILE_LIST_SIFT");

    //ACG
    comando=EXEC_ACGGEOLOCALIZER+" "+FILE_LIST_KEY+" "+PATH_RICOSTRUZIONE_OUT+" "+N_CENTROIDI+" "+PATH_CENTROIDI+" "+PATH_DESC_ASSIGN+" 0 "+PATH_TMP+"/"+basename+"_results.txt 200 1 1 0 >> "+FILE_LOG_SATTLER+" ;";
    log+=comando+"\n\n";
    system(comando.c_str());

    //ACG2CAMERA
    comando=EXEC_SATTLER2CAMERA+" "+FILE_LOG_SATTLER+" "+FILE_LIST_KEY+" "+PATH_TMP;
    log+=comando+"\n\n";
    system(comando.c_str());

    //CAMERA2LATLONG
    comando=EXEC_CAMERA2LATLONG+" "+FILE_CAMERA+" "+PATH_MEDIA_CAM_CENTER+" > "+FILE_COORD_FINAL;
    log+=comando+"\n\n";
    system(comando.c_str());



    std::ifstream file_coord(FILE_COORD_FINAL.c_str());
    std::vector<float> coordinate(2);
    //file_coord.open(FILE_COORD_FINAL,"ios::in");
    std::string riga;
    std::string lon_marker="Longitude: ";
    std::string alt_marker=" Altitude: ";
    std::string lat_marker=" Latitude: ";
    std::string s1,s2;
    while(getline(file_coord,riga))
    {

        if(riga.find(lon_marker) !=riga.npos )
        {
            //riga.substr(riga.find(lon_marker)+lon_marker.length(),riga.find(lat_marker));
            s1=riga.substr(riga.find(lon_marker)+lon_marker.length(),riga.find(lat_marker)-(riga.find(lon_marker)+lon_marker.length()));
            s2=riga.substr(riga.find(lat_marker)+lat_marker.length(),riga.find(alt_marker)-(riga.find(lat_marker)+lat_marker.length()));
        }

    }
    log+="Longitudine: "+s1+"\nLatitudine: "+s2+"\n\n";
    std::vector<std::string> ritorno;
    ritorno.push_back(s1);
    ritorno.push_back(s2);
    return ritorno;
}

double deg2rad (double d) {
return d * M_PI / 180;
}
double rad2deg (double r) {
return r * 180/ M_PI;
}



double localizzazione::calcola_distanza(double lat1,double lon1,double lat2,double lon2,std::string& log)
{
   log+="calcolo distanza tra "+std::to_string(lat1)+","+std::to_string(lon2)+" e "+std::to_string(lat2)+","+std::to_string(lon2)+";\n\n";
   double R = 6371; // km
   double f1 = deg2rad(lat1);
   double f2 = deg2rad(lat2);
   double df = deg2rad(lat2-lat1);
   double dl = deg2rad(lon2-lon1);

   double a = sin(df/2) * sin(df/2) +
        cos(f1) * cos(f2) *
        sin(dl/2) * sin(dl/2);
   double c = 2 * atan2(sqrt(a), sqrt(1-a));

   double d = R * c;
   return d*1000;




}

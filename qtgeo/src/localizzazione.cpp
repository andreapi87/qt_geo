#include "localizzazione.hpp"


ExifGPS readGPS(std::string file)
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
if (image.get() == NULL) {
fprintf(stderr, "Failed to read file %s.\n", file.c_str());
// return 0;
}
exifData = image->exifData();
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
if (strcmp(lonRef.toString().c_str(), "W") == 0) {
lon = -lon;
}
ExifGPS gps;
gps.lat = lat;
gps.lon = lon;
gps.altitude = 0;
std::cout << "lat " << latValue.toString() << " ref " << latRef.toString() << " lon " << lonValue.toString() << " ref " << lonRef.toString() << std::endl;
return gps;
}


const std::string get_path_senza_estensione(const std::string& filename)
{

  std::cout<<"PATH+BASENAME: ";
  const int i = filename.rfind(".",filename.size());
  std::cout<<filename.substr(0,i)<<"\n";
  return filename.substr(0,i);
}

const std::string get_basename(const std::string& filename)
{
  std::cout<<"BASENAME: ";
  const int i = filename.rfind("/",filename.size());
  std::cout<<filename.substr(i+1,filename.size())<<"\n";
  return filename.substr(i+1,filename.size());
}


localizzazione::localizzazione()
{
    EXEC_JPG2PGM="./eseguibili/jpeg2pgm";
    EXEC_JPG2PGM2="convert";
    EXEC_FEAT="./eseguibili/sift";
    EXEC_FEAT2="./eseguibili/sift2";
    EXEC_SIFT2KEY="./eseguibili/FromSIFTtoKEY";
    EXEC_COMPDESCASSIGMENT="./eseguibili/compute_desc_assignments";
    EXEC_ACGGEOLOCALIZER="./eseguibili/acg_localizer_active_search";
    EXEC_SATTLER2CAMERA="./eseguibili/conv.sh";
    EXEC_CAMERA2LATLONG="./eseguibili/from_sattler_to_lat_long";
    this->PATH_TMP="./";
}

void localizzazione::imposta_path(std::string PATH_RICOSTRUZIONE_OUT,std::string PATH_CENTROIDI,std::string PATH_MEDIA_CAM_CENTER,std::string PATH_DESC_ASSIGN,std::string N_CENTROIDI)
{
 this->PATH_RICOSTRUZIONE_OUT=PATH_RICOSTRUZIONE_OUT;
 this->PATH_CENTROIDI=PATH_CENTROIDI;
 this->PATH_MEDIA_CAM_CENTER=PATH_MEDIA_CAM_CENTER;
 this->PATH_DESC_ASSIGN=PATH_DESC_ASSIGN;
 this->N_CENTROIDI=N_CENTROIDI;
 this->PATH_TMP="./";

}

std::vector<std::string> localizzazione::localizza(std::string path_img_jpg)
{
        std::string path_file_feat=calcola_sift(path_img_jpg);
        return acg_localizer(path_file_feat);


}

std::string localizzazione::calcola_sift(std::string path_img_jpg)
{
    std::cout<<"calcolo sift di "<<path_img_jpg<<"\n";
    std::string fullname_senza_estensione=get_path_senza_estensione(path_img_jpg);
    std::string basename=get_basename(fullname_senza_estensione);

    //CALCOLO PGM
    std::string comando=EXEC_JPG2PGM+" "+path_img_jpg+" "+PATH_TMP+"/"+basename+".pgm >> out.txt 2>errori.txt";
    system(comando.c_str());
    //CALCOLO SIFT
    comando=EXEC_FEAT+" "+PATH_TMP+"/"+basename+".pgm --peak-thresh=3.4 -o "+PATH_TMP+"/"+basename+".key >> out.txt 2>errori.txt ;";
    system(comando.c_str());

    //SPOSTO LA JPG IN TEMP
    comando="cp "+path_img_jpg+" "+PATH_TMP+"/";
    system(comando.c_str());

    return PATH_TMP+"/"+basename+".key";

    //acg_localizer(PATH_TMP+"/"+basename+".key");
}

std::vector<std::string> localizzazione::acg_localizer(std::string path_img_sift)
{
    std::cout<<"calcolo geolocalizzazione di "<<path_img_sift<<"\n";
    std::string fullname_senza_estensione=get_path_senza_estensione(path_img_sift);
    std::string basename=get_basename(fullname_senza_estensione);

    std::string FILE_LIST_KEY=PATH_TMP+"/"+"listquery_"+basename+".txt";
    std::string FILE_LIST_SIFT=PATH_TMP+"/"+"listsift_"+basename+".txt";
    std::string FILE_LOG_SATTLER=PATH_TMP+"/"+basename+"_sattler.txt";
    std::string FILE_CAMERA=PATH_TMP+"/"+basename+".key.camera";
    std::string FILE_COORD_FINAL=PATH_TMP+"/"+basename+"_coord_final.txt";

    //GENERO FILE NECESSARI
    std:: string comando="echo '"+PATH_TMP+"/"+basename+".key' > "+FILE_LIST_KEY;
    system(comando.c_str());
   //exec("echo '$fullname_senza_estensione.sift' > $FILE_LIST_SIFT");

    //ACG
    comando=EXEC_ACGGEOLOCALIZER+" "+FILE_LIST_KEY+" "+PATH_RICOSTRUZIONE_OUT+" "+N_CENTROIDI+" "+PATH_CENTROIDI+" "+PATH_DESC_ASSIGN+" 0 "+PATH_TMP+"/"+basename+"_results.txt 200 1 1 0 >> "+FILE_LOG_SATTLER+" ;";
    system(comando.c_str());

    //ACG2CAMERA
    comando=EXEC_SATTLER2CAMERA+" "+FILE_LOG_SATTLER+" "+FILE_LIST_KEY+" "+PATH_TMP;
    //system(comando.c_str());

    //CAMERA2LATLONG
    comando=EXEC_CAMERA2LATLONG+" "+FILE_CAMERA+" "+PATH_MEDIA_CAM_CENTER+" > "+FILE_COORD_FINAL;
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
    std::cout<<"lon:"<<s1<<"\nlat:"<<s2<<"\n";
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



double localizzazione::calcola_distanza(double lat1,double lon1,double lat2,double lon2)
{
   std::cout<<"distanza tra "<<lat1<<" "<<lon2<<" e "<<lat2<<" "<<lon2<<"\n";
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

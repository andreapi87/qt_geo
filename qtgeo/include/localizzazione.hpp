#ifndef LOCALIZZAZIONE_H
#define LOCALIZZAZIONE_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exiv2/exiv2.hpp>
#include<math.h>
#include<boost/filesystem.hpp>

typedef struct {
double lat;
double lon;
double altitude;
} ExifGPS;
ExifGPS readGPS(const std::string&  file);

class localizzazione
{
    public:
        localizzazione();
        void imposta_path(const std::string& PATH_RICOSTRUZIONE_OUT,const std::string&  PATH_CENTROIDI,const std::string&  PATH_MEDIA_CAM_CENTER,const std::string& PATH_DESC_ASSIGN,const std::string& N_CENTROIDI,const std::string& PATH_TMP);
        std::string calcola_sift(const std::string&  path_img_jpg,char tipo_sift=0,std::string parametri="");
        std::vector<std::string> acg_localizer(const std::string&  path_img_sift);
        std::vector<std::string> localizza(const std::string&  path_img_jpg,char tipo_sift=0,std::string parametri="");
        double calcola_distanza(double lat1,double lon1,double lat2,double lon2);

    private:

    //PATH FILE RICOSTRUZIONI
    std::string PATH_RICOSTRUZIONE_OUT;//="./univ31geo_translato_rispetto_centroide.out";
    std::string PATH_CENTROIDI;//="./centroids_150.txt";
    std::string PATH_MEDIA_CAM_CENTER;//="./univ31geo_valore_centroide.txt";
    std::string PATH_DESC_ASSIGN;//="./bundle.desc_assignments.integer_mean.voctree.clusters.150k.bin";
    std::string N_CENTROIDI;//=150;

    std::string PATH_TMP;

    //PATH ESEGUIBILI;
    std::string EXEC_JPG2PGM="./jpeg2pgm";
    std::string EXEC_JPG2PGM2="convert";
    std::string EXEC_FEAT="./sift";
    std::string EXEC_FEAT2="./sift2";
    std::string EXEC_FEATGPU="./siftGPU";
    std::string EXEC_SIFT2KEY="./FromSIFTtoKEY";
    std::string EXEC_COMPDESCASSIGMENT="./compute_desc_assignments";
    std::string EXEC_ACGGEOLOCALIZER="./acg_localizer_active_search";
    std::string EXEC_SATTLER2CAMERA="./conv.sh";
    std::string EXEC_CAMERA2LATLONG="./from_sattler_to_lat_long";

};



#endif // LOCALIZZAZIONE_H

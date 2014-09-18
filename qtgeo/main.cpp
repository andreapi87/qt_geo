#include<QtWidgets/QApplication>


#include <QtWidgets/QtWidgets>
#include <interfaccia.h>


using namespace std;

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    Dialogo d;
    d.show();



    return app.exec();;
}

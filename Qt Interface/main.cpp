#include <QApplication>
#include "MaFenetre.h"
#include "FenGenere.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MaFenetre fenetre;
    fenetre.show();

    return app.exec();
}

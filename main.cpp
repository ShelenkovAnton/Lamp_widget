#include "Widgets/mainwindow.h"

#include "Network/server.h" // TEST

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#else
#include <QtGui/QApplication>
#endif

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    Server s;
    s.startServer( );
    s.start( );

    MainWindow w;
    w.show( );
    return a.exec( );
}

#pragma once

#include <QtCore/qglobal.h>
#include <QtWidgets/QMainWindow>

#include "Network/networkconnection.h"

class LampWidget;
class ConnectionWidget;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow( );

    auto serverDisconnected( ) -> void;

private:
    auto onConnectClick( ) -> void;
    auto onDisconnectClick( ) -> void;

    auto onCannotConnect( ) -> void;
    auto incomingRequest( const Request& ) -> void;
    auto connected( ) -> void;

private:
    auto init( ) -> void;
    auto initConnections( ) -> void;
    auto initStyles( ) -> void;
    auto initLampWidget( ) -> void;
    auto initConnetionWidget( ) -> void;
    auto connectToServer( ) -> void;

private:
    Ui::MainWindow* ui;
    LampWidget* m_lampWidget{nullptr};
    ConnectionWidget* m_connectionWidget{nullptr};
    NetworkConnection m_networkConnection;
};

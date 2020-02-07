#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Styles/styles.h"
#include "Widgets/connectionwidget.h"
#include "Widgets/lampwidget.h"

#include <QHostAddress>

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , m_lampWidget{new LampWidget{this}}
    , m_connectionWidget{new ConnectionWidget{this}}
{
    ui->setupUi( this );
    init( );
}

MainWindow::~MainWindow( )
{
    delete ui;
}

auto MainWindow::init( ) -> void
{
    initConnections( );
    initStyles( );
    initLampWidget( );
    initConnetionWidget( );
}

auto MainWindow::initConnections( ) -> void
{
    connect( m_connectionWidget, &ConnectionWidget::sig_connect, this, &MainWindow::onConnectClick );
    connect( m_connectionWidget, &ConnectionWidget::sig_disconnect, this, &MainWindow::onDisconnectClick );

    connect( &m_networkConnection, &NetworkConnection::sig_cannot_connect, this, &MainWindow::onCannotConnect );
    connect( &m_networkConnection, &NetworkConnection::sig_request, this, &MainWindow::incomingRequest );
    connect( &m_networkConnection, &NetworkConnection::sig_connected, this, &MainWindow::connected );
}

auto MainWindow::initStyles( ) -> void
{
    Styles::aplyMainStyle( this );
}

auto MainWindow::connected( ) -> void
{
    m_connectionWidget->setState( State::connected );
}

auto MainWindow::onDisconnectClick( ) -> void
{
    m_networkConnection.blockSignals( true );
    m_networkConnection.disconnectServer( );
    m_networkConnection.stopReconnction( );
    m_networkConnection.blockSignals( false );
}

auto MainWindow::onConnectClick( ) -> void
{
    connectToServer( );
}

auto MainWindow::connectToServer( ) -> void
{
    const auto address = m_connectionWidget->getAdress( );
    const auto port    = m_connectionWidget->getPort( );

    m_networkConnection.connectToServer( address, port );
}

auto MainWindow::onCannotConnect( ) -> void
{
    m_connectionWidget->setState( State::disconnected );
}

auto MainWindow::initLampWidget( ) -> void
{
    if ( const auto layout = ui->frLampWidget->layout( ) )
    {
        layout->addWidget( m_lampWidget );
    }
    else
    {
        assert( false );
    }
}

auto MainWindow::incomingRequest( const Request& request ) -> void
{
    const auto state = request.getState( );

    switch ( state )
    {
    case LampAction::on:
        m_lampWidget->setState( true );
        break;
    case LampAction::off:
        m_lampWidget->setState( false );
        break;
    case LampAction::changeColor:
        m_lampWidget->setState( true );
        m_lampWidget->setColor( request.getColor( ) );
        break;
    default:
        break;
    }
}

auto MainWindow::initConnetionWidget( ) -> void
{
    if ( const auto layout = ui->frNetworkWidget->layout( ) )
    {
        layout->addWidget( m_connectionWidget );
    }
    else
    {
        assert( false );
    }
}

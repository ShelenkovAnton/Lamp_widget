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
    connect( &m_networkConnection, &NetworkConnection::sig_cannot_connect, this, &MainWindow::onCannotConnect );
    connect( &m_networkConnection, &NetworkConnection::sig_disconnected, this, &MainWindow::serverDisconnected );
    connect( &m_networkConnection, &NetworkConnection::sig_request, this, &MainWindow::incomingRequest );
    connect( &m_networkConnection, &NetworkConnection::sig_connected, this, &MainWindow::connected );
}

auto MainWindow::initStyles( ) -> void
{
    Styles::aplyMainStyle( this );
    Styles::aplyMainStyle( m_connectionWidget );
}

auto MainWindow::serverDisconnected( ) -> void
{
    m_connectionWidget->setState( State::reconnection );
    connectToServer( );
}

auto MainWindow::connected( ) -> void
{
    m_connectionWidget->setState( State::connected );
}

auto MainWindow::onConnectClick( ) -> void
{
    const auto state = m_connectionWidget->getState( );

    qDebug( ) << static_cast<int>( state );

    switch ( state )
    {
    case State::connected:
    case State::reconnection:
        m_networkConnection.disconnectServer( );
        m_connectionWidget->setState( State::disconnected );
        break;
    case State::disconnected:
        m_connectionWidget->setState( State::reconnection );
        connectToServer( );
        break;
    }
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

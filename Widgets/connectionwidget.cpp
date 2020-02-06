#include "connectionwidget.h"
#include "ui_connectionwidget.h"
#include <QDebug>

#include "Styles/styles.h"
#include <QHostAddress>

#include "statewidget.h"

ConnectionWidget::ConnectionWidget( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::ConnectionWidget )
    , m_stateWidget{new StateWidget{this}}
{
    ui->setupUi( this );
    init( );
}

ConnectionWidget::~ConnectionWidget( )
{
    delete ui;
}

auto ConnectionWidget::init( ) -> void
{
    initConnections( );
    initStateWidget( );
    initStyles( );
    initAddressValidator( );
    setState( State::disconnected );
}

auto ConnectionWidget::initAddressValidator( ) -> void
{
    const QString ipRange = "(([ 0]+)|([ 0]*[0-9] *)|([0-9][0-9] )|([ 0][0-9][0-9])|(1[0-9][0-9])|([2][0-4][0-9])|(25[0-5]))";
    const QRegExp ipRegex( "^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$" );
    const auto ipValidator = new QRegExpValidator( ipRegex, this );

    ui->txtServer->setValidator( ipValidator );
    ui->txtServer->setInputMask( "000.000.000.000" );
    ui->txtServer->setCursorPosition( 0 );
}

auto ConnectionWidget::initStateWidget( ) -> void
{
    if ( const auto layout = ui->frStateWidget->layout( ) )
    {
        layout->addWidget( m_stateWidget );
    }
    else
    {
        assert( false );
    }
}

auto ConnectionWidget::setState( State state ) -> void
{
    m_state = state;
    m_stateWidget->setState( state );

    constexpr auto connectText   = "Discconect";
    constexpr auto disconectText = "Connect";
    constexpr auto reconnectText = "Stop reconnection";

    switch ( state )
    {
    case State::connected:
        ui->btnConnect->setText( connectText );
        break;
    case State::disconnected:
        ui->btnConnect->setText( disconectText );
        break;
    case State::reconnection:
        ui->btnConnect->setText( reconnectText );
        break;
    }
}

auto ConnectionWidget::on_btnRestore( ) -> void
{
    constexpr auto defaultPort = 9999;
    ui->txtServer->clear( );
    ui->spPort->setValue( defaultPort );
}

auto ConnectionWidget::initStyles( ) -> void
{
    ui->spPort->setButtonSymbols( QAbstractSpinBox::NoButtons );

    auto palette = ui->spPort->palette( );
    palette.setColor( QPalette::Text, Qt::white );
    ui->spPort->setPalette( palette );
}

auto ConnectionWidget::initConnections( ) -> void
{
    connect( ui->btnRestore, &QPushButton::clicked, this, &ConnectionWidget::on_btnRestore );
    connect( ui->btnConnect, &QPushButton::clicked, this, &ConnectionWidget::on_btnConnect );
}

auto ConnectionWidget::on_btnConnect( ) -> void
{
    switch ( m_state )
    {
    case State::connected:
        setState( State::disconnected );
        emit sig_disconnect( );
        break;
    case State::disconnected:
        setState( State::reconnection );
        emit sig_connect( );
        break;
    case State::reconnection:
        setState( State::disconnected );
        emit sig_disconnect( );
        break;
    }
}

auto ConnectionWidget::getAdress( ) const -> QHostAddress
{
    return QHostAddress{ui->txtServer->text( )};
}

auto ConnectionWidget::getPort( ) const -> uint16_t
{
    return static_cast<uint16_t>( ui->spPort->value( ) );
}

auto ConnectionWidget::getState( ) const -> State
{
    return m_state;
}

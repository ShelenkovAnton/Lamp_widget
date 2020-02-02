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
    connect( ui->btnConnect, &QPushButton::clicked, this, &ConnectionWidget::sig_connect );
}

auto ConnectionWidget::getAdress( ) const -> QHostAddress
{
    // TODO: validate text
    const auto text = ui->txtServer->text( ).isEmpty( ) ? "127.0.0.1" : ui->txtServer->text( );
    return QHostAddress{text};
}

auto ConnectionWidget::getPort( ) const -> uint16_t
{
    return static_cast<uint16_t>( ui->spPort->value( ) );
}

auto ConnectionWidget::getState( ) const -> State
{
    if ( m_stateWidget )
    {
        return m_stateWidget->getState( );
    }
    assert( false );
    return State::disconnected;
}

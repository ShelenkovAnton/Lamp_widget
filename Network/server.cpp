#include "server.h"
#include "request.h"
#include <QByteArray>

Server::Server( )
{
    connect( &m_timer, &QTimer::timeout, this, &Server::sendRequest );
}

auto Server::incomingConnection( qintptr handle ) -> void
{
    qDebug( ) << "incoming connection, handle: " << handle;

    m_socket.setSocketDescriptor( handle );

    connect( &m_socket, &QTcpSocket::readyRead, this, &Server::readyRead );
    connect( &m_socket, &QTcpSocket::disconnected, this, &Server::clientDisconnected );

    m_socket.write( "you are connected to server" );
}

auto Server::generateRequest( ) -> QByteArray
{
    QByteArray arr;
    const auto action = getAction( );

    arr.append( static_cast<char>( action ) );

    if ( action == LampAction::changeColor )
    {
        const auto size = getSize( );

        if ( size < 16 )
        {
            arr.append( QByteArray::number( 0 ) );
        }

        arr.append( QByteArray::number( size, 16 ) );

        arr.append( static_cast<char>( getColor( ) ) );
        arr.append( static_cast<char>( getColor( ) ) );
        arr.append( static_cast<char>( getColor( ) ) );
    }
    else
    {
        arr.append( QByteArray::number( 0, 16 ) );
        arr.append( QByteArray::number( 0, 16 ) );
    }

    return arr;
}

auto Server::getColor( ) const -> uint8_t
{
    return std::rand( ) % 255;
}

auto Server::getSize( ) const -> uint16_t
{
    const auto num = std::rand( ) % 100;
    return ( num < 3 ) ? ( std::rand( ) % 65535 ) : 3;
}

auto Server::getAction( ) const -> LampAction
{
    const auto num = std::rand( ) % 100;

    if ( num < 30 )
    {
        return LampAction::on;
    }
    else if ( num < 60 )
    {
        return LampAction::off;
    }
    else if ( num < 90 )
    {
        return LampAction::changeColor;
    }
    return LampAction::unknown;
}

auto Server::sendRequest( ) -> void
{
    const auto request = generateRequest( );
    m_socket.write( request );
}

auto Server::readyRead( ) -> void
{
}

auto Server::clientDisconnected( ) -> void
{
}

auto Server::startServer( ) -> void
{
    if ( !listen( QHostAddress::LocalHost, 9999 ) )
    {
        qDebug( ) << "server error";
    }
}

auto Server::start( ) -> void
{
    const auto timeout = 1 + ( std::rand( ) % 10 );
    m_timer.start( std::chrono::seconds( timeout ) );
}

auto Server::stop( ) -> void
{
    m_timer.stop( );
}

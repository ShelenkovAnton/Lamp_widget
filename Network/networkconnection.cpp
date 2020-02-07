#include "networkconnection.h"

#include <QHostAddress>

#include <QTimer>

NetworkConnection::NetworkConnection( QObject* parent )
    : QObject( parent )
    , m_socket{new QTcpSocket( this )}
{
    init( );
}

auto NetworkConnection::init( ) -> void
{
    initConnections( );
}

auto NetworkConnection::initConnections( ) -> void
{
    connect( m_socket, &QTcpSocket::readyRead, this, &NetworkConnection::incomingData );
    connect( &m_timer, &QTimer::timeout, this, &NetworkConnection::reconnect );
}

auto NetworkConnection::stopReconnction( ) -> void
{
    m_connectionState = false;
}

auto NetworkConnection::incomingData( ) -> void
{
    const auto data = m_socket->readAll( );

    const Request request{data};

    if ( request.valid( ) )
    {
        emit sig_request( request );
    }
}

auto NetworkConnection::sendRequest( QByteArray data ) -> void
{
    if ( !data.isEmpty( ) )
    {
        switch ( static_cast<LampAction>( static_cast<int>( data[0] ) ) )
        {
        case LampAction::on:
        case LampAction::off:
            emit sig_request( Request{data.left( 4 )} );
            data.remove( 0, 4 );
            sendRequest( data );
            break;
        case LampAction::changeColor: {
            const auto length = data.mid( 1, 3 ).toInt( );

            if ( data.size( ) < length + 4 )
                return;

            emit sig_request( Request{data.left( length + 4 )} );
            data.remove( 0, 4 + length );
            sendRequest( data );
            break;
        }
        case LampAction::unknown:
            return;
        }
    }
}

auto NetworkConnection::connectToServer( const QHostAddress& address, const uint16_t port ) -> void
{
    m_port    = port;
    m_address = address;

    m_connectionState = true;

    reconnect( );
}

auto NetworkConnection::reconnect( ) -> void
{
    m_socket->connectToHost( m_address, m_port );

    if ( isConnected( ) )
    {
        m_timer.stop( );
        m_currentAttempt = 0;
        emit sig_connected( );
        return;
    }

    if ( ( m_currentAttempt++ < m_attemptCount ) && m_connectionState )
    {
        m_timer.start( 200 );
    }
    else
    {
        m_currentAttempt = 0;
        m_timer.stop( );
        emit sig_cannot_connect( );
    }
}

auto NetworkConnection::isConnected( ) const -> bool
{
    return ( m_socket->state( ) == QAbstractSocket::ConnectedState );
}

auto NetworkConnection::disconnectServer( ) -> void
{
    m_socket->close( );
    m_socket->disconnectFromHost( );
}

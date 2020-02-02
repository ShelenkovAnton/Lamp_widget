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
    connect( m_socket, &QTcpSocket::disconnected, this, &NetworkConnection::sig_disconnected );
    connect( &m_timer, &QTimer::timeout, this, &NetworkConnection::reconnect );
}

auto NetworkConnection::incomingData( ) -> void
{
    emit sig_request( Request{m_socket->readAll( )} );
}

auto NetworkConnection::connectToServer( const QHostAddress& address, const uint16_t port ) -> void
{
    m_socket->connectToHost( address, port );

    m_port    = port;
    m_address = address;

    if ( !isConnected( ) )
    {
        if ( m_currentAttempt++ < m_attemptCount )
        {
            m_timer.start( 10 );
        }
        else
        {
            emit sig_cannot_connect( );
        }
    }
    else
    {
        emit sig_connected( );
    }
}

auto NetworkConnection::reconnect( ) -> void
{
    m_socket->connectToHost( m_address, m_port );
}

auto NetworkConnection::isConnected( ) const -> bool
{
    return ( m_socket->state( ) != QAbstractSocket::UnconnectedState );
}

auto NetworkConnection::disconnectServer( ) -> void
{
    return m_socket->disconnectFromHost( );
}

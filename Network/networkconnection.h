#pragma once
#include <QtCore/qglobal.h>

#include "Network/request.h"

#include <QHostAddress>
#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class NetworkConnection : public QObject
{
    Q_OBJECT
public:
    explicit NetworkConnection( QObject* = nullptr );
    ~NetworkConnection( ) = default;

    auto connectToServer( const QHostAddress&, const uint16_t ) -> void;
    auto isConnected( ) const -> bool;
    auto disconnectServer( ) -> void;

    auto stopReconnction( ) -> void;

signals:
    void sig_cannot_connect( );
    void sig_request( Request );
    void sig_connected( );

private:
    auto init( ) -> void;
    auto initConnections( ) -> void;
    auto incomingData( ) -> void;
    auto reconnect( ) -> void;
    auto sendRequest( QByteArray ) -> void;

private:
    QTcpSocket* m_socket{nullptr};

    QTimer m_timer;

    QHostAddress m_address;
    quint16 m_port{0};

    int16_t m_attemptCount{30};
    int16_t m_currentAttempt{0};
    bool m_connectionState{true};
};

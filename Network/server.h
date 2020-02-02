#pragma once
#include <QTcpServer>
#include <QtCore/qglobal.h>

#include <QTcpSocket>
#include <QTimer>

enum class LampAction;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server( );
    virtual ~Server( ) = default;

    auto startServer( ) -> void;

    auto start( ) -> void;
    auto stop( ) -> void;

protected:
    auto incomingConnection( qintptr ) -> void override;

private:
    auto readyRead( ) -> void;
    auto clientDisconnected( ) -> void;
    auto sendRequest( ) -> void;

    auto generateRequest( ) -> QByteArray;
    auto getAction( ) const -> LampAction;
    auto getSize( ) const -> uint16_t;
    auto getColor( ) const -> uint8_t;

private:
    QTcpSocket m_socket;
    QTimer m_timer;
};

#pragma once

#include <QtWidgets/QWidget>

#include "Widgets/statewidget.h"

namespace Ui
{
class ConnectionWidget;
}

class QHostAddress;

class ConnectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWidget( QWidget* parent = nullptr );
    ~ConnectionWidget( );

    auto getAdress( ) const -> QHostAddress;
    auto getPort( ) const -> uint16_t;

    auto setState( State ) -> void;
    auto getState( ) const -> State;

signals:
    void sig_connect( );

private:
    auto on_btnRestore( ) -> void;

    auto initConnections( ) -> void;

    auto init( ) -> void;
    auto initStyles( ) -> void;

    auto initStateWidget( ) -> void;

private:
    Ui::ConnectionWidget* ui;
    StateWidget* m_stateWidget{nullptr};
};

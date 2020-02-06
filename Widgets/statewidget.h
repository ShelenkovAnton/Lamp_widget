#pragma once

#include <QtCore/qglobal.h>

#include <QWidget>

enum class State
{
    connected    = 0,
    disconnected = 1,
    reconnection = 2
};

class StateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StateWidget( QWidget* );

    auto setState( const State ) -> void;
    auto getState( ) const -> State;

protected:
    auto paintEvent( QPaintEvent* ) -> void override;

private:
    QColor m_color{Qt::transparent};
};

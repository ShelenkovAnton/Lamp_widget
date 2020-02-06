#include "statewidget.h"

#include <QPainter>

StateWidget::StateWidget( QWidget* parent )
    : QWidget( parent )
{
    setMinimumSize( 50, 50 );
}

auto StateWidget::paintEvent( QPaintEvent* ) -> void
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen( QPen{Qt::white, 1} );
    painter.setBrush( QBrush{m_color} );

    const auto radius = std::min( rect( ).width( ), rect( ).height( ) );

    painter.drawEllipse( 0, 0, radius, radius );
    painter.drawLine( radius / 2, 0, radius / 2, rect( ).height( ) );

    painter.drawArc( QRect{0, 0, radius, radius / 4}, -590, -1700 );
    painter.drawArc( QRectF( radius * 0.026, radius * 0.23, radius * 0.955, radius * 0.25 ), 0, -2880 );
    painter.drawArc( QRectF( 0, radius * 0.5, radius, radius * 0.25 ), -300, -2250 );

    painter.end( );
}

auto StateWidget::setState( const State state ) -> void
{
    switch ( state )
    {
    case State::connected:
        m_color = Qt::green;
        break;
    case State::disconnected:
        m_color = Qt::red;
        break;
    case State::reconnection:
        m_color = Qt::gray;
        break;
    }

    update( );
}

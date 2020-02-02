#include "lampwidget.h"

#include <QDebug>
#include <QPainter>

//#include "Styles/styles.h"

LampWidget::LampWidget( QWidget* parent )
    : QWidget( parent )
{
    // Styles::aplyMainStyle( this );
}

auto LampWidget::paintEvent( QPaintEvent* ) -> void
{
    auto rect = getRect( );
    paintLamp( rect );
    paintLight( rect );
    paintSwitch( rect );
}

auto LampWidget::getRect( ) const -> QRect
{
    auto paintRect = rect( );
    if ( ( static_cast<float>( paintRect.width( ) ) / static_cast<float>( paintRect.height( ) ) ) > 2 )
    {
        paintRect.setWidth( paintRect.height( ) * 2 );
    }
    else
    {
        paintRect.setHeight( paintRect.width( ) / 2 );
    }

    const auto margin = paintRect.size( ) * 0.2;
    paintRect         = paintRect.adjusted( margin.width( ), margin.height( ), -margin.width( ), -margin.height( ) );
    return paintRect;
}

auto LampWidget::paintSwitch( const QRect& rect ) -> void
{
    const auto margin = mState ? rect.width( ) * 0.04 : 0;

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen( QPen{Qt::white} );

    const auto rectX = rect.x( ) + margin;
    const auto rectY = rect.y( );
    const auto rectW = rect.width( );
    const auto rectH = rect.height( );

    QPainterPath path;
    path.moveTo( rectW * 0.245 + rectX, 0.37 * rectH + rectY );

    path.lineTo( rectW * 0.25 + rectX, 0.35 * rectH + rectY );
    path.lineTo( rectW * 0.255 + rectX, 0.35 * rectH + rectY );
    path.lineTo( rectW * 0.26 + rectX, 0.33 * rectH + rectY );
    path.lineTo( rectW * 0.29 + rectX, 0.33 * rectH + rectY );
    path.lineTo( rectW * 0.295 + rectX, 0.35 * rectH + rectY );
    path.lineTo( rectW * 0.3 + rectX, 0.35 * rectH + rectY );
    path.lineTo( rectW * 0.305 + rectX, 0.37 * rectH + rectY );

    painter.drawPath( path );

    painter.setPen( QPen( QColor( 210, 210, 210 ) ) );
    painter.drawLine( QPointF{rectW * 0.255 + rectX, 0.35 * rectH + rectY}, QPointF{rectW * 0.295 + rectX, 0.35 * rectH + rectY} );
    painter.end( );
}

auto LampWidget::paintLamp( const QRect& rect ) -> void
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen( QPen{Qt::white} );

    const auto rectX = rect.x( );
    const auto rectY = rect.y( );
    const auto rectW = rect.width( );
    const auto rectH = rect.height( );

    const QPointF p1{rectW * 0.5 + rectX, 0.375 * rectH + rectY};
    const QPointF p2{rectW * 0.625 + rectX, 0.25 * rectH + rectY};
    const QPointF p3{rectW * 0.625 + rectX, 0.75 * rectH + rectY};
    const QPointF p4{rectW * 0.5 + rectX, 0.625 * rectH + rectY};
    const QPointF p5{p1};
    const QPointF p6{static_cast<qreal>( rect.x( ) ), 0.375 * rectH + rectY};
    const QPointF p7{static_cast<qreal>( rect.x( ) ), 0.625 * rectH + rectY};
    const QPointF p8{p4};

    QPainterPath path;
    path.moveTo( p1 );
    path.lineTo( p2 );
    path.lineTo( p3 );
    path.lineTo( p4 );
    path.lineTo( p5 );
    path.lineTo( p6 );
    path.lineTo( p7 );
    path.lineTo( p8 );

    painter.drawPath( path );
    painter.end( );
}

auto LampWidget::paintLight( const QRect& rect ) -> void
{
    if ( !mState )
    {
        return;
    }

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );

    const auto margin = rect.topLeft( );
    const auto rectW  = rect.width( );
    const auto rectH  = rect.height( );
    const auto rectC  = rect.center( );

    const auto p1 = QPointF{rectW * 0.625, rectH * 0.25} + margin;
    const auto p2 = QPointF{rectW * 0.75, rectH * 0.1} + margin;
    const auto p3 = QPointF{rectW * 0.75, rectH * 0.9} + margin;
    const auto p4 = QPointF{rectW * 0.625, rectH * 0.75} + margin;

    QRectF arcRect{p2.x( ) - rectW * 0.2, p2.y( ), rectW * 0.4, rectH * 0.8};

    QPainterPath path;
    path.moveTo( p1 );
    path.lineTo( p2 );
    path.arcTo( arcRect, 90, -180 );
    path.lineTo( p3 );
    path.lineTo( p4 );

    QRadialGradient radialGrad( {p1.x( ), static_cast<qreal>( rectC.y( ) )}, arcRect.width( ) * 0.75 );

    QColor color{mColor};

    for ( int i = 1; i < 255; ++i )
    {
        color.setAlpha( i );
        radialGrad.setColorAt( 1 / i, color );
    }
    painter.fillPath( path, radialGrad );
    painter.end( );
}

auto LampWidget::setColor( const QColor& color ) -> void
{
    mColor = color;
    update( );
}

auto LampWidget::getColor( ) const -> QColor
{
    return mColor;
}

auto LampWidget::setState( bool state ) -> void
{
    if ( mState != state )
    {
        mState = state;
        update( );
    }
}

auto LampWidget::getState( ) const -> bool
{
    return mState;
}

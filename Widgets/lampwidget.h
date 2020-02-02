#pragma once
#include <QtCore/qglobal.h>

#include <QWidget>

class LampWidget : public QWidget
{
public:
    explicit LampWidget( QWidget* = nullptr );

    auto setColor( const QColor& ) -> void;
    auto getColor( ) const -> QColor;

    auto setState( bool ) -> void;
    auto getState( ) const -> bool;

protected:
    auto paintEvent( QPaintEvent* ) -> void override;

private:
    auto paintLamp( const QRect& ) -> void;
    auto paintLight( const QRect& ) -> void;
    auto paintSwitch( const QRect& ) -> void;
    auto getRect( ) const -> QRect;

private:
    QColor mColor{Qt::green};
    bool mState{true};
};

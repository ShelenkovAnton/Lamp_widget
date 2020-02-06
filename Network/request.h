#pragma once
#include <QtCore/qglobal.h>

#include <QColor>

enum class LampAction
{
    unknown     = 0x0,
    on          = 0x12,
    off         = 0x13,
    changeColor = 0x20,
};

class Request
{
public:
    explicit Request( const QByteArray& );

    auto setAction( const LampAction ) -> void;
    auto setAction( const uint8_t ) -> void;

    auto getAction( ) const -> LampAction;

    auto setColor( ) -> void;

    auto getColor( ) const -> QColor;

    auto getState( ) const -> LampAction;

    auto valid( ) const -> bool;

private:
    auto parceRequest( const QByteArray& ) -> void;
    auto parceColor( const QByteArray& ) -> void;

    auto setRGBColor( const ushort, const ushort, const ushort ) -> bool;
    auto setStringColor( const QString& ) -> bool;
    auto setColor( QColor&& color ) -> bool;

private:
    LampAction m_action{LampAction::unknown};
    QColor m_color{Qt::white};
};

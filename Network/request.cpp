#include "request.h"

#include <QByteArray>

Request::Request( const QByteArray& request )
{
    parceRequest( request );
}

auto Request::setAction( const LampAction type ) -> void
{
    m_action = type;
}

auto Request::valid( ) const -> bool
{
    return m_action != LampAction::unknown;
}

auto Request::setAction( const uint8_t value ) -> void
{
    if ( static_cast<LampAction>( value ) == LampAction::on )
    {
        m_action = LampAction::on;
    }
    else if ( static_cast<LampAction>( value ) == LampAction::off )
    {
        m_action = LampAction::off;
    }
    else if ( static_cast<LampAction>( value ) == LampAction::changeColor )
    {
        m_action = LampAction::changeColor;
    }
    else
    {
        m_action = LampAction::unknown;
    }
}

auto Request::getAction( ) const -> LampAction
{
    return m_action;
}

auto Request::getColor( ) const -> QColor
{
    return m_color;
}

auto Request::parceColor( const QByteArray& color ) -> void
{
    if ( color.size( ) == 3 )
    {
        const auto red   = static_cast<uint8_t>( color[0] );
        const auto green = static_cast<uint8_t>( color[1] );
        const auto blue  = static_cast<uint8_t>( color[2] );

        if ( !setRGBColor( red, green, blue ) )
        {
            setAction( LampAction::unknown );
        }
    }
    else
    {
        if ( !setStringColor( color ) )
        {
            setAction( LampAction::unknown );
        }
    }
}

auto Request::parceRequest( const QByteArray& request ) -> void
{
    const auto size = request.size( );

    if ( size == 0 )
        return;

    const auto action = static_cast<LampAction>( static_cast<int>( request[0] ) );

    setAction( action );

    const auto length = request.mid( 1, 3 ).toInt( );

    if ( request.size( ) < length + 4 )
    {
        return;
    }

    parceColor( request.mid( 3, length ) );
}

auto Request::setRGBColor( const ushort red, const ushort green, const ushort blue ) -> bool
{
    return setColor( QColor{red, green, blue} );
}

auto Request::setStringColor( const QString& str ) -> bool
{
    return setColor( QColor{str} );
}

auto Request::setColor( QColor&& color ) -> bool
{
    const auto valid{color.isValid( )};
    if ( valid )
    {
        m_color = color;
    }
    return valid;
}

auto Request::getState( ) const -> LampAction
{
    return m_action;
}

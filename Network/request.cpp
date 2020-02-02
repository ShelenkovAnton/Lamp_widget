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

auto Request::parceRequest( const QByteArray& request ) -> void
{
    const auto size = request.size( );

    if ( ( size == 3 ) || ( size == 6 ) )
    {
        setAction( static_cast<uint8_t>( request.at( 0 ) ) );
    }

    if ( size == 6 )
    {
        const auto length = request.mid( 1, 2 ).toUShort( );
        if ( length != 3 )
        {
            setAction( LampAction::unknown );
        }
        else
        {
            const auto red   = static_cast<uint8_t>( request[3] );
            const auto green = static_cast<uint8_t>( request[4] );
            const auto blue  = static_cast<uint8_t>( request[5] );

            if ( !setRGBColor( red, green, blue ) )
            {
                setAction( LampAction::unknown );
            }
        }
    }
}

auto Request::setRGBColor( const ushort red, const ushort green, const ushort blue ) -> bool
{
    QColor color{red, green, blue};
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

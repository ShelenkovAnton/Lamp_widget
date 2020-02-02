#include "styles.h"

#include <QWidget>

#include <QDebug>

auto Styles::aplyBackgroundStyle( QWidget* const widget, const QColor& color ) -> void
{
    const auto style = QString{R"(%1{ background-color: %2; })"}.arg( widget->objectName( ) ).arg( color.name( ) );

    widget->setStyleSheet( widget->styleSheet( ) + style );
}

auto Styles::aplyGroupBoxStyle( QWidget* const widget ) -> void
{
    const auto style = QString( R"(
    QGroupBox
    {
        color: white;
    }
)" );

    widget->setStyleSheet( widget->styleSheet( ) + style );
}

auto Styles::aplySelectedStyle( QWidget* const widget ) -> void
{
    widget->setStyleSheet( widget->styleSheet( ) + getSelectedStyle( ) );
}

auto Styles::removeSelectedStyle( QWidget* const widget ) -> void
{
    widget->setStyleSheet( widget->styleSheet( ).remove( getSelectedStyle( ) ) );
}

auto Styles::getSelectedStyle( ) -> QString
{
    const auto style = QString( R"(
    QFrame
    {
        background-color: %1;
    }
    )" )
                           .arg( Styles::colors.selectedFrameColor );
    return style;
}

auto Styles::aplyMainStyle( QWidget* const widget ) -> void
{
    widget->setStyleSheet( widget->styleSheet( ) + getMainStyle( ) );
}

auto Styles::getMainStyle( ) -> QString
{
    const auto style = QString( R"(
    QWidget
    {
        background-color: %1;
    }

    QAbstractButton
    {
        background-color: %2;
        color: white;
    }
    QAbstractButton:checked
    {
        background-color: %3;
    }
    QAbstractButton:hover
    {
        background-color: %4;
    }
    QGroupBox
    {
        color: white;
    }
    QComboBox
    {
        color: white;
    }
    QLineEdit
    {
        color:white;
        width: 800;
    }
    QLabel
    {
        color:white;
    }
)" )

                           .arg( Styles::colors.windowBackground )
                           .arg( Styles::colors.btnBackground )
                           .arg( Styles::colors.checkedBtnBackground )
                           .arg( Styles::colors.hoveredBtnBackground );

    return style;
}

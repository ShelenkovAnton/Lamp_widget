#pragma once

#include <QColor>

class QWidget;

class Styles
{
public:
    static auto aplyBackgroundStyle( QWidget* const, const QColor& ) -> void;
    static auto aplyGroupBoxStyle( QWidget* const ) -> void;
    static auto aplySelectedStyle( QWidget* const ) -> void;
    static auto removeSelectedStyle( QWidget* const ) -> void;

    static auto aplyMainStyle( QWidget* const ) -> void;

    static const struct Colors
    {
        static constexpr auto windowBackground     = "#27292D";
        static constexpr auto btnBackground        = "#1F2023";
        static constexpr auto checkedBtnBackground = "#0000FF";
        static constexpr auto hoveredBtnBackground = "#414144";
        static constexpr auto selectedFrameColor   = "#AAAAAA";
    } colors;

private:
    static auto getSelectedStyle( ) -> QString;
    static auto getMainStyle( ) -> QString;
};

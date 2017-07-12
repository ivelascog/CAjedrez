#include "UIButtonLogic.h"

BorderColor UIButtonLogic::getBorder() const
{
    return border;
}

void UIButtonLogic::setBorder(const BorderColor &value)
{
    border = value;
}

BGColor UIButtonLogic::getBg() const
{
    return bg;
}

void UIButtonLogic::setBg(const BGColor &value)
{
    bg = value;
}

FGColor UIButtonLogic::getFg() const
{
    return fg;
}

void UIButtonLogic::setFg(const FGColor &value)
{
    fg = value;
}

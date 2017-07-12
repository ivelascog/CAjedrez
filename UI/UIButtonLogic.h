#ifndef UIBUTTONLOGIC_H
#define UIBUTTONLOGIC_H

enum BGColor {
    def = 0, inMoveRange = 1, inAttackRange= 2, inAttackRangeandHostile = 3, obstacle = 4, selected = 5, debug = 6
};

enum BorderColor {
    noBorder = 0, posToDefendMe = 1, posToDefendAlly = 2, posToDefendEnemy = 3
};

enum FGColor {
    me = 0, enemy = 1, ally = 2, white = 3
};

class UIButtonLogic
{
    BGColor bg  = def;
    FGColor fg = me;
    BorderColor border = noBorder;
public:
    BGColor getBg() const;
    void setBg(const BGColor &value);
    FGColor getFg() const;
    void setFg(const FGColor &value);
    BorderColor getBorder() const;
    void setBorder(const BorderColor &value);
};

#endif // UIBUTTONLOGIC_H

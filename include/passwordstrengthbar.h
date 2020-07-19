#ifndef PASSWORDSTRENGTHBAR_H
#define PASSWORDSTRENGTHBAR_H

#include <QProgressBar>

class PasswordStrengthBar : public QProgressBar
{
public:
    PasswordStrengthBar(QWidget * parent = nullptr);

private:
    enum class State{ Useless, Weak, Medium, Strong };

    void updateStyle();

    State currentState;
};

#endif // PASSWORDSTRENGTHBAR_H

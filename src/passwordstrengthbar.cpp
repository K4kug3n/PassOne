#include "passwordstrengthbar.h"

#include <iostream>

PasswordStrengthBar::PasswordStrengthBar(QWidget * parent) :
    QProgressBar(parent),
    currentState(State::Useless)
{
    connect(this, &QProgressBar::valueChanged, this, [&](){
        updateStyle();
    });

    setValue(0);
}

void PasswordStrengthBar::updateStyle()
{
    int value{ this->value() };

    QString style{"QProgressBar{ text-align: center; \
        border: 1px solid black; }"};

    if(value <= 25 && currentState != State::Useless){
         QString uselessStyle{ "QProgressBar::chunk { \
               background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, \
                 stop: 0 rgb(255, 0, 0), \
                 stop: 1 rgb(255, 0, 0)); }" };

         uselessStyle += style;
         setStyleSheet(uselessStyle);

         currentState = State::Useless;
    }
    else if(value <= 50 && currentState != State::Weak){
         QString weakStyle{ "QProgressBar::chunk { \
                    background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, \
                      stop: 0 rgb(255, 0, 0), \
                      stop: 0.4999 rgb(255, 0, 0), \
                      stop: 0.5 rgb(255, 191, 0), \
                      stop: 1 rgb(255, 191, 0)); }" };

         weakStyle += style;
         setStyleSheet(weakStyle);

         currentState = State::Weak;
    }
    else if(value <= 75 && currentState != State::Medium){
         QString mediumStyle{ "QProgressBar::chunk { \
                       background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, \
                         stop: 0 rgb(255, 0, 0), \
                         stop: 0.3332 rgb(255, 0, 0), \
                         stop: 0.3333 rgb(255, 191, 0), \
                         stop: 0.6665 rgb(255, 191, 0), \
                         stop: 0.6666 rgb(128, 255, 0), \
                         stop: 1 rgb(128, 255, 0)); }" };

         mediumStyle += style;
         setStyleSheet(mediumStyle);

         currentState = State::Medium;
    }
    else if(currentState != State::Strong){
         QString strongStyle{ "QProgressBar::chunk { \
                              background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, \
                                stop: 0 rgb(255, 0, 0), \
                                stop: 0.2499 rgb(255, 0, 0), \
                                stop: 0.25 rgb(255, 191, 0), \
                                stop: 0.4999 rgb(255, 191, 0), \
                                stop: 0.5 rgb(128, 255, 0), \
                                stop: 0.7499 rgb(128, 255, 0), \
                                stop: 0.75 rgb(0, 255, 0), \
                                stop: 1 rgb(0, 255, 0)); }" };

        strongStyle += style;
        setStyleSheet(strongStyle);

        currentState = State::Strong;
    }
}

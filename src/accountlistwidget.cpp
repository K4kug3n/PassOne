#include "accountlistwidget.h"

#include <iostream>

AccountListWidget::AccountListWidget(int nbPerLine):
    grid(new QGridLayout()),
    y(0),
    x(0),
    xMax(nbPerLine)

{
    setupInterface();
}

void AccountListWidget::addAccount(AccountPresentation *account)
{
    setupPresentation(account);
    addWidget(account);
}

void AccountListWidget::addButton(QPushButton *button)
{
    setupButton(button);
    addWidget(button);
}

void AccountListWidget::setupPresentation(AccountPresentation *account)
{
    account->setFixedSize(80,80);
    account->setStyleSheet("background-color: #0db5b2; border-radius:10px");

    connect(account, &AccountPresentation::clicked, this, [&](size_t id){
        emit presentationClicked(id);
    });
}

void AccountListWidget::setupButton(QPushButton *button)
{
    button->setFixedSize(80,80);
}

void AccountListWidget::addWidget(QWidget *widget)
{
    if(x == xMax){
        y++;
        x = 0;
    }

    grid->addWidget(widget, y, x);

    x++;
}

void AccountListWidget::setupInterface()
{
    setLayout(grid);
    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(10);
}


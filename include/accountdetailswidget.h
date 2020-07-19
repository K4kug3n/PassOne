#ifndef ACCOUNTDETAILSWIDGET_H
#define ACCOUNTDETAILSWIDGET_H

#include <iostream>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "passwordstrengthbar.h"

class AccountDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    AccountDetailsWidget();

    void setName(std::string const& name);
    void setLogin(std::string const& login);
    void setPassword(std::string const& password);
    void setId(size_t newId);

signals:
    void back();
    void editAccount(size_t id);
    void deleteAccount(size_t id);

private:
    void setupInterface();
    void setupConnections();

    size_t id;

    QLabel * siteNameLabel;
    QLabel * loginLabel;
    QLabel * passwordLabel;

    PasswordStrengthBar * passwordStrengthBar;

    QPushButton * backButton;
    QPushButton * editButton;
    QPushButton * deleteButton;
};

#endif // ACCOUNTDETAILSWIDGET_H

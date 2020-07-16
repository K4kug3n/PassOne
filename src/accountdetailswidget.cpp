#include "accountdetailswidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

AccountDetailsWidget::AccountDetailsWidget():
    siteNameLabel(new QLabel(this)),
    loginLabel(new QLabel(this)),
    passwordLabel(new QLabel(this)),
    backButton(new QPushButton(this)),
    editButton(new QPushButton(this)),
    deleteButton(new QPushButton(this))
{
    setupInterface();
    setupConnections();
}

void AccountDetailsWidget::setName(std::string const& name)
{
    siteNameLabel->setText(QString::fromStdString(name));
}

void AccountDetailsWidget::setLogin(std::string const& login)
{
    loginLabel->setText(QString::fromStdString(login));
}

void AccountDetailsWidget::setPassword(std::string const& password)
{
    passwordLabel->setText(QString::fromStdString(password));
}

void AccountDetailsWidget::setId(size_t newId)
{
    id = newId;
}

void AccountDetailsWidget::setupInterface()
{
    QVBoxLayout * mainLayout{ new QVBoxLayout };

    /* Set title */
    QLabel * title{ new QLabel( "Account Details", this ) };
    QFont font{ title->font() };
    font.setPointSize(15);
    title->setFont(font);
    mainLayout->addWidget(title, 0, Qt::AlignCenter);

    QVBoxLayout * detailsLayout{ new QVBoxLayout };
    detailsLayout->setSpacing(50);

    /* Set Name */
    QHBoxLayout * nameLayout{ new QHBoxLayout };
    nameLayout->setSpacing(10);
    nameLayout->addWidget(new QLabel{ "Site name : ", this }, 0, Qt::AlignRight);
    siteNameLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    nameLayout->addWidget(siteNameLabel, 0, Qt::AlignLeft);
    //mainLayout->addLayout(nameLayout);
    detailsLayout->addLayout(nameLayout);

    /* Set Login */
    QHBoxLayout * loginLayout{ new QHBoxLayout };
    loginLayout->setSpacing(10);
    loginLayout->addWidget(new QLabel{ "Your login : ", this }, 0, Qt::AlignRight);
    loginLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    loginLayout->addWidget(loginLabel, 0, Qt::AlignLeft);
    //mainLayout->addLayout(loginLayout);
    detailsLayout->addLayout(loginLayout);

    /* Set Password */
    QHBoxLayout * passwordLayout{ new QHBoxLayout };
    passwordLayout->setSpacing(10);
    passwordLayout->addWidget(new QLabel{ "Your password : ", this }, 0, Qt::AlignRight);
    passwordLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    passwordLayout->addWidget(passwordLabel, 0, Qt::AlignLeft);
    //mainLayout->addLayout(passwordLayout);
    detailsLayout->addLayout(passwordLayout);

    mainLayout->addLayout(detailsLayout);

    /* Set buttons */
    QHBoxLayout * buttonLayout{ new QHBoxLayout };
    buttonLayout->setMargin(50);

    backButton->setStyleSheet("background-image: url(res/back.png);\
                               border-style: none;\
                               border-radius: 40px;");
    backButton->setFixedSize(60,60);
    buttonLayout->addWidget(backButton);

    editButton->setStyleSheet("background-image: url(res/edit.png);\
                               border-style: none;\
                               border-radius: 40px;");
    editButton->setFixedSize(60,60);
    buttonLayout->addWidget(editButton);

    deleteButton->setStyleSheet("background-image: url(res/delete.png);\
                                 border-style: none;\
                                 border-radius: 40px;");
    deleteButton->setFixedSize(60,60);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void AccountDetailsWidget::setupConnections()
{
    connect(backButton, &QPushButton::clicked, this, [&](){
        emit back();
    });

    connect(editButton, &QPushButton::clicked, this, [&](){
        emit editAccount(id);
    });

    connect(deleteButton, &QPushButton::clicked, this, [&](){
        emit deleteAccount(id);
    });
}

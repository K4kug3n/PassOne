#include "accountformwidget.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QProgressBar>

#include "utils.h"

AccountFormWidget::AccountFormWidget():
    titleLabel(createLabel("", 15)),
    nameLineEdit(new QLineEdit()),
    loginLineEdit(new QLineEdit()),
    passwordLineEdit(new QLineEdit()),
    passwordStrengthBar(new PasswordStrengthBar()),
    cancelButton(new QPushButton("Cancel")),
    acceptButton(new QPushButton("Accept"))

{
    setupInterface();
    setupConnections();
}

void AccountFormWidget::setTitle(const std::string &title)
{
    titleLabel->setText(QString::fromStdString(title));
}

void AccountFormWidget::setSiteName(const std::string &siteName)
{
    nameLineEdit->setText(QString::fromStdString(siteName));
}

void AccountFormWidget::setLogin(const std::string &login)
{
    loginLineEdit->setText(QString::fromStdString(login));
}

void AccountFormWidget::setPassword(const std::string &pw)
{
    passwordLineEdit->setText(QString::fromStdString(pw));
}

void AccountFormWidget::setId(size_t newId){
    id = newId;
}

void AccountFormWidget::cancel()
{
    reset();
    emit canceled();
}

void AccountFormWidget::valid()
{
    QString name{ nameLineEdit->text() };
    QString login{ loginLineEdit->text() };
    QString password{ passwordLineEdit->text() };
    std::optional<size_t> currentId{ id };

    reset();

    emit valided(name, login, password, currentId);
}

void AccountFormWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Enter){
        valid();
    }
}

void AccountFormWidget::setupInterface()
{
    QVBoxLayout * mainLayout{ new QVBoxLayout() };
    mainLayout->setContentsMargins(50, 20, 50, 50);

    /* Set Title */
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    /* Set Form */
    QFormLayout * formLayout{ new QFormLayout() };
    formLayout->setSpacing(50);
    formLayout->setContentsMargins(0, 20, 0, 50);

    formLayout->addRow(createLabel(tr("Site name : "), 10), nameLineEdit);
    formLayout->addRow(createLabel(tr("Login : "), 10), loginLineEdit);
    formLayout->addRow(createLabel(tr("Password : "), 10), passwordLineEdit);

    mainLayout->addLayout(formLayout);

    /* Set Pwd Strength Bar */
    QHBoxLayout * passwordStrengthLayout{ new QHBoxLayout() };
    passwordStrengthLayout->setContentsMargins(0, 0, 0, 50);
    passwordStrengthLayout->addWidget(createLabel(tr("Password Strength : "), 10));

    passwordStrengthBar->setValue(0);
    passwordStrengthLayout->addWidget(passwordStrengthBar);

    mainLayout->addLayout(passwordStrengthLayout);

    /* Set Button */
    QHBoxLayout * buttonLayout{ new QHBoxLayout() };
    buttonLayout->setSpacing(100);

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(acceptButton);

    mainLayout->addLayout(buttonLayout);

    /* Apply Main Layout */
    setLayout(mainLayout);
}

void AccountFormWidget::setupConnections()
{
    connect(acceptButton, &QPushButton::clicked, this, &AccountFormWidget::valid);
    connect(cancelButton, &QPushButton::clicked, this, &AccountFormWidget::cancel);

    connect(passwordLineEdit, &QLineEdit::textEdited, this, [&](const QString &text){
        unsigned score{ getPasswordStrength(text.toStdString()) };

        passwordStrengthBar->setValue(score);
    });
}

void AccountFormWidget::reset()
{
    nameLineEdit->clear();
    loginLineEdit->clear();
    passwordLineEdit->clear();

    id = std::nullopt;
}

QLabel * AccountFormWidget::createLabel(QString const& text, int fontSize)
{
    QLabel * label{ new QLabel(text) };

    QFont font{ label->font() };
    font.setPointSize(fontSize);
    label->setFont(font);

    return label;
}

#include "mainwindow.h"

#include <QInputDialog>
#include <QDesktopWidget>
#include <QPushButton>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      //mainArea(new QScrollArea()),
      presentationList(new AccountListWidget(6)),
      accountForm(new AccountFormWidget()),
      accountDetails(new AccountDetailsWidget())
{
    setupInterface();
    setupConnections();
}

void MainWindow::showDetails(size_t id, std::string const& name, std::string const& login, std::string const& pw)
{
    takeCentralWidget();

    accountDetails->setName(name);
    accountDetails->setLogin(login);
    accountDetails->setPassword(pw);
    accountDetails->setId(id);

    setCentralWidget(accountDetails);
}

void MainWindow::showAccountList()
{
    /*QWidget * central{ new QWidget() };
    QVBoxLayout * layout{ new QVBoxLayout() };

    layout->addWidget(presentationList);
    central->setLayout(layout);

    mainArea->setWidget(central);*/

    takeCentralWidget();
    setCentralWidget(presentationList);
}

void MainWindow::showForm()
{
    takeCentralWidget();
    setCentralWidget(accountForm);
}

void MainWindow::resetPresentation()
{
    presentationList->deleteLater();

    presentationList = new AccountListWidget(6);

    setupAccountList();
}

void MainWindow::addAccount(size_t id, std::string const& name)
{
    presentationList->addAccount(new AccountPresentation(id, name));
}

AccountFormWidget &MainWindow::getForm() const
{
    return *accountForm;
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupInterface()
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.5);
    //setCentralWidget(mainArea);
    showAccountList();

    setupAccountList();
}

void MainWindow::setupConnections()
{
    connect(accountForm, &AccountFormWidget::valided, this, [&](QString const& name, QString const& login, QString const& password, std::optional<size_t> const& id){
        this->notifyInput(login.toStdString(), password.toStdString(), name.toStdString(), id);
        this->showAccountList();
    });

    connect(accountForm, &AccountFormWidget::canceled, this, [&](){
        this->showAccountList();
    });

    connect(accountDetails, &AccountDetailsWidget::deleteAccount, this, [&](size_t id){
        this->notifyRemove(id);
    });

    connect(accountDetails, &AccountDetailsWidget::editAccount, this, [&](size_t id){
        this->notifyEditAsked(id);
    });

    connect(accountDetails, &AccountDetailsWidget::back, this, [&](){
        this->showAccountList();
    });
}

void MainWindow::setupAccountList()
{
    QPushButton * button{ new QPushButton() };
    button->setStyleSheet("background-image: url(res/plus.png);\
                           border-style: none;\
                           border-radius: 40px;");

    presentationList->addButton(button);

    connect(button, &QPushButton::clicked, this, [&](){ this->notifyInputAsked(); });

    connect(presentationList, &AccountListWidget::presentationClicked, this, [&](size_t id){
        this->notifyDetail(id);
    });
}

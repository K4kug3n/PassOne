#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "observable.h"
#include "accountlistwidget.h"
#include "accountformwidget.h"
#include "accountdetailswidget.h"

#include <QMainWindow>
#include <QBoxLayout>
#include <QScrollArea>

class MainWindow : public QMainWindow, public Observable
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void showDetails(size_t id, std::string const& name, std::string const& login, std::string const& pw);
    void showAccountList();
    void showForm();

    void resetPresentation();

    void addAccount(size_t id, std::string const& name);

    AccountFormWidget & getForm() const;

    ~MainWindow();

private:
    void setupInterface();
    void setupConnections();

    void setupAccountList();

    //QScrollArea * mainArea;

    AccountListWidget * presentationList;
    AccountFormWidget * accountForm;
    AccountDetailsWidget * accountDetails;
};

#endif // MAINWINDOW_H

#ifndef ACCOUNTLISTWIDGET_H
#define ACCOUNTLISTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include <unordered_map>
#include <array>

#include "accountpresentation.h"

class AccountListWidget : public QWidget
{
    Q_OBJECT
public:
    AccountListWidget(int nbPerLine);

    void addAccount(AccountPresentation * account);
    void addButton(QPushButton * button);

signals:
    void presentationClicked(size_t id);

private:
    void setupPresentation(AccountPresentation * account);
    void setupButton(QPushButton * button);
    void addWidget(QWidget * widget);

    void setupInterface();

    QGridLayout * grid;

    int y;
    int x;
    int xMax;
};

#endif // ACCOUNTLISTWIDGET_H

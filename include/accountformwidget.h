#ifndef ACCOUNTFORMWIDGET_H
#define ACCOUNTFORMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <string>
#include <optional>

class AccountFormWidget : public QWidget
{
    Q_OBJECT

public:
    AccountFormWidget();

    void setTitle(std::string const& title);
    void setSiteName(std::string const& siteName);
    void setLogin(std::string const& login);
    void setPassword(std::string const& pw);
    void setId(size_t newId);

signals:
    void valided(QString const& name, QString const& login, QString const& password, std::optional<size_t> const& id);
    void canceled();

private slots:
    void cancel();
    void valid();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void setupInterface();
    void setupConnections();

    void reset();

    QLabel * createLabel(QString const& text, int fontSize);

    QLabel * titleLabel;

    QLineEdit * nameLineEdit;
    QLineEdit * loginLineEdit;
    QLineEdit * passwordLineEdit;

    QPushButton * cancelButton;
    QPushButton * acceptButton;

    std::optional<size_t> id;
};

#endif // ACCOUNTFORMWIDGET_H

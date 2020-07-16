#ifndef ACCOUNTPRESENTATION_H
#define ACCOUNTPRESENTATION_H

#include <QWidget>

class AccountPresentation : public QWidget
{
    Q_OBJECT
public:
    AccountPresentation(size_t id, std::string const& name);

    void paintEvent(QPaintEvent *) override;

signals:
    void clicked(size_t id);

protected:
    void mouseReleaseEvent(QMouseEvent * event) override;

private:
    void setupInterface(std::string const& name);

    size_t id;
};

#endif // ACCOUNTPRESENTATION_H

#include "accountpresentation.h"

#include <QHBoxLayout>
#include <QLabel>

#include <iostream>

#include <QStyleOption>
#include <QPainter>

AccountPresentation::AccountPresentation(size_t id, std::string const& name) :
    id(id)
{
    setupInterface(name);
}

void AccountPresentation::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p{ this };
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void AccountPresentation::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked(id);
}

void AccountPresentation::setupInterface(std::string const& name)
{
    QLabel * nameLabel{ new QLabel(QString::fromStdString(name)) };

    QHBoxLayout * centralLayout{ new QHBoxLayout() };
    centralLayout->addWidget(nameLabel, 0, Qt::AlignCenter);

    setLayout(centralLayout);
}

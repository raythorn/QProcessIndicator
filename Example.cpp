#include "Example.h"

#include "QProcessIndicator/QProcessIndicator.h"

Example::Example(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(256, 64);

    QProcessIndicator *indicator = new QProcessIndicator(this);
    indicator->setGeometry(16, 16, 64, 32);
    indicator->setType(QProcessIndicator::line_rotate);
    indicator->start();

    indicator = new QProcessIndicator(this);
    indicator->setGeometry(96, 16, 64, 32);
    indicator->setType(QProcessIndicator::ball_rotate);
    indicator->start();

    indicator = new QProcessIndicator(this);
    indicator->setGeometry(176, 16, 64, 32);
    indicator->setType(QProcessIndicator::line_scale);
    indicator->setInterval(125);
    indicator->start();
}

Example::~Example()
{
}

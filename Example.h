#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QWidget>

class Example : public QWidget
{
    Q_OBJECT

public:
    explicit Example(QWidget *parent = 0);
    ~Example();

private:

};

#endif // EXAMPLE_H

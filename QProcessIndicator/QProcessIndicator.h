#ifndef QPROCESSINDICATOR_H
#define QPROCESSINDICATOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QColor>
#include <QTimer>
#include <QPainter>

class QProcessIndicator : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int m_type READ type WRITE setType)
    Q_PROPERTY(QColor m_color READ color WRITE setColor)
    Q_PROPERTY(int m_interval READ interval WRITE setInterval)

public:
    QProcessIndicator(QWidget *parent = 0);
    ~QProcessIndicator();

    enum {
        line_rotate,
        line_scale,
        ball_rotate,
    };

    void paintEvent(QPaintEvent *e);

    void start();
    void stop();

    int type() {return m_type;}
    void setType(int type) {m_type = type;}

    QColor &color() {return m_color;}
    void setColor(QColor &color) {m_color = color;}

    int interval() {return m_interval;}
    void setInterval(int interval) {m_interval = interval;}

private slots:
    void onTimeout();

private:
    void drawRotateLine(QPainter *painter);
    void drawScaleLine(QPainter *painter);
    void drawRotateBall(QPainter *painter);

private:
    int m_type;
    int m_interval;
    QColor m_color;

    int m_angle;
    qreal m_scale;

    QTimer *m_timer;
};

#endif // QPROCESSINDICATOR_H

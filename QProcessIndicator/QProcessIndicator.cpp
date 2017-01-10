#include "QProcessIndicator.h"

#include <QDebug>
#include <QtGlobal>
#include <QPoint>

#define SPIN_INTERVAL   60

QProcessIndicator::QProcessIndicator(QWidget *parent)
    : QWidget(parent),
      m_type(line_rotate),
      m_interval(SPIN_INTERVAL),
      m_angle(0),
      m_scale(0.0f),
      m_color(Qt::black)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

QProcessIndicator::~QProcessIndicator()
{
    stop();

    delete m_timer;
}

void QProcessIndicator::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    if(!m_timer->isActive())
    {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    switch(m_type)
    {
    case line_rotate:
        drawRotateLine(&painter);
        break;
    case line_scale:
        drawScaleLine((&painter));
        break;
    case ball_rotate:
        drawRotateBall(&painter);
        break;
    }
}

void QProcessIndicator::start()
{
    m_timer->start(m_interval);
}

void QProcessIndicator::stop()
{
    m_timer->stop();
}

void QProcessIndicator::onTimeout()
{
    switch(m_type)
    {
    case line_rotate:
    case ball_rotate:
        m_angle = (m_angle + 45) % 360;
        break;
    case line_scale:
        m_scale += 0.1f;
        m_scale = m_scale > .5f ? 0.0f : m_scale;
        break;
    }

    update();
}

void QProcessIndicator::drawRotateLine(QPainter *painter)
{
    int width = qMin(this->width(), this->height());

    int outerRadius = (width - 4) * 0.5f;
    int innerRadius = outerRadius * 0.42f;

    int capsuleHeight = outerRadius - innerRadius;
    int capsuleWidth  = (width > 32 ) ? capsuleHeight * .32f : capsuleHeight * .40f;
    int capsuleRadius = capsuleWidth / 2;

    for (int i = 0; i < 8; i++)
    {
        QColor color = m_color;

        color.setAlphaF(1.0f - (i / 8.0f));
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);

        painter->save();

        painter->translate(rect().center());
        painter->rotate(m_angle - i * 45.0f);

        painter->drawRoundedRect(-capsuleWidth * 0.5, -(innerRadius + capsuleHeight), capsuleWidth, capsuleHeight, capsuleRadius, capsuleRadius);

        painter->restore();
    }
}

void QProcessIndicator::drawScaleLine(QPainter *painter)
{
    int height = qMin(this->width(), this->height());

    qreal lineWidth = height * 0.15f;
    qreal lineHeight = height * 0.9f;
    qreal lineRadius = lineWidth / 2.0f;
    qreal lineGap = lineWidth;
    qreal margin = (this->width() - lineWidth * 5 - lineGap * 4) / 2.0f;

    for(int i = 0; i < 5; i++)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(m_color);

        int tmp = m_scale * 10 + i + 1;
        if(tmp > 5)
        {
            tmp = 5 - tmp % 5;
        }

        qDebug() << tmp;

        qreal scale = 0.5f + tmp * 0.1f;
        qreal h = lineHeight * scale;

        painter->save();

        painter->translate(QPointF(margin + (lineWidth + lineGap) * i, this->height() / 2));

        painter->drawRoundedRect(0, -h / 2.0f, lineWidth, h, lineRadius, lineRadius);

        painter->restore();
    }
}

void QProcessIndicator::drawRotateBall(QPainter *painter)
{
    int width = qMin(this->width(), this->height());

    int outerRadius = (width - 4) * 0.5f;
    int innerRadius = outerRadius * 0.78f;

    int capsuleRadius = (outerRadius - innerRadius) / 2;

    for(int i = 0; i < 8; i++)
    {
        QColor color = m_color;

        color.setAlphaF(1.0f - (i / 8.0f));

        painter->setPen(Qt::NoPen);
        painter->setBrush(color);

        qreal radius = capsuleRadius * (1.0f - (i / 16.0f));

        painter->save();

        painter->translate(rect().center());
        painter->rotate(m_angle - i * 45.0f);

        QPointF centre = QPointF(-capsuleRadius, -(innerRadius + capsuleRadius));
        painter->drawEllipse(centre, radius * 2, radius * 2);

        painter->restore();
    }
}

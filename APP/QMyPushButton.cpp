#include "QMyPushButton.h"
#include <QPainter>
#include <QColor>
#include <QDebug>

QMyPushButton::QMyPushButton(QWidget* parent) : QPushButton(parent)
{
    m_isPressed = false;

    m_countDownEnable = false;     // 倒计时效果使能
    m_countDownTm = 0;          // 倒计时时间
    m_remainTm = 0;

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    setAttribute(Qt::WA_AcceptTouchEvents);
}

void QMyPushButton::onTimeOut()
{
    if (m_remainTm > 0) {
        m_remainTm -= COUNT_DOWN_INTERVAL_TM;
        update();
    } else {
        m_remainTm = 0;
        m_timer->stop();
    }
}

bool QMyPushButton::event(QEvent *e)
{
    bool ret = true;

     qDebug() << e->type();

    switch (e->type()) {
    case QEvent::TouchBegin:
    case QEvent::MouseButtonPress:
        emit QPushButton::pressed();
        m_isPressed = true;
        update();
        //e->ignore();
        break;
    case QEvent::TouchEnd:
    case QEvent::MouseButtonRelease:
        emit QPushButton::released();
        emit QPushButton::clicked(true);
        m_isPressed = false;
        update();
        if ((true == m_countDownEnable) && (0 == m_remainTm)) {
            m_remainTm = m_countDownTm;
            m_timer->start(COUNT_DOWN_INTERVAL_TM);
        }
        //e->ignore();
        break;
    default:
        ret = QPushButton::event(e);
        break;
    }

    return ret;
}

void QMyPushButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addEllipse(2, 2, width()-4,  height()-4);
    painter.setClipPath(path);

    if (false == m_isPressed) {
        if (!m_normalIcon.isNull()) {
            painter.drawPixmap(0, 0, width(), height(), m_normalIcon);
        }
    } else {
        if (!m_pressedIcon.isNull()) {
            painter.drawPixmap(0, 0, width(), height(), m_pressedIcon);
        } else {
            if (!m_normalIcon.isNull()) {
                painter.drawPixmap(0, 0, width(), height(), m_normalIcon);
            }
        }
    }

    if (m_countDownEnable) {
        QColor color(50, 50, 50, 150);
        QBrush brush(color);
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        int angle = 360 * m_remainTm / m_countDownTm;
        painter.drawPie(2, 2, width()-4,  height()-4, 90*16, angle*16);

        if (m_remainTm > 0) {
            QPen pen(QColor(55, 55, 200));
            painter.setPen(pen);
            QFont font = painter.font();
            font.setPixelSize(80);
            painter.setFont(font);
            QString str = QString::number(m_remainTm / 1000 + 1);
            painter.drawText(2, 2, width()-4,  height()-4, Qt::AlignCenter, str);
        }
    }

    painter.setRenderHint(QPainter::Antialiasing, false);

    //QPushButton::paintEvent(e);
}

void QMyPushButton::setNormalIcon(QString path)
{
    m_normalIcon.load(path);
}

void QMyPushButton::setHoverIcon(QString path)
{
    m_hoverIcon.load(path);
}

void QMyPushButton::setPressedIcon(QString path)
{
    m_pressedIcon.load(path);
}

void QMyPushButton::setCountDownEnable(bool ret)
{
    m_countDownEnable = ret;
}

void QMyPushButton::setCountDownTime(int tm)
{
    m_countDownTm = tm * 1000;
}

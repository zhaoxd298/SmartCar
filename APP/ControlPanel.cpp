#include "ControlPanel.h"
#include <QPainter>
#include <QTouchEvent>
#include <QMouseEvent>
#include <QPointF>
#include <math.h>

#include <QDebug>

ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent)
{
    m_pressFlg = false;
    m_lastAngle = 0;
    m_touchPix.load(":/img/touch.png");
    m_ctlBackground.load(":/img/ctlBackground.png");

    resizeEvent(NULL);

    m_angle = 0;
    m_lastAngle = 0;
    m_speed = 0;
    m_lastSpeed = 0;

    setAttribute(Qt::WA_AcceptTouchEvents);
}


void ControlPanel::paintEvent(QPaintEvent *)
{
    QPainter painter;

    painter.begin(this);

    int x = CTL_CIRCLE_OFFSET;
    int y = height() - m_ctlCircleRadius*2 - CTL_CIRCLE_OFFSET;

    //painter.drawEllipse(x, y, m_ctlCircleRadius*2, m_ctlCircleRadius*2);
    painter.drawPixmap(x, y, m_ctlCircleRadius*2, m_ctlCircleRadius*2, m_ctlBackground);

    QRect rect = getTouchPixRect();

    painter.drawPixmap(rect, m_touchPix);

    painter.end();
}

void ControlPanel::resizeEvent(QResizeEvent*)
{
    int w = this->width();
    int h = this->height();

    qDebug() << w << ":" << h;

    m_ctlCircleRadius = ((w < h) ? (w-CTL_CIRCLE_OFFSET * 2) : (h-CTL_CIRCLE_OFFSET * 2)) / 2;
    m_touchPixRadius = m_ctlCircleRadius * 2 / 5;
}

void ControlPanel::mouseMove(QPoint point)
{
    //m_curPos = event->pos();
    m_curPos = point;
    //qDebug() << m_curPos;

    screenCoordToMathCoord();

    update();

    m_angle = getAngle();
    int angleDiff = m_angle - m_lastAngle;

    m_speed = getSpeed();
    int speedDiff = m_speed - m_lastSpeed;

    if ((angleDiff<=-1) || (angleDiff>=1) || (speedDiff>=5) || (speedDiff<=-5)) {
        m_lastAngle = m_angle;
        m_lastSpeed = m_speed;
        //qDebug() << "Control the car, angle:" << m_angle << "speed:" << m_speed;

        ctlCar();
    }

    //event->ignore();
}

void ControlPanel::mousePressed()
{
    m_pressFlg = true;
}

void ControlPanel::mouseReleased()
{
    m_pressFlg = false;
    update();

    //m_msgDialog->ctlCar(true, 0, 0);
    m_speed = 0;
    m_angle = 90;

    ctlCar();
}

bool ControlPanel::event(QEvent *e)
{
    bool ret = true;

    //qDebug() << e->type();
    QMouseEvent* mouseEvent = NULL;
    QTouchEvent* touchEvent = NULL;
    QPointF pointF;

    switch (e->type()) {
    case QEvent::TouchBegin:
    case QEvent::MouseButtonPress:
        mousePressed();
        //e->ignore();
        break;
    case QEvent::TouchUpdate:
        touchEvent = dynamic_cast<QTouchEvent*>(e);
        if (NULL != touchEvent) {
            pointF = touchEvent->touchPoints()[0].pos();
            mouseMove(QPoint(pointF.x(), pointF.y()));
        }
        //e->ignore();
        break;
    case QEvent::MouseMove:
        mouseEvent = dynamic_cast<QMouseEvent*>(e);
        if (NULL != mouseEvent) {
            mouseMove(mouseEvent->pos());
        }
        //e->ignore();
        break;
    case QEvent::TouchEnd:
    case QEvent::MouseButtonRelease:
        mouseReleased();
        //e->ignore();
        break;
    default:
        ret = QWidget::event(e);
        break;
    }

    return ret;
}

QPoint ControlPanel::getTouchPixPoint()
{
    int x, y;

    int curX = m_curMathCoord.x();
    int curY = m_curMathCoord.y();

    int radius = sqrt(curX*curX + curY*curY);

    if (radius > (m_ctlCircleRadius-m_touchPixRadius)) {     // 触摸点超出了控制圆圈范围
        x = curX * (m_ctlCircleRadius-m_touchPixRadius) / radius + m_mathCoordCenter.x();
        y = m_mathCoordCenter.y() - (curY * (m_ctlCircleRadius-m_touchPixRadius) / radius);
    } else {    // 控制点在控制圆圈范围内
        x = m_curPos.x();
        y = m_curPos.y();
    }

    return QPoint(x, y);
}

QRect ControlPanel::getTouchPixRect()
{
    QRect rect;
    int x, y;

    if (m_pressFlg) {   // 鼠标按下或触摸屏幕
        QPoint point = getTouchPixPoint();
        x = point.x() - m_touchPixRadius;
        y = point.y() - m_touchPixRadius;
    } else {    // 没有鼠标按下或没有触摸屏幕
        x = CTL_CIRCLE_OFFSET + m_ctlCircleRadius - m_touchPixRadius;
        y = height() - CTL_CIRCLE_OFFSET - m_ctlCircleRadius - m_touchPixRadius;
    }

    rect.setX(x);
    rect.setY(y);
    rect.setWidth(m_touchPixRadius*2);
    rect.setHeight(m_touchPixRadius*2);

    return rect;
}

int ControlPanel::getAngle()
{
    double x = m_curMathCoord.x();
    double y = m_curMathCoord.y();

    double radian, angle;

    if ((x>0) && (y>=0)) {         // 第一象限
        radian = atan(y / x);
        angle = radian * 180 / 3.14;
    } else if ((x<=0) && (y>0)) {   // 第二象限
        radian = atan(-x / y);
        angle = 90 + radian * 180 / 3.14;
    } else if ((x<0) && (y<=0)) {    // 第三象限
        radian = atan(y / x);
        angle = 180 + radian * 180 / 3.14;
    } else if ((x>=0) && (y<0)) {    // 第四象限
        radian = atan(x / -y);
        angle = 270 + radian * 180 / 3.14;
    }

    //qDebug() << "m_curMathCoord:" << m_curMathCoord;
    //qDebug() << "radian:" << radian << "angle:" << angle;

    return static_cast<int>(angle);
}


int ControlPanel::getSpeed()
{
    int r = sqrt(m_curMathCoord.x()*m_curMathCoord.x() + m_curMathCoord.y()*m_curMathCoord.y());

    int speed = r * 200 / (m_ctlCircleRadius - m_touchPixRadius);
    if (speed > 200) {
        speed = 200;
    }

    return speed;
}

void ControlPanel::screenCoordToMathCoord()
{
    int x = CTL_CIRCLE_OFFSET + m_ctlCircleRadius;
    int y = height() - CTL_CIRCLE_OFFSET - m_ctlCircleRadius;

    m_mathCoordCenter.setX(x);
    m_mathCoordCenter.setY(y);

    m_curMathCoord.setX(m_curPos.x() - x);
    m_curMathCoord.setY(y - m_curPos.y());
}



void ControlPanel::ctlCar()
{
    bool dir = true;
    int angle = 0;

    if (m_angle <= 180) {
        dir = true;
        angle = 90 - m_angle;
    } else {
        dir = false;
        angle = -(270 - m_angle);
    }

    // qDebug() << "dir:" << dir << "speed:" << m_speed << "angle:" << angle;
    /*QString s = tr("方向：") + tr(dir ? "前进" : "倒退") + tr("   角度：") +
            QString::number(abs(angle)) + tr("   速度：") + QString::number(m_speed);
    m_noticLabel->setText(s);
    m_msgDialog->ctlCar(dir, m_speed, angle);
    */
}

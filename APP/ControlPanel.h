#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>
#include <QPixmap>

class ControlPanel : public QWidget
{
    Q_OBJECT
private:
    QPoint m_curPos;                // 当前物理坐标（屏幕坐标）
    QPoint m_mathCoordCenter;       // 数学（直角）坐标圆点
    QPoint m_curMathCoord;          // 当前数学（直角）坐标
    QPixmap m_touchPix;             // 保存触摸点图片
    QPixmap m_ctlBackground;
    int m_angle;
    int m_lastAngle;                // 上次角度值
    int m_speed;
    int m_lastSpeed;                // 上次速度

    bool m_pressFlg;
    int m_ctlCircleRadius;
    int m_touchPixRadius;
    enum {
        CTL_CIRCLE_OFFSET   = 5,   // 控制圆圈离屏幕边缘距离 30
    };

private:
    QPoint getTouchPixPoint();      // 获取触摸点图像中心坐标
    QRect getTouchPixRect();        // 获取触摸点图像Rect
    int getAngle();                 // 获取角度[0,360]
    int getSpeed();                 // 获取小车速度
    void screenCoordToMathCoord();  // 屏幕坐标转换到数学（直角）坐标

    void ctlCar();

    void mouseMove(QPoint point);
    void mousePressed();
    void mouseReleased();
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    //void mouseMoveEvent(QMouseEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);

    bool event(QEvent *e);
public:
    explicit ControlPanel(QWidget *parent = 0);

signals:

public slots:
};

#endif // CONTROLPANEL_H

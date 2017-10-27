#ifndef QMYPUSHBUTTON_H
#define QMYPUSHBUTTON_H

#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QEvent>
#include <QTimer>

class QMyPushButton : public QPushButton
{
    Q_OBJECT
private:
    bool m_isPressed;

    enum {COUNT_DOWN_INTERVAL_TM = 25};
    bool m_countDownEnable;     // 倒计时效果使能
    int m_countDownTm;          // 倒计时时间，单位 ms
    int m_remainTm;             // 倒计时剩余时间，单位 ms
    QTimer* m_timer;

    QPixmap m_normalIcon;
    QPixmap m_hoverIcon;
    QPixmap m_pressedIcon;

private slots:
    void onTimeOut();

protected:
    bool event(QEvent *e);
    void paintEvent(QPaintEvent *);

public:
    QMyPushButton(QWidget* parent = 0);
    void setNormalIcon(QString path);
    void setHoverIcon(QString path);
    void setPressedIcon(QString path);

    void setCountDownEnable(bool ret);
    void setCountDownTime(int tm);      // tm单位 s
};

#endif // QMYPUSHBUTTEN_H

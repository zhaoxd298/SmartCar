#include "NewWindow.h"
#include <QPainter>
#include <QDebug>
#include <math.h>
#include <QMessageBox>
#include <QPainter>
#include <QFont>
#include <QApplication>
#include <QDesktopWidget>

NewWindow::NewWindow(QWidget *parent) : QWidget(parent)
{
#if defined(Q_OS_WIN32) || defined (Q_OS_MACX)
    this->resize(640, 480);
#else
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取设备屏幕大小
    QRect screenRect = desktopWidget->screenGeometry();
    resize(screenRect.width(), screenRect.height());
#endif

    //setAttribute(Qt::WA_AcceptTouchEvents);

    m_background.load(":/img/background.png");

    qDebug() << this->width() << ":" << this->height();

    m_msgDialog = new MsgDialog();

    constructUI();
    connectSlots();
}


void NewWindow::constructUI()
{
    // 将屏幕分为 20*12
    m_gridLayout = new QGridLayout(this);

    QLabel* titleLabel = new QLabel();
    titleLabel->setText("驾驶");
    QFont font("Microsoft YaHei", 30, 10);
    titleLabel->setFont(font);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel {background: transparent;}");     // 设置子控件的背景为透明，否则在Android上显示异常

    m_controlPanel = new ControlPanel();
    int w = (width() < height()) ? width()*2/3 : height()*2/3;
    qDebug() << "wwwwwwwwwwwwwwwwwwwwwwww:" << w;
    m_controlPanel->setFixedSize(w, w);
    m_controlPanel->setStyleSheet("QWidget {background: transparent;}");

    int s = ((width() < height()) ? width() : height()) / 12;

    m_rocketBtn = new QMyPushButton();
    m_rocketBtn->setText("加速");
    m_rocketBtn->setFixedSize(s*3, s*3);
    m_rocketBtn->setNormalIcon(":/img/lighting.png");
    m_rocketBtn->setStyleSheet("QPushButton {background: transparent;}");
    m_rocketBtn->setCountDownEnable(true);
    m_rocketBtn->setCountDownTime(3);

    m_lightBtn = new QMyPushButton();
    m_lightBtn->setText("亮灯");
    m_lightBtn->setFixedSize(s*3, s*3);
    m_lightBtn->setNormalIcon(":/img/light.png");
    m_lightBtn->setPressedIcon(":/img/lightPressed.png");
    m_lightBtn->setStyleSheet("QPushButton {background: transparent;}");

    m_whistleBtn = new QMyPushButton();
    m_whistleBtn->setText("鸣笛");
    m_whistleBtn->setFixedSize(s*3, s*3);
    m_whistleBtn->setNormalIcon(":/img/bugle.png");
    m_whistleBtn->setPressedIcon(":/img/buglePressed.png");
    m_whistleBtn->setStyleSheet("QPushButton {background: transparent;}");

    m_gridLayout->addWidget(titleLabel, 0, 0, 1, 20);
    m_gridLayout->addWidget(m_controlPanel, 3, 1, 8, 8, Qt::AlignBottom);
    m_gridLayout->addWidget(m_rocketBtn, 5, 10, 3, 3);
    m_gridLayout->addWidget(m_lightBtn, 5, 13, 3, 3);
    m_gridLayout->addWidget(m_whistleBtn, 5, 16, 3, 3);
}

void NewWindow::connectSlots()
{
    //connect(m_connectBtn, SIGNAL(clicked(bool)), this, SLOT(onConnectBtn()));
}


void NewWindow::onConnectBtn()
{
    qDebug() << "void NewWindow::onConnectBtn()";
    if (NULL != m_msgDialog) {
        m_msgDialog->show();
    }
}

void NewWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, width(), height(), m_background);
}

void NewWindow::showEvent(QShowEvent*)
{
    if (m_msgDialog->isConnected() == false) {
        /*QMessageBox msg(this);
        msg.setText("未连接到小车");
        msg.setIcon(QMessageBox::Information);
        msg.addButton("稍后", QMessageBox::RejectRole);
        msg.addButton("立刻连接", QMessageBox::AcceptRole);

        if (msg.exec() == QMessageBox::AcceptRole) {
            onConnectBtn();
        }*/
    }
}


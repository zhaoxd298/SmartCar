#include "MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_msgDialog = new MsgDialog();
    //m_msgDialog->resize(width(), height());
    constructUI();
    connectSlots();
}

MainWindow::~MainWindow()
{
    delete m_msgDialog;
}

void MainWindow::constructUI()
{
    m_connectBtn = new QPushButton;
    m_connectBtn->setText("连接小车");
    QString btnStyle1 = "\
        QPushButton{\
            color: rgb(38, 133, 227);\
            border:1px;\
        }\
        QPushButton:hover{\
            color: rgb(97, 179, 246);\
        }\
        QPushButton:pressed{\
            color: rgb(38, 133, 227);\
        }";
    m_connectBtn->setStyleSheet(btnStyle1);

    m_upBtn = new QPushButton();
    m_upBtn->setText("前进");

    m_downBtn = new QPushButton();
    m_downBtn->setText("倒退");

    m_leftBtn = new QPushButton();
    m_leftBtn->setText("向左");

    m_rightBtn = new QPushButton();
    m_rightBtn->setText("向右");

    m_stopBtn = new QPushButton();
    m_stopBtn->setText("停止");

    QVBoxLayout* vLayout = new QVBoxLayout();

    vLayout->addWidget(m_connectBtn);
    vLayout->addStretch();

    QGridLayout* ctlLayout = new QGridLayout();
    ctlLayout->addWidget(m_upBtn, 0, 1, 1, 1);
    ctlLayout->addWidget(m_leftBtn, 1, 0, 1, 1);
    ctlLayout->addWidget(m_stopBtn, 1, 1, 1, 1);
    ctlLayout->addWidget(m_rightBtn, 1, 2, 1, 1);
    ctlLayout->addWidget(m_downBtn, 2, 1, 1, 1);
    vLayout->addLayout(ctlLayout);

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addStretch();
    m_mainLayout->addLayout(vLayout);

    this->setLayout(m_mainLayout);
}

void MainWindow::connectSlots()
{
    connect(m_connectBtn, SIGNAL(clicked(bool)), this, SLOT(onConnectBtn()));
    connect(m_upBtn, SIGNAL(pressed()), this, SLOT(onUpPressedBtn()));
    //connect(m_upBtn, SIGNAL(released()), this, SLOT(onReleasedBtn()));

    connect(m_downBtn, SIGNAL(pressed()), this, SLOT(onDownPressedBtn()));
    //connect(m_downBtn, SIGNAL(released()), this, SLOT(onReleasedBtn()));

    connect(m_leftBtn, SIGNAL(pressed()), this, SLOT(onLeftPressedBtn()));
    connect(m_leftBtn, SIGNAL(released()), this, SLOT(onReleasedBtn()));

    connect(m_rightBtn, SIGNAL(pressed()), this, SLOT(onRightPressedBtn()));
    connect(m_rightBtn, SIGNAL(released()), this, SLOT(onReleasedBtn()));

    connect(m_stopBtn, SIGNAL(clicked(bool)), this, SLOT(onStopBtn()));
}

void MainWindow::onConnectBtn()
{
    if (NULL != m_msgDialog) {
        m_msgDialog->show();
    }
}


void MainWindow::onUpPressedBtn()
{
    qDebug() << "onUpPressedBtn";
    m_msgDialog->ctlCar(true, 150, 0);
    m_lastDir = true;
}

void MainWindow::onDownPressedBtn()
{
   qDebug() << "onDownPressedBtn";
   m_msgDialog->ctlCar(false, 150, 0);
   m_lastDir = false;
}

void MainWindow::onLeftPressedBtn()
{
   qDebug() << "onLeftPressedBtn";
   m_msgDialog->ctlCar(m_lastDir, 150, -90);
}

void MainWindow::onRightPressedBtn()
{
   qDebug() << "onRightPressedBtn";
   m_msgDialog->ctlCar(m_lastDir, 150, 90);
}

void MainWindow::onStopBtn()
{
    m_msgDialog->ctlCar(m_lastDir, 0, 0);
}

void MainWindow::onReleasedBtn()
{
   qDebug() << "onReleasedBtn";
   m_msgDialog->ctlCar(m_lastDir, 150, 0);
}

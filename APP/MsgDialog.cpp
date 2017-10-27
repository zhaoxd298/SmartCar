#include "MsgDialog.h"
#include "Protocol.h"
#include <QMessageBox>

MsgDialog::MsgDialog(QWidget *parent) : QWidget(parent)
{
    m_isConnected = false;

    constructUI();
    connectSlots();

    m_bluetoothDev = new Bluetooth(this);
}

MsgDialog::~MsgDialog()
{
    //delete m_bluetoothDev;
}

void MsgDialog::constructUI()
{
    QLabel* label = new QLabel();
    label->setText("Connect Car ...");
    QFont font("Times New Roman", 30, 30);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    m_bluetoothRbtn = new QRadioButton();
    m_bluetoothRbtn->setText("蓝牙");
    m_bluetoothRbtn->setChecked(true);

    m_wifiRbtn = new QRadioButton();
    m_wifiRbtn->setText("网络");
    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(m_bluetoothRbtn);
    hLayout1->addWidget(m_wifiRbtn);
    hLayout1->addStretch();

    m_showList = new QListWidget();

    m_scanBtn = new QPushButton();
    m_scanBtn->setText("扫描");
    m_connectBtn = new QPushButton();
    m_connectBtn->setText("连接");
    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addStretch();
    hLayout2->addWidget(m_scanBtn);
    hLayout2->addWidget(m_connectBtn);

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(label);
    m_mainLayout->addLayout(hLayout1);
    m_mainLayout->addWidget(m_showList);
    m_mainLayout->addLayout(hLayout2);

}

void MsgDialog::connectSlots()
{
    connect(m_connectBtn, SIGNAL(clicked(bool)), this, SLOT(onConnectBtn()));
    connect(m_scanBtn, SIGNAL(clicked(bool)), this, SLOT(onScanBtn()));
}

void MsgDialog::onScanBtn()
{
    if (m_bluetoothRbtn->isChecked()) {
        m_bluetoothDev->scan();
    } else if (m_wifiRbtn->isChecked()) {

    }

}

void MsgDialog::onConnectBtn()
{
    if (m_bluetoothRbtn->isChecked()) {
        QListWidgetItem *item = m_showList->currentItem();
        if (NULL != item) {
            m_bluetoothDev->connectToTarget(item);
        } else {
            QMessageBox::information(this, tr("Info"), "Please choose device!");
        }
    } else if (m_wifiRbtn->isChecked()) {

    }
}

void MsgDialog::addBluetoothToList(QListWidgetItem *item)
{
    if (NULL != item) {
        m_showList->addItem(item);
    }
}

QListWidget* MsgDialog::getShowList()
{
    return m_showList;
}

void MsgDialog::sendData(const char* data, int size)
{
    if (m_bluetoothRbtn->isChecked()) {
        m_bluetoothDev->sendData(data, size);
        qDebug() << "Send data success, size:" << size;
    } else if (m_wifiRbtn->isChecked()) {

    }
}

void MsgDialog::ctlCar(bool direction, int speed, int angle)
{
    char buf[128] = {0};

    if (angle >= 0) {
        snprintf(buf, sizeof(buf), "@car#dir=%d#spd=%03d#ang=%03d#", direction, speed, angle);
    } else {
        snprintf(buf, sizeof(buf), "@car#dir=%d#spd=%03d#ang=%02d#", direction, speed, angle);
    }

    CmdBuf cmdBuf(CMD_CTL_SPEED, 0, buf, strlen(buf));

    sendData(cmdBuf.cmdBuf(), cmdBuf.cmdSize());
}

bool MsgDialog::isConnected()
{
    return m_isConnected;
}

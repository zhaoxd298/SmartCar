#include "Bluetooth.h"
#include "MsgDialog.h"
#include <QMessageBox>

#include <QDebug>

static const QLatin1String serviceUuid("00001101-0000-1000-8000-00805F9B34FB");

Bluetooth::Bluetooth(QWidget *parent) : QWidget(parent)
{
    m_msgDialog = dynamic_cast<MsgDialog*>(parent);

    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    m_localDevice = new QBluetoothLocalDevice();
    m_bluetoothSocket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    connect(m_discoveryAgent,
            SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this,
            SLOT(addBluetoothDevToList(QBluetoothDeviceInfo))
            );
    connect(m_bluetoothSocket,
            SIGNAL(readyRead()),
            this,
            SLOT(readBluetoothDataEvent())
            );
    connect(m_bluetoothSocket,
            SIGNAL(connected()),
            this,
            SLOT(bluetoothConnectedEvent())
            );
    connect(m_bluetoothSocket,
            SIGNAL(disconnected()),
            this,
            SLOT(bluetoothDisconnectedEvent())
            );

    m_isConnected = false;
}

Bluetooth::~Bluetooth()
{
    m_bluetoothSocket->disconnectFromService();
    //m_localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);

    delete m_discoveryAgent;
    delete m_localDevice;
    delete m_bluetoothSocket;
}

void Bluetooth::addBluetoothDevToList(const QBluetoothDeviceInfo& info)
{
    if (NULL == m_msgDialog) {
        return;
    }

    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());

    qDebug() << "found bluetooth device" << label;

    QList<QListWidgetItem *> items = m_msgDialog->getShowList()->findItems(label, Qt::MatchExactly);

    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = m_localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired ||
            pairingStatus == QBluetoothLocalDevice::AuthorizedPaired) {
            item->setTextColor(QColor(Qt::green));
        } else {
            item->setTextColor(QColor(Qt::black));
        }

        m_msgDialog->addBluetoothToList(item);
    }
}

void Bluetooth::readBluetoothDataEvent()
{
    QByteArray line = m_bluetoothSocket->readAll();
    QString strData = QString::fromLocal8Bit(line);

    qDebug() << strData;
}

void Bluetooth::bluetoothConnectedEvent()
{
    QMessageBox::information(this, tr("Info"), tr("successful connection!"));
    m_isConnected = true;
}

void Bluetooth::bluetoothDisconnectedEvent()
{
    QMessageBox::information(this, tr("Info"), tr("successful disconnection!"));
    m_isConnected = false;
}

void Bluetooth::scan()
{
    qDebug() << "void Bluetooth::scan()";

    if(m_localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff ) {
        qDebug() << "open bluetooth";
        m_localDevice->powerOn();
    }

    m_discoveryAgent->start();
}

void Bluetooth::sendData(const char* data, int size)
{
    if ((NULL == data) || (size <= 0)) {
        qDebug() << "Invalid parameter";
        return;
    }

    if (m_bluetoothSocket->write(data, size) < 0) {
        qDebug() << "Bluetooth send data error";
    }
}

void Bluetooth::connectToTarget(QListWidgetItem *item)
{
    QString text = item->text();

    int index = text.indexOf(' ');

    if (index == -1)
        return;

    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));
    m_targetName = name;
    qDebug() << "You has choice the bluetooth address is " << address;
    qDebug() << "The device is connneting.... ";
    m_bluetoothSocket->connectToService(address, QBluetoothUuid(serviceUuid) ,QIODevice::ReadWrite);
    QMessageBox::information(this, tr("Info"), "Connecting to " + m_targetName + " ...");
}

bool Bluetooth::isConnected()
{
    return m_isConnected;
}

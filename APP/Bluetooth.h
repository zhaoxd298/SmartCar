#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QWidget>
#include <QObject>
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>
#include <QListWidgetItem>

class MsgDialog;

class Bluetooth : public QWidget
{
    Q_OBJECT
private:
    bool m_isConnected;
    QString m_targetName;
    MsgDialog* m_msgDialog;

    QBluetoothDeviceDiscoveryAgent *m_discoveryAgent;
    QBluetoothLocalDevice *m_localDevice;
    QBluetoothSocket *m_bluetoothSocket;

public slots:
    void addBluetoothDevToList(const QBluetoothDeviceInfo& info);
    void readBluetoothDataEvent();
    void bluetoothConnectedEvent();
    void bluetoothDisconnectedEvent();

public:
    explicit Bluetooth(QWidget *parent);
    ~Bluetooth();

    void scan();
    void sendData(const char* data, int size);
    void connectToTarget(QListWidgetItem *item);
    bool isConnected();
signals:

public slots:
};

#endif // BLUETOOTH_H

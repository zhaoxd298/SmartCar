#ifndef MSGDIALOG_H
#define MSGDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidgetItem>

#include "Bluetooth.h"

class MsgDialog : public QWidget
{
    Q_OBJECT

private:
    bool m_isConnected;
    QRadioButton* m_bluetoothRbtn;
    QRadioButton* m_wifiRbtn;
    QListWidget* m_showList;
    QPushButton* m_scanBtn;
    QPushButton* m_connectBtn;
    QVBoxLayout* m_mainLayout;

    Bluetooth* m_bluetoothDev;

private:
    void constructUI();
    void connectSlots();

public slots:
    void onScanBtn();
    void onConnectBtn();

public:
    MsgDialog(QWidget *parent = 0);
    ~MsgDialog();

    void addBluetoothToList(QListWidgetItem* item);
    QListWidget* getShowList();
    void sendData(const char* data, int size);
    /**
    * 控制小车
    * @direction：方向  true：前进  false：倒退
    * @speed:小车速度，取值范围[0-255]
    * @angle:小车角度  <0:向左转  >0:向右转  ==0:直行
    */
    void ctlCar(bool direction, int speed, int angle);

    bool isConnected();
};

#endif // MSGDIALOG_H

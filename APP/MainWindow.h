#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include "MsgDialog.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton* m_connectBtn;
    QPushButton* m_upBtn;
    QPushButton* m_downBtn;
    QPushButton* m_leftBtn;
    QPushButton* m_rightBtn;
    QPushButton* m_stopBtn;
    QHBoxLayout* m_mainLayout;

    bool m_lastDir;
    MsgDialog* m_msgDialog;
private:
    void constructUI();
    void connectSlots();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onConnectBtn();

    void onUpPressedBtn();
    void onDownPressedBtn();
    void onLeftPressedBtn();
    void onRightPressedBtn();
    void onStopBtn();

    void onReleasedBtn();
};

#endif // MAINWINDOW_H

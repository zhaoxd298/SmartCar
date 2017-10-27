#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>
#include <QPixmap>
#include <QGridLayout>

#include "MsgDialog.h"
#include "ControlPanel.h"
#include "QMyPushButton.h"

class NewWindow : public QWidget
{
    Q_OBJECT
private:
    QPixmap m_background;

    QMyPushButton* m_rocketBtn;
    QMyPushButton* m_lightBtn;
    QMyPushButton* m_whistleBtn;
    ControlPanel* m_controlPanel;
    MsgDialog* m_msgDialog;
    QGridLayout* m_gridLayout;


private:
    void constructUI();
    void connectSlots();

protected:
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

public slots:
    void onConnectBtn();

public:
    explicit NewWindow(QWidget *parent = 0);


signals:


};

#endif // NEWWINDOW_H

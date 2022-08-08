#ifndef MAINSEND2_H
#define MAINSEND2_H

#include "dmxcore.h"
#include "operation.h"

#include <QMainWindow>
#include <opencv2/opencv.hpp>

#include <QDebug>
#include <QString>

#include <QTimer>
#include <QThread>

namespace Ui {
class MainSend2;
}



class MainSend2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainSend2( QWidget *parent = nullptr);
    ~MainSend2();
    dmxcore dmx;
    operation *op2 = new operation();

    QThread _thread;
    bool AutoColor = false;
    bool OFF = false;

    void setSliderPosition(int i);

    //void RGBoperation(cv::Scalar _mean);
    //void Color_Oversize_Check(cv::Scalar _mean);
    void Dmx_Start();
    void Dmx_Color_Start();
    void Dmx_pan_tilt_Start();
private:
    Ui::MainSend2 *ui;
    operation op;


private slots:

    void on_PanSlider_valueChanged(int value);
    void on_TiltSlider_valueChanged(int value);
    void on_SpeedSlider_valueChanged(int value);
    void on_BulbSlider_valueChanged(int value);

    void on_Front_light_on_clicked();
    void on_Front_ligth_off_clicked();
    void on_Back_light_on_clicked();
    void on_Back_light_off_clicked();
    void on_Motor_auto_off_clicked();
    void on_Bulb_auto_off_clicked();
    void on_RGB_ON_BT_clicked();

    //int on_Color_auto_clicked();
    void on_Color_auto_clicked();

    void on_Motor_auto_clicked();
    void on_Bulb_auto_clicked();

    void on_OFF_clicked();

public slots:
    void on_RedSlider_valueChanged(int value);
    void on_GreenSlider_valueChanged(int value);
    void on_BlueSlider_valueChanged(int value);
    void on_WhiteSlider_valueChanged(int value);



};

#endif // MAINSEND2_H

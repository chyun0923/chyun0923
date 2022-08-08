#ifndef OPERATION_H
#define OPERATION_H
#include "dmxcore.h"


#include <opencv2/opencv.hpp>
#include <QDebug>

class operation : public QObject
{
public:
    //explicit operation(QObject* parent = 0);
    operation();
    dmxcore dmx;
    dmxcore *dmx2 = new dmxcore();
    //dmxcore *color;

    QThread _thread2;

    bool AutoColor = false;
    bool OFF = false;

    void run();
    void Front_Back_division(int &front_color,int &back_color,int &temp1 ,int &temp2,int value ,bool &front, bool &back);
    int value_mul(int &mode , int _value);

    void Front_color_zero(int &_red , int &_green, int &_blue  , int &_white);

    void Back_color_zero(int &_red2 , int &_green2, int &_blue2  , int &_white2);

    int ColorAuto(int &pan , int &tilt, int &pan2, int &tilt2 ,int &auto_motor , int &auto_bulb , int &motor_speed,int &bulb_speed, bool &front, bool &back);
    void RGBoperation(cv::Scalar _mean, bool &front, bool &back);
    void Color_Oversize_Check(cv::Scalar _mean, bool &front, bool &back);

};

#endif // OPERATION_H

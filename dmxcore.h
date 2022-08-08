#ifndef DMXCORE_H
#define DMXCORE_H


#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QtNetwork>
#include <QTimer>


class dmxcore
{
public:
    dmxcore();
    QUdpSocket _sender;
    QByteArray result;


    int _Master = 255; //조명 밝기 최대치 설정.
    int Speed1 = 254;
    int Speed2 = 0;
    //====================dmx1 && dmx 2====================
    int _red = 0;       int _red2 = 0;
    int _green = 0;   int _green2 =0;
    int _blue = 0;      int _blue2 = 0;
    int _white = 0;     int _white2 =0;

    int _auto_motor = 0;
    int _auto_bulb = 0;

    bool front = true;
    bool back = true;

    int front_red = 0;
    int front_green = 0;
    int front_blue = 0;
    int front_white = 0;
    int back_red =0;
    int back_green = 0;
    int back_blue = 0;
    int back_white = 0;
    //====================dmx1 ======================
     int dmx1=0 ;
     int _pan = 0;
     int _tilt = 0;
    //====================dmx2 =======================
     int dmx2 =1;
     int _pan2 = 255; //255
     int _tilt2 = 255; //65

public:
    void makeprotocol(int universe ,int PAN , int TILT , int Master, int Auto_motor , int Auto_bulb ,int motor_speed,int bulb_speed);
    void Send();
    void OFF(int universe , int pan , int tilt);
private:

};

#endif // DMXCORE_H

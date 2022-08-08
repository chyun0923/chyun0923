#include "dmxcore.h"

dmxcore::dmxcore()
{

}
void dmxcore::makeprotocol(int universe ,int PAN , int TILT , int Master, int Auto_motor , int Auto_bulb ,int motor_speed,int bulb_speed){

   // qDebug() << " Click Light ON";
    result = "Art-Net";
    result.append(char(0)); // 기본 8Byte 기재

    result.append(char(0)); //  Opcode [0]
    result.append(80);      //  Opcode [1]                              X00P
    result.append(char(0)); //  Protocol Version Hi(0)                  X00
    result.append(14);      //  Protocol Version Lo(14)                 X0E
    result.append(char(0)); //  Sequence                                X00
    result.append(char(0)); //  Physical                                X00

    //result.append((universe >> 8) & 0xFF);  //Universe little endian[0]                 X00
    result.append(char(universe));

    //result.append(universe & 0xFF);         //Universe little endian[1]                 X00
     result.append(char(0));

     result.append(char(0));      //Length Hi                             X00
//    //===============================================

     result.append(21);          //Lenth Lo (XN)     // Channel -> char(N)

     result.append(char(PAN));        //channel 1 Pan running
     result.append(char(0));          //channel 2 Pan running fine truinng
     result.append(char(TILT));       //channel 3 Tilt running
     result.append(char(0));          //channel 4 Tilt running fine truning
     result.append(char(0));          //channel 5 Pan/Tilt Running Speed
     result.append(char(0));          //channel 6 Tilt infinite rotation
     result.append(char(Master));     //channel 7 Master Dimming(밝기) 필수 !
     result.append(char(0));          //channel 8 Strove
     result.append(char(_red));       //channel 9 RED
     result.append(char(_green));     //channel 10 GREEN
     result.append(char(_blue));      //channel 11 BLUE
     result.append(char(_white));     //channel 12 WHITE
     result.append(char(_red2));      //channel 13 RED2
     result.append(char(_green2));    //channel 14 GREEN2
     result.append(char(_blue2));     //channel 15 BLUE2
     result.append(char(_white2));    //channel 16 WHITE2
     result.append(char(Auto_motor)); //channel 17 Motor Auto
     result.append(char(motor_speed));     //channel 18 Motor Auto Speed
     result.append(char(Auto_bulb));  //channel 19 Bulb Auto
     result.append(char(bulb_speed));     //channel 20 Bulb Auto Speed
     result.append(char(0));          //channel 21 Reset !
     //result.append(5);



     qDebug() << "DMX_CORE";
     qDebug() << "front"<< front;
     qDebug() << "back"<< back;
     qDebug() << "red : " << _red;
     qDebug() << "red2 : " << _red2;
     qDebug() << "green : " << _green;
     qDebug() << "blue : " << _blue;
     qDebug() << "white : " << _white;

     Send();
}

void dmxcore::Send(){
    //To DMX controller Send data
    //qDebug() << " Send Data";
    _sender.writeDatagram(result, result.length(), QHostAddress("192.168.0.178") , 6454);
}

void dmxcore::OFF(int universe , int pan , int tilt)
{
    qDebug() << " Click Light OFF";
    //op.Front_color_zero();
    //op.Back_color_zero();
    _auto_motor = 0;
    _auto_bulb = 0;

    result = "Art-Net";
    result.append(char(0)); // 기본 8Byte 기재

    result.append(char(0)); //  Opcode [0]
    result.append(80);      //  Opcode [1]
    result.append(char(0)); //  Protocol Version Hi(0)
    result.append(14);      //  Protocol Version Lo(14)
    result.append(char(0)); //  Sequence
    result.append(char(0)); //  Physical

    result.append(char(universe));

    result.append(char(0));
    result.append(char(0));
    //===============================================
     result.append(21);

    result.append(char(pan));      //channel 1 Pan running
    result.append(char(0));
    result.append(char(tilt));
    for (int i=0;i<19;i++) {
        result.append(char(0));
    }
    Send();
}

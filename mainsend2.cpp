#include "mainsend2.h"
#include "ui_mainsend2.h"

MainSend2::~MainSend2()
{
    delete ui;
}

MainSend2::MainSend2( QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSend2)
{
    ui->setupUi(this);
    connect(ui->RedSlider,SIGNAL(valueChanged(int)),ui->RedValue,SLOT(setNum(int)));
    connect(ui->GreenSlider,SIGNAL(valueChanged(int)),ui->GreenValue,SLOT(setNum(int)));
    connect(ui->BlueSlider,SIGNAL(valueChanged(int)),ui->BlueValue,SLOT(setNum(int)));
    connect(ui->WhiteSlider,SIGNAL(valueChanged(int)),ui->WhiteValue,SLOT(setNum(int)));
    connect(ui->PanSlider,SIGNAL(valueChanged(int)),ui->PanValue,SLOT(setNum(int)));
    connect(ui->TiltSlider,SIGNAL(valueChanged(int)),ui->TiltValue,SLOT(setNum(int)));
    connect(ui->SpeedSlider,SIGNAL(valueChanged(int)),ui->SpeedValue,SLOT(setNum(int)));
    connect(ui->BulbSlider,SIGNAL(valueChanged(int)),ui->BulbValue,SLOT(setNum(int)));
    dmx.makeprotocol(dmx.dmx1 , dmx._pan , dmx._tilt, dmx._Master ,dmx._auto_motor , dmx._auto_bulb , dmx.Speed1 , dmx.Speed2);
    dmx.makeprotocol(dmx.dmx2 , dmx._pan2 , dmx._tilt2, dmx._Master ,dmx._auto_motor , dmx._auto_bulb , dmx.Speed1 , dmx.Speed2);
    op._thread2.moveToThread(&op._thread2);
}

void MainSend2::on_RedSlider_valueChanged(int value)
{
    op.Front_Back_division(dmx._red,dmx._red2,dmx.front_red, dmx.back_red , value,dmx.front , dmx.back  );
    Dmx_Color_Start();
}

void MainSend2::on_GreenSlider_valueChanged(int value)
{
    op.Front_Back_division(dmx._green,dmx._green2,dmx.front_green, dmx.back_green, value,dmx.front , dmx.back );
    Dmx_Color_Start();
}

void MainSend2::on_BlueSlider_valueChanged(int value)
{
    op.Front_Back_division(dmx._blue,dmx._blue2,dmx.front_blue,dmx.back_blue , value ,dmx.front , dmx.back );
    Dmx_Color_Start();
}

void MainSend2::on_WhiteSlider_valueChanged(int value)
{
    op.Front_Back_division(dmx._white,dmx._white2,dmx.front_white ,dmx.back_white , value,dmx.front , dmx.back  );
    Dmx_Color_Start();
}

void MainSend2::on_PanSlider_valueChanged(int value)
{
    value = value+1;
    dmx._pan2 = value * -2.55;
    op.value_mul(dmx._pan,value);
    Dmx_pan_tilt_Start();
}

void MainSend2::on_TiltSlider_valueChanged(int value)
{
    value = value+1;
    dmx._tilt2 = value * -2.55;
    op.value_mul(dmx._tilt,value);
    Dmx_pan_tilt_Start();
}

void MainSend2::on_SpeedSlider_valueChanged(int value)
{
    value = value + 1;
    dmx.Speed1 = value * -2.55;
    qDebug() <<"Speed motor"<<dmx.Speed1 ;
    Dmx_pan_tilt_Start();
}

void MainSend2::on_BulbSlider_valueChanged(int value)
{
    op.value_mul( dmx.Speed2 , value);
    Dmx_pan_tilt_Start();
}

//======================================= 앞 뒤 조명 ON / OFF SLOT ==================================

void MainSend2::on_Front_light_on_clicked()
{

    dmx.front = true;
    qDebug() << "front "<<dmx.front;
    qDebug() << "Back "<<dmx.back;
    if(dmx.back == false){
        dmx._red = dmx.front_red;
        dmx._green = dmx.front_green;
        dmx._blue = dmx.front_blue;
        dmx._white = dmx.front_white;
        op.Back_color_zero(dmx._red2 , dmx._green2 , dmx._blue2 , dmx._white2);
        Dmx_Start();
    }else{
        dmx._red = dmx._red2;
        dmx._green = dmx._green2;
        dmx._blue = dmx._blue2;
        dmx._white = dmx._white2;
        Dmx_Start();
    }
     qDebug() << "temp R G B : " << dmx.front_red << dmx.front_green << dmx.front_blue;

}

void MainSend2::on_Front_ligth_off_clicked()
{

    dmx.front = false;
    qDebug() << "front "<<dmx.front;
    qDebug() << "Back "<<dmx.back;
    if(dmx.back == false){
        op.Front_color_zero(dmx._red , dmx._green , dmx._blue , dmx._white);
        op.Back_color_zero(dmx._red2 , dmx._green2 , dmx._blue2 , dmx._white2);
        Dmx_Start();

    }else{
        op.Front_color_zero(dmx._red , dmx._green , dmx._blue , dmx._white);
        Dmx_Start();
    }
    qDebug() << "temp R G B : " << dmx.front_red << dmx.front_green << dmx.front_blue;

}

void MainSend2::on_Back_light_on_clicked()
{

    dmx.back = true;
    if(dmx.front == false){
        op.Front_color_zero(dmx._red , dmx._green , dmx._blue , dmx._white);
        dmx._red2 =   dmx.back_red;
        dmx._green2 = dmx.back_green;
        dmx._blue2 =  dmx.back_blue;
        dmx._white2 = dmx.back_white;
        Dmx_Start();
    }else{
        dmx._red2 = dmx._red ;
        dmx._green2 = dmx._green;
        dmx._blue2 = dmx._blue;
        dmx._white2 = dmx._white;
        Dmx_Start();
    }
     qDebug() << "temp R G B : " << dmx.front_red << dmx.front_green << dmx.front_blue;

}

void MainSend2::on_Back_light_off_clicked()
{

    dmx.back = false;
    if(dmx.front == false){
        op.Front_color_zero(dmx._red , dmx._green , dmx._blue , dmx._white);
        op.Back_color_zero(dmx._red2 , dmx._green2 , dmx._blue2 , dmx._white2);
        dmx.makeprotocol(dmx.dmx1 , dmx._pan , dmx._tilt, dmx._Master, dmx._auto_motor , dmx._auto_bulb, dmx.Speed1 , dmx.Speed2);
        dmx.makeprotocol(dmx.dmx2 , dmx._pan2 , dmx._tilt2, dmx._Master, dmx._auto_motor , dmx._auto_bulb, dmx.Speed1 , dmx.Speed2);
    }else{
        op.Back_color_zero(dmx._red2 , dmx._green2 , dmx._blue2 , dmx._white2);
        dmx.makeprotocol(dmx.dmx1 , dmx._pan , dmx._tilt, dmx._Master, dmx._auto_motor , dmx._auto_bulb, dmx.Speed1 , dmx.Speed2);
        dmx.makeprotocol(dmx.dmx2 , dmx._pan2 , dmx._tilt2, dmx._Master, dmx._auto_motor , dmx._auto_bulb, dmx.Speed1 , dmx.Speed2);
    }
     qDebug() << "temp R G B : " << dmx.front_red << dmx.front_green << dmx.front_blue;
}

//====================================AUTO MODE===================================

void MainSend2::on_Motor_auto_clicked()
{
     dmx._auto_motor = 16;
     Dmx_Start();
}


void MainSend2::on_Motor_auto_off_clicked()
{
    dmx._auto_motor = 0;
    Dmx_Start();
}

void MainSend2::on_Bulb_auto_clicked()
{
    dmx._auto_bulb = 8;
    Dmx_Start();
}

void MainSend2::on_Bulb_auto_off_clicked()
{
    dmx._auto_bulb = 0;
    Dmx_Start();
}

//===================================== Auto color create ================================================

void MainSend2::on_Color_auto_clicked()
{
    AutoColor = true;
    op.ColorAuto(dmx._pan , dmx._tilt ,dmx._pan2,dmx._tilt2 , dmx._auto_motor ,
                 dmx._auto_bulb ,dmx.Speed1,dmx.Speed2 ,dmx.front,dmx.back);
}

void MainSend2::on_RGB_ON_BT_clicked()
{
    QString StrR = ui->R_edit->text();
    int intR = StrR.toInt();
    dmx._red = intR;
    dmx._red2 = intR;
    QString StrG = ui->G_edit->text();
    int intG = StrG.toInt();
    dmx._green = intG;
    dmx._green2 = intG;
    QString StrB = ui->B_edit->text();
    int intB = StrB.toInt();
    dmx._blue = intB;
    dmx._blue2 = intB;
    Dmx_Color_Start();
}

void MainSend2::on_OFF_clicked() //끄기
{
    op.OFF = true;
    dmx.front = true;
    dmx.back = true;
    AutoColor = false;
    dmx.OFF(dmx.dmx1 , 0 , 0);
    dmx.OFF(dmx.dmx2 , 255 , 255);
    ui->RedSlider->setSliderPosition(0);
    ui->GreenSlider->setSliderPosition(0);
    ui->BlueSlider->setSliderPosition(0);
    ui->WhiteSlider->setSliderPosition(0);
    ui->PanSlider->setSliderPosition(0);
    ui->TiltSlider->setSliderPosition(0);
    ui->SpeedSlider->setSliderPosition(0);
    ui->BulbSlider->setSliderPosition(0);
}

//==========================================Start function====================================

void MainSend2::Dmx_Color_Start(){

    if(op.AutoColor){
        op.Front_color_zero(dmx._red , dmx._green , dmx._blue , dmx._white);
        op.Back_color_zero(dmx._red2 , dmx._green2 , dmx._blue2 , dmx._white2);
    }else {
        Dmx_Start();
    }
}

void MainSend2::Dmx_pan_tilt_Start(){
    qDebug() << "AutoColor : " << AutoColor;
    if(AutoColor){
        QTimer::singleShot(100, &op._thread2, [=](){
          Dmx_Start();
        });
    }else {
          Dmx_Start();
    }
}

void MainSend2::Dmx_Start(){
    dmx.makeprotocol(dmx.dmx1 , dmx._pan , dmx._tilt, dmx._Master, dmx._auto_motor , dmx._auto_bulb, dmx.Speed1 , dmx.Speed2);
    dmx.makeprotocol(dmx.dmx2 , dmx._pan2 , dmx._tilt2, dmx._Master, dmx._auto_motor , dmx._auto_bulb, dmx.Speed1 , dmx.Speed2);
}


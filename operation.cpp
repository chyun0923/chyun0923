#include "operation.h"


operation::operation()
{
    //_thread2.moveToThread(&_thread2);
    moveToThread(&_thread2);
    _thread2.start();
}
//========================================slider operation function===============================================
void operation::Front_Back_division(int &front_color,int &back_color,int &temp1 ,int &temp2,int value ,bool &front, bool &back){
    if(front){
        value_mul(front_color,value);
        temp1 = front_color;
    }else{
         temp1 = back_color;
         Front_color_zero(dmx._red , dmx._green , dmx._blue , dmx._white);
         qDebug() << "here";
    }

    if(back){
        value_mul(back_color,value);
        temp2 = back_color;
    }else{
        temp2 = front_color;
        Back_color_zero(dmx._red2 , dmx._green2 , dmx._blue2 , dmx._white2);
        qDebug() << "here";
    }
}

int operation::value_mul(int &mode , int _value){
    mode = _value * 2.55;
    return mode;
}

void operation::Front_color_zero(int &_red , int &_green, int &_blue  , int &_white){
    _red = 0;
    _green = 0;
    _blue = 0;
    _white = 0;
}

void operation::Back_color_zero(int &_red2 , int &_green2, int &_blue2 , int &_white2){
    _red2 = 0;
    _green2 = 0;
    _blue2 = 0;
    _white2 = 0;
}

//=======================================Open Cv Color Auto ====================================

int operation::ColorAuto(int &pan , int &tilt, int &pan2, int &tilt2 ,int &auto_motor , int &auto_bulb ,
                         int &motor_speed,int &bulb_speed , bool &front , bool &back)
{

    AutoColor = true;
    //qDebug() << "dmx thread start" << _thread2.isRunning();
    //==========비디오 가운데 픽셀만 계산 .===================
    cv::VideoCapture cap("C:/testfile/HDRtest.avi" ); //OK

    if (!cap.isOpened())  // if not success, exit program
    {
        qDebug() << "Cannot open the video cam !" ;
        return -1;
    }

    while(1){
        OFF = false;

        cv::Mat frame ;
        cv::Mat risize_video;
        cv::Mat main_border_video;
        cv::Mat all_border_video;

        bool bSuccess = cap.read(frame);
        if(!bSuccess){
            qDebug() << "Can't read a frame !";
            break;
        }

        cv::resize(frame,risize_video,cv::Size(780,540),0,0,cv::INTER_LINEAR);
        cv::Mat maincolor_video = risize_video(cv::Range(180,400),cv::Range(250,520));

        //가운데 BGR값 추출 .
        cv::Scalar _mean;
        _mean = cv::mean(maincolor_video);

        //비디오 연산 구간 .
        cv::copyMakeBorder(risize_video , main_border_video,50,50,50,50,cv::BORDER_CONSTANT,cv::Scalar(_mean[0], _mean[1], _mean[2]));

        //비디오 재생
        cv::imshow("Color main" , main_border_video);
        cv::imshow("Color Division" , maincolor_video);
        //ESC = 종료
        if(cv::waitKey(30) == 27 || OFF){
            qDebug() << "esc key is pressed by user ! ";
                if(_thread2.isRunning())
                {
                    _thread2.quit();
                    _thread2.wait();

                }
            AutoColor = false;
            break;
        }

       //  qDebug() << "1 RGB ";
       //  qDebug() << "R :" << _mean[2] << "G :" << _mean[1] << "B :" << _mean[0];
         //qDebug() << " ";
         RGBoperation(_mean ,front,back);

         int master_avg = (_mean[0]+_mean[1]+_mean[2])/3;
         if(front ==false){
         dmx._white = 0;
         }
         if(back ==false){
         dmx._white2 = 0;
         }
         dmx.makeprotocol(dmx.dmx1 , pan , tilt , master_avg, auto_motor , auto_bulb ,motor_speed,bulb_speed);
         dmx.makeprotocol(dmx.dmx2 , pan2 ,tilt2, master_avg, auto_motor ,auto_bulb,motor_speed,bulb_speed);
       // qDebug() << "dmx thread start" << _thread2.isRunning();
       // qDebug() << "2 RGB ";
       // qDebug() << "R :" << _mean[2] << "G :" << _mean[1] << "B :" << _mean[0] << "White : " << dmx._white;
       // qDebug() << " ";

   }

    return 0;
}
      //====================I 조명 출력 연산 I============================
void operation::RGBoperation(cv::Scalar _mean, bool &front, bool &back){


    int G_B = _mean[1] -_mean[0];
    int B_G = _mean[0] - _mean[1];

    int R_B = _mean[2] - _mean[0];
    int B_R = _mean[0] - _mean[2];

    int R_G = _mean[2] - _mean[1];
    int G_R = _mean[1] - _mean[2];

   if(_mean[2]+_mean[1]+_mean[0] < 150){ //블랙처리
        _mean[2] =0 ;
        _mean[1] =0 ;
        _mean[0] =0 ;
        dmx._white =0;
        dmx._white2 = 0;
   }
   else if(R_G> -13 && R_G<13 && G_B > -13 &&G_B <13  && _mean[2]+_mean[1]+_mean[0] > 254){ //회색-> 흰색 출력. //&& R_B > -13 && R_B < 13
            _mean[2] =0 ;
            _mean[1] =0 ;
            _mean[0] =0 ;
            dmx._white   =255;
            dmx._white2 = 255;

   }else if(G_B < 10 && G_B >= -10 && B_G <10 && B_G >=-10 && _mean[2]> _mean[1] && _mean[2] > _mean[0]){ //RED
         qDebug() << "RED";
         dmx._white = _mean[1]; //연분홍빛
         dmx._white2 = _mean[1];
         _mean[1] = 0; //분홍빛
         _mean[0] = 0;

   }else if(B_G <10 && B_G >=-10 &&G_B < 10 && G_B >= -10 && _mean[2] < _mean[1] && _mean[2] < _mean[0]){ //SKY
         qDebug() << "SKY";
         dmx._white = _mean[2];
         dmx._white2 = _mean[2];
         _mean[2] = 0;

   }else if(R_B <10 && R_B >=-10 &&B_R < 10 && B_R >= -10 && _mean[1] > _mean[2] && _mean[1] > _mean[0]){ // GREEN
         qDebug() << "GREEN ";
         dmx._white = _mean[2];
         dmx._white2 = _mean[2];
         _mean[2] = 0;
         _mean[0] = 0;

   }else if(B_R <10 && B_R >=-10 &&R_B < 10 && R_B >= -10 &&_mean[1] < _mean[2] && _mean[1] < _mean[0]){ //PURPLR
          qDebug() << "PURPLE ";
          dmx._white = _mean[1];
          dmx._white2 = _mean[1];
          _mean[1] = 0;

   }else if(R_G <10 && R_G >=-10 &&G_R < 10 && G_R >= -10 && _mean[0] > _mean[1] && _mean[0] > _mean[2]){ // BLUE
          qDebug() << "BLUE ";
          dmx._white = _mean[1];
          dmx._white2 = _mean[1];
          _mean[2] = 0;
          _mean[1] = 0;

   }else if(G_R <10 && G_R >=-10 &&R_G < 10 && R_G >= -10 && _mean[0] < _mean[2] && _mean[0] < _mean[1]){ //Yellow
          qDebug() << "YELLOW";
          dmx._white = _mean[0];
          dmx._white2 = _mean[0];
          _mean[0] = 0;


   }else if(_mean[0] >= _mean[2]  && _mean[1] >= _mean[2]){ //레드가 그린/블루 보다 낮으면 Red < Green & Blue

            if(G_B <= 255 && G_B >= 0){ // Red < Blue < Green //에메랄드

                if(_mean[1] > 200){
                _mean[0] = _mean[0] - 150;
                }else {
                _mean[0] = _mean[0] - 120;
                }
            }
            dmx._white = _mean[2];
            dmx._white2 = _mean[2];
            _mean[2] = 0;

   }else if(_mean[2] >= _mean[1] && _mean[0] >= _mean[1]){ //그린이 레드/블루 보다 낮으면 Green < Red & Blue

            if(B_R <= 255 && B_R >= 0 ){ //블루가 레드보다 높으면 레드는 줄어야한다. Green < Red < Blue

                _mean[2] =  _mean[2] - 100;

            }
             dmx._white = _mean[1];
             dmx._white2 = _mean[1]; //연분홍빛
             _mean[1] = 5;

   }else if(_mean[2] >= _mean[0] && _mean[1] >= _mean[0]){ //블루가 레드/그린 보다 낮으면 Blue < Red & Green
                if(G_R <= 255 && G_R >= 0 ){ // 레드가 제일 낮으면 Blue < Green < Red // _mean[1]>_mean[2]
                    //
                    _mean[1] = _mean[1] + 100;
                    _mean[2] = _mean[2] - 50;

                }
                dmx._white = _mean[0];
                dmx._white2 = _mean[0];
                _mean[0] = 5;
   }

   Color_Oversize_Check(_mean, front , back);

}

void operation::Color_Oversize_Check(cv::Scalar _mean , bool &front, bool &back){ //, bool &front ,bool &back
    for(int i=0; i<3; i++){
        if(_mean[i] <= 0){
            _mean[i] = 0;
        }else if(_mean[i] >= 255){
            _mean[i] = 255;
        }
    }

    if(front){
        dmx._red = _mean[2];
        dmx._green = _mean[1];
        dmx._blue = _mean[0];
    }else {
        dmx._red = 0;
        dmx._green = 0;
        dmx._blue = 0;
    }

    if(back){
        dmx._red2 = _mean[2];
        dmx._green2 = _mean[1];
        dmx._blue2 = _mean[0];
    }else {
        dmx._red2 = 0;
        dmx._green2 = 0;
        dmx._blue2 = 0;
    }
}




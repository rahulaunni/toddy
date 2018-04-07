#ifndef ICON_H
#define ICON_H
#include "Arduino.h"
#include "U8g2lib.h"
class ICON
{
  private:
  
    U8G2 _u8g2;
    int state=3,laststate=3;
    int speed=20,moving=0;
    //int cur_state;
     int cur_posx;
    int cur_posy;
     int last_posx;
    int last_posy;
    String title;
     unsigned char *ic;
    
  public:
    ICON(String,unsigned char*,U8G2 u8);
    ~ICON();
    void setPos(int);
    void displaym();
    int getMoving();

};



#endif

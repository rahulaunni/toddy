#ifndef LOADER_H
#define LOADER_H
#include "Arduino.h"
#include "U8g2lib.h"
#include "icons.h"
class LOADER
{
  private:
  
    U8G2 _u8g2;
    double inRad;
    double outRad;
    float speedinc;
    float i,lasti,r;
    String err[5];
    int strwidth;
    int err_items;
   
  public:
 
    LOADER(double,double,U8G2 u8);
    LOADER(double,U8G2 u8);
    LOADER(char* , U8G2 u8);
    LOADER();
    void _displayErr();
    void hotspot();
    ~LOADER();
    void draw();

};



#endif

#ifndef MAINMENU_H
#define MAINMENU_H
#include "Arduino.h"
#include "ICON.h"
#include "U8g2lib.h"

class MAINMENU
{
  private:
    int state=0,changeflag=1;
    ICON* _ic;
    int arr[9];
    float dotrad=1;
    U8G2 _u8g2;
    

    
  public:
    MAINMENU(int,ICON*,U8G2 u8);
    ~MAINMENU();
    void up();
    void dwn();
    int getSelected();
    void displayc();
};



#endif

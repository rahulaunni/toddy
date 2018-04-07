#include"ICON.h"
#define DHEIGHT 128
#define DWIDTH 64

ICON::ICON(String _title, unsigned char* _ic, U8G2 u8)
{
  //initializing values
  _u8g2 = u8;
  title = _title;
  ic = _ic;

  last_posx = 8;
  last_posy = 160;
  cur_posx=8;
  cur_posy=160;
}

ICON::~ICON() ///default distructor
{
}


void ICON::displaym() {
  if (state == 1 || laststate == 1) {
    last_posx = last_posx + ((cur_posx - last_posx)) % speed;
    last_posy = last_posy + ((cur_posy - last_posy)) % speed;
    if (cur_posx > last_posx) {
      last_posx = last_posx + speed;
    } else if (cur_posx < last_posx) {
      last_posx = last_posx - speed;
    }

    if (cur_posy > last_posy) {
      last_posy = last_posy + speed;
    } else if (cur_posy < last_posy) {
      last_posy = last_posy - speed;
    }

  } else {
    last_posy = cur_posy;
    last_posx = cur_posx;
  }
  //

  if (last_posy == cur_posy && last_posx == cur_posx) {
    moving = 0;
  } else {
    moving = 1;
  }

  _u8g2.setFont(u8g2_font_crox2h_tr); // choose a suitable font
  _u8g2.drawXBM(last_posx + 8, last_posy, 48, 48, ic);
  //_u8g2.drawXBM(8, 35, 48, 48,ic);

  _u8g2.setCursor((32 - (_u8g2.getStrWidth(title.c_str()) / 2)) + last_posx, last_posy + 70);
  _u8g2.print(title);

}

int ICON::getMoving() {
  return moving;
}

void ICON::setPos(int _state) {

  if (_state == 4) {
    laststate = state;
    state = 4;
    cur_posx = -64;
    cur_posy = 40;


  } else if (_state == 3) {
    laststate = state;
    state = 3;
    cur_posx = -64;
    cur_posy = 40;


  } else if (_state == 2) {
    laststate = state;
    state = 2;
    cur_posx = 64;
    cur_posy = 40;


  } else {
    laststate = state;
    state = 1;
    cur_posx = 0;
    cur_posy = 40;

  }
}



#include"MENU.h"
#define DHEIGHT 128
#define DWIDTH 64

void MENU::up()
{
  if (state < last_item)
  {
    state++;

  }
  //      Serial.print(state);

}


void MENU::dwn()
{
  if (state > 1)
  {
    state--;
  }

}

String  MENU::getSelect()
{
  // return menu_item[state];

 return id_item[state];

}


void MENU::display_menu() {
  int i, pos, first = 1, last = 5;
  if (last_item < 5)
  {
    last = last_item;
  }
  if (state > 3 && state < (last_item - 1) && last_item > 5)
  {
    first = state - 2;
    last = state + 2;
  }
  if ( state >= (last_item - 1) && last_item > 5)
  {
    first = last_item - 4;
    last = last_item;
  }

  _u8g2.setDrawColor(2);
  _u8g2.drawBox(0, 0, 64, 14);
  _u8g2.setDrawColor(0);
  _u8g2.setFont(u8g2_font_crox2h_tr);
  strwidth = _u8g2.getStrWidth(_title.c_str());
  _u8g2.setCursor(32 - (strwidth / 2), 11);
  _u8g2.print(_title);

  _u8g2.setDrawColor(1);


  //  _u8g2.setDrawColor(1);
  if (state == 1)
  {
    _u8g2.drawRBox(0, 23, 64, 15, 0);
  }

  else if (state == 2)
  {
    _u8g2.drawRBox(0, 43, 64, 15, 0);
  }
  else if (state == 3 && last_item < 5)
  {
    _u8g2.drawRBox(0, 63, 64, 15, 0);
  }
  else if (state == 4 && last_item < 5)
  {
    _u8g2.drawRBox(0, 83, 64, 15, 0);
  }


  else if (state == last_item - 1)
  {
    _u8g2.drawRBox(0, 83, 64, 15, 0);
  }

  else if (state == last_item)
  {
    _u8g2.drawRBox(0, 103, 64, 15, 0);
  }

  else {
    _u8g2.drawRBox(0, 63, 64, 15, 0);
  }




  for (i = first, pos = 35; i <= last; i++)
  {
    if (i == state)
      _u8g2.setDrawColor(0);
    else
      _u8g2.setDrawColor(1);
    strwidth = _u8g2.getStrWidth(menu_item[i].c_str());

    _u8g2.setCursor(32 - (strwidth / 2), pos);
    _u8g2.print(menu_item[i]);
    pos = pos + 20;
  }


}


MENU::MENU(String title, char *st, U8G2 u8)
{
  _title = title;
  int i = 2;

  menu_item[1] = "<<back";
 id_item[1] = "<<back";

  /* get the first token */

 char* token = strtok(st, "*,&");


  while ( token != NULL )
  {
    menu_item[i] = String(token);
    token = strtok(NULL, "&");
    id_item[i] = String(token);
    i++;

    token = strtok(NULL, "&");


 }
     

  _u8g2 = u8;
  state = 1;
  last_item = i - 1;
  strwidth=0;
_diastate=0;
_diares=1;
state=1;
}


MENU::MENU(U8G2 u8)
{
  _u8g2 = u8;
  strwidth=0;
_diastate=0;
_diares=1;
state=1;
last_item=1;
}
MENU::MENU()   ///default constructor
{
strwidth=0;
_diastate=0;
_diares=1;
state=1;
last_item=1;


}

MENU::~MENU()   ///default distructor
{


}

void MENU::dialog_box(char* Title, int pos, int res)
{
  _diares = res;
  int i = 0;
 char *token;

  /* get the first token */
  token = strtok((char*)Title, "&");


  while ( token != NULL )
  {
    _diatitle[i] = String((char*)token);
    token = strtok(NULL, "&");
    i++;

  }
  _u8g2.setFont(u8g2_font_crox2h_tr);

  if (res == 1)
  {
        strwidth = _u8g2.getStrWidth(_diatitle[0].c_str());

    _u8g2.setCursor(32 - (strwidth / 2), pos + 12);
   _u8g2.setDrawColor(2);
   _u8g2.drawBox(4, pos, 56, 15);
 _u8g2.setDrawColor(0);
   _u8g2.print(_diatitle[0]);
    _u8g2.setDrawColor(1);

     }
  else if (res == 2)
  {
    if (_diastate == 0) {

      _u8g2.setDrawColor(2);
      _u8g2.drawBox(4, pos, 28, 15);
      _u8g2.setDrawColor(0);
      _u8g2.setCursor(9, pos + 12);
      _u8g2.print(_diatitle[0]);

      _u8g2.setDrawColor(1);


      _u8g2.setCursor(33, pos + 12);
      _u8g2.print(_diatitle[1]);

      _u8g2.drawFrame(4, pos, 56, 15);
    }

    if (_diastate == 1) {

      _u8g2.setDrawColor(2);
      _u8g2.drawBox(32, pos, 28, 15);
      _u8g2.setDrawColor(0);
      _u8g2.setCursor(33, pos + 12);
      _u8g2.print(_diatitle[1]);

      _u8g2.setDrawColor(1);

      _u8g2.setCursor(9, pos + 12);
      _u8g2.print(_diatitle[0]);


      _u8g2.drawFrame(4, pos, 56, 15);
    }
    //
    //

  }
}

void MENU::_diaup()
{
  _diastate = 1;




}


void MENU::_diadwn()
{
  _diastate = 0;


}

String  MENU::getDia()
{ return _diatitle[_diastate];

}



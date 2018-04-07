#include"LOADER.h"


LOADER::LOADER(double _inRad,double _outRad, U8G2 u8)
{
 _u8g2 = u8;
 inRad=_inRad;
 outRad=_outRad;
 i=random(360);
lasti=i;
speedinc=0.6;
r=0;
}

LOADER::LOADER(double _outRad, U8G2 u8)
{
 _u8g2 = u8;
 outRad=_outRad;
 i=0;
 lasti=0;
 inRad=1;
r=random(1,outRad);
speedinc=(float)((rand() % 4 + 1)/3);
}

LOADER::~LOADER()   ///default distructor
{
}

void LOADER::hotspot(){
  if(!speedinc)speedinc=.6;
  r=r+speedinc;
   _u8g2.drawCircle(32,67,r, U8G2_DRAW_UPPER_RIGHT);
     _u8g2.drawCircle(32,67,r, U8G2_DRAW_LOWER_LEFT);
 if(r>outRad)r=0;

}

void LOADER::draw(){
    i+=.3;
   double x = outRad*cos(i);
   double y = outRad*sin(i);
   _u8g2.drawDisc(x+32,y+64,(2+cos(i))*1.5, U8G2_DRAW_ALL);

    double x2 = outRad*cos(i-.8);
   double y2 = outRad*sin(i-.8);
   _u8g2.drawDisc(x2+32,y2+64,(2+cos(i-.8))*1.5, U8G2_DRAW_ALL);

    double x3 = outRad*cos(i-1.6);
   double y3 = outRad*sin(i-1.6);
   _u8g2.drawDisc(x3+32,y3+64,(2+cos(i-1.6))*1.5, U8G2_DRAW_ALL);

    double x4 = outRad*cos(i-2.4);
   double y4 = outRad*sin(i-2.4);
   _u8g2.drawDisc(x4+32,y4+64,(2+cos(i-2.4))*1.5, U8G2_DRAW_ALL);

    double x5 = outRad*cos(i-3.2);
   double y5 = outRad*sin(i-3.2);
   _u8g2.drawDisc(x5+32,y5+64,(2+cos(i-3.2))*1.5, U8G2_DRAW_ALL);
   
 
    lasti=i;
   if(i>360)i=0;
}

//save err
LOADER::LOADER(char *er, U8G2 u8)
{
	int i = 1;
char* token = strtok(er,"&");
	while(token != NULL)
	{
		err[i]=String(token);
		token = strtok(NULL,"&");
		i++;
	}
_u8g2 = u8;
err_items= i-1;
}
//default constructor
LOADER::LOADER()
{
}
//display err
void LOADER::_displayErr()
{
	int i =1;
_u8g2.setFont(u8g2_font_crox2h_tr);
//_u8g2.drawXBM(10,10,err_width,err_height,err_bits); 
for(i=1;i<=err_items;i++)
{
	strwidth = _u8g2.getStrWidth(err[i].c_str());

	_u8g2.setCursor(32-(strwidth/2),38+(17*i));
	_u8g2.print(err[i]);
}
 _u8g2.setCursor(23,  50+(17*(err_items+1)));
_u8g2.setDrawColor(2);
 _u8g2.drawBox(4, 38+(17*(err_items+1)), 56, 15);
 _u8g2.setDrawColor(0);
  
 _u8g2.print("Ok");
 _u8g2.setDrawColor(1);

}



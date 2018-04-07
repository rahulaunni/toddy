#include"MAINMENU.h"

MAINMENU::MAINMENU(int state, ICON* ic,U8G2 u8)
{
	_u8g2=u8;
  _ic = ic;
 int j =1;
 for (int i = 0; i < 3; i++) {
  _ic[i].setPos(j);
  arr[i]=j;
   if(j<3)
   j++;
 }
}



MAINMENU::~MAINMENU()
{
}

void MAINMENU::displayc() {
   for (int i = 0; i < 3; i++) {
  _ic[i].displaym();
  _u8g2.setFont(u8g2_font_crox2h_tr);
//_u8g2.setCursor(30,60);
 //_u8g2.print(sizeof(_ic));
  _u8g2.drawDisc(20+i*11, 120,1, U8G2_DRAW_ALL);
  if(i==state){
  if(dotrad<2.5)
  dotrad=dotrad+.5;
  _u8g2.drawDisc(20+i*11, 120,dotrad, U8G2_DRAW_ALL);
  }
   }
}


void MAINMENU::up() {
dotrad=1;
int n=3;

for(int i=0;i<n;i++)
{
  if(_ic[i].getMoving()==1)
  changeflag=0;
}

if(changeflag==1){
  int x = arr[n-1], i;
   for (i = n-1; i > 0; i--)
      arr[i] = arr[i-1];
   arr[0] = x;


for(int i=0;i<n;i++)
{
  _ic[i].setPos(arr[i]);
}
 if(state<n-1)
  state++;
else
state=0;
}
changeflag=1;
}

void MAINMENU::dwn() {
dotrad=1;
int n=3;
for(int i=0;i<n;i++)
{
  if(_ic[i].getMoving()==1)
  changeflag=0;
}
if(changeflag==1){
     int x = arr[0], i;
   for (i = 0; i<n; i++)
      arr[i] = arr[i+1];
   arr[n-1] = x;

for(int i=0;i<n;i++)
{
  _ic[i].setPos(arr[i]);
}
  if(state>0)
  state--;
  else state=n-1;

}

  changeflag=1;

 }

int MAINMENU::getSelected() {
   return state;
}


#ifndef DROP_H
#define DROP_H
#include "Arduino.h"
#include "MovingAverageFilter.h"
// #define   BLOCK     405
// #define   EMPTY     404
// #define   RATE_ERR  406
// #define   NO_ERR    100 
// #define   COMPLETED   101 
#define   MON_RANGE  10
#define   ALERT_PERCENT       0.15
#define   PERIOD	10
class DROP
{
private:
unsigned int newrate;
unsigned int _rate_ml;
unsigned int _alert;
unsigned int _df;
unsigned int _rate2set;
String _Bed;
String _Med;
String _Name;
String _MedName;
String _Timetable;
unsigned int _Tvol;
int _RemVol;
unsigned int _Infvol;
long _Dcount;
int _rTime;
int _tTime;
int _monCount;
int _setCount;
boolean setCount;

public:
long _rate;
unsigned long int  _Etime;
unsigned long int  _LastEtime;

DROP();
~DROP();
void setDcount(long);
void setTime(unsigned long int,long);
int getRate();
int  getRateMl();
int getvolInf();
int getvolRem();
int getinfPercent();
int getrate2set();
long getDcount();
int getRtime();
int getTtime();
void resetMonitor();
String getName();
String getMed();
String getMedName();
String getTimetable();

String getBed();

int getTvol();
int getDf();

void setDf(String);
void setBed(String);
void setMed(String);
void setMedName(String);
void setTimetable(String);

void setNam(String);
void setTvol(String);
void setR2set(String);
void setAlrt(String);
int MonRate();
String  Alert(unsigned long int);
int getAlertPercent() ;
int getAlertDrops();
int getR2setDPM();

};



#endif

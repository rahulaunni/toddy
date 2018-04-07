#ifndef ERR_HANDLER_H
#define ERR_HANDLER_H
#include<U8g2lib.h>
#include "PubSubClient.h"
#include<Arduino.h>
#define ACKD 102
#define NOACKD 105
class ERR_HANDLER
{

	private:
		bool STA_ACK;
		bool DEV_ACK;
		int ERR;
		int mode;
		int batchrge;
		char ID[30]={'0'};
		String MED,_Timetable;
		int RATE,INFVOL,RTIME,TVOL;
		U8G2 _u8g2;
		PubSubClient mqttclnt;
		 bool wasExecuted1;
		 bool wasExecuted2;
		 bool wasExecuted3;
		 bool wasExecuted4;


	public:
		ERR_HANDLER(U8G2 u8,PubSubClient mqclnt);
		bool display_err(String,int,bool,bool,char[],String,int,int,int,int,int,int);
		void err_alerttype1();
		void err_alerttype2();
		void err_alerttype3();
		void mqttsenderror(char[]);
	        void wasExecuted();

};




#endif



#include "err_handler.h"




bool ERR_HANDLER::display_err(String Ttab, int alt, bool ack_dev, bool ack_sta,char id[30],String med,int rate,int infvol,int rtime,int tvol,int mqttmode,int batc)
{
	STA_ACK=ack_sta;
	DEV_ACK=ack_dev;
	ERR= alt;
	strcpy(ID,id);
	MED=med;
	RATE=rate;
	INFVOL=infvol;
	RTIME=rtime;
	TVOL=tvol;
	_Timetable=Ttab;
        mode = mqttmode;
        batchrge = batc;	

	if(DEV_ACK==true)
	{

		err_alerttype3();
		return false;

	}
      else if(STA_ACK==false&&DEV_ACK==false)
		{

			err_alerttype1();
			return false;
		}
	else if(STA_ACK==true&&DEV_ACK==false)
	 {
	 		err_alerttype2();
	 		return false;

	 }

}


ERR_HANDLER::ERR_HANDLER(U8G2 u8,PubSubClient mqclnt)
{
_u8g2=u8;
mqttclnt=mqclnt;
wasExecuted1=false;
wasExecuted2=false;
wasExecuted3=false;
wasExecuted4=false;
STA_ACK=false;
DEV_ACK=true;
ERR=0;
RATE=1;
INFVOL=1;
RTIME=1;
TVOL=1;

}
void ERR_HANDLER::err_alerttype1()
{//add buzzer code here
		_u8g2.setFont(u8g2_font_crox2hb_tr);
			if(ERR==405)
			{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Block")/2),115);	
		   			_u8g2.print("Block");
					_u8g2.setDrawColor(1);

				
                                    if(wasExecuted1==false){
					for (long i = 0; i < 250; i++ )
				{
  					  digitalWrite(15, HIGH);
   					delayMicroseconds(500);
   					digitalWrite(15, LOW);
  					 delayMicroseconds(500);
				}
					delay(200);
					yield();
			for (long i = 0; i < 250; i++ )
				{
  					  digitalWrite(15, HIGH);
   					delayMicroseconds(500);
   					digitalWrite(15, LOW);
  					 delayMicroseconds(500);
				}
			delay(200);
			yield();
			for (long i = 0; i < 250; i++ )
				{
  					  digitalWrite(15, HIGH);
   					delayMicroseconds(500);
   					digitalWrite(15, LOW);
  					 delayMicroseconds(500);
				}
					mqttsenderror("Block");
					yield();
				      wasExecuted1=true;
															
					}
				}
			else if(ERR==404)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Empty")/2),115);
					_u8g2.print("Empty");
					_u8g2.setDrawColor(1);
					if(wasExecuted2==false){

								for (long i = 0; i < 250; i++ )
				{
  					  digitalWrite(15, HIGH);
   					delayMicroseconds(500);
   					digitalWrite(15, LOW);
  					 delayMicroseconds(500);
				}
								delay(200);
								yield();
							for (long i = 0; i < 250; i++ )
				{
  					  digitalWrite(15, HIGH);
   					delayMicroseconds(500);
   					digitalWrite(15, LOW);
  					 delayMicroseconds(500);
				}
							delay(200);
							yield();
							for (long i = 0; i < 250; i++ )
				{
  					  digitalWrite(15, HIGH);
   					delayMicroseconds(500);
   					digitalWrite(15, LOW);
  					 delayMicroseconds(500);
				}
						mqttsenderror("Empty");
						yield();
					wasExecuted2=true;}	
				}
			else if(ERR==406)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Rate Err")/2),115);
					_u8g2.print("Rate Err");
					_u8g2.setDrawColor(1);
					
					if(wasExecuted3==false){
						for (long i = 0; i < 250; i++ )
				{
  					  digitalWrite(15, HIGH);
   					delayMicroseconds(500);
   					digitalWrite(15, LOW);
  					 delayMicroseconds(500);
				} 
						delay(200);
						yield();
						for (long i = 0; i < 250; i++ )
				{
  					  digitalWrite(15, HIGH);
   					delayMicroseconds(500);
   					digitalWrite(15, LOW);
  					 delayMicroseconds(500);
				}
				       mqttsenderror("Rate_Err");
				       yield();
					wasExecuted3=true;}
				}
			else if(ERR==101)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Complete")/2),115);
					_u8g2.print("Complete");
					_u8g2.setDrawColor(1);
				
					if(wasExecuted4==false){
					mqttsenderror("Complete");
					yield();
                                        wasExecuted4=true;}
				}
}

void ERR_HANDLER::err_alerttype2()
{
	_u8g2.setFont(u8g2_font_crox2hb_tr);
			if(ERR==405)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Block")/2),115);	
					_u8g2.print("Block");
					_u8g2.setDrawColor(1);
					_u8g2.setPowerSave(0);


				}
			else if(ERR==404)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Empty")/2),115);
					_u8g2.print("Empty");
					_u8g2.setDrawColor(1);
					_u8g2.setPowerSave(0);
				}
			else if(ERR==406)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Rate Err")/2),115);
					_u8g2.print("Rate Err");
					_u8g2.setDrawColor(1);
					_u8g2.setPowerSave(0);
		
				}
			else if(ERR==101)
				{
					_u8g2.setDrawColor(2);
					_u8g2.drawBox(0,92,64,36);
					_u8g2.setDrawColor(0);
					_u8g2.setCursor(32-(_u8g2.getStrWidth("Complete")/2),115);
					_u8g2.print("Complete");
					_u8g2.setDrawColor(1);
					_u8g2.setPowerSave(0);

				}
}
//function to publish error
void ERR_HANDLER::mqttsenderror(char errortype[20])
{
if(mode==1)
{
	char e_data[80];
	String medi=MED+"-"+_Timetable+"-"+errortype;
	  const char* chr = medi.c_str();
	  sprintf(e_data,"%s-%d-%d-%d-%d-%d",chr,RATE,INFVOL,RTIME,TVOL,batchrge);
	    if (mqttclnt.connected()) 
	    {

		const char* mqtt_channel_error="dripo/%s/mon";
		char error_channel[80];
	    	sprintf(error_channel,mqtt_channel_error,ID);
	    	mqttclnt.publish(error_channel, e_data);
		}
	    yield();
}	      
}


void ERR_HANDLER::err_alerttype3()
{

			if(ERR==405)
				{
				
					mqttsenderror("Block_ACK");
					yield();
			
				}
			else if(ERR==404)
				{
				
					mqttsenderror("Empty_ACK");
					yield();
				}
			else if(ERR==406)
				{
			
					mqttsenderror("Rate_Err_ACK");
					yield();
				}
			else if(ERR==101)
				{
				
					mqttsenderror("Complete_ACK");
					yield();
				}


}

void ERR_HANDLER::wasExecuted()

{
wasExecuted1=false;
wasExecuted2=false;
wasExecuted3=false;
wasExecuted4=false;
}

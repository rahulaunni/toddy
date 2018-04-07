int send_req(int Data)
{
  const char* DRIPO_NAME = "DRIPO-%d";
  sprintf(id, DRIPO_NAME, ESP.getChipId());
  if (!mqttClient.connected()){
    return 7;
    }
  else{
  switch(Data){
    case 0:
    {
      char e_data[50];
      String medi = _dripo.getMed();
      const char* chr = medi.c_str();
      sprintf(e_data, "%s", chr);
      sprintf(pat_channel, mqtt_channel_req, id);
      mqttClient.publish(pat_channel, chr);
      yield();
      return 7;
      break;
    }
    case 1:
    {
      sprintf(pat_channel, mqtt_channel_bedreq, id);
      mqttClient.publish(pat_channel, "bed");
      yield();
      return 7;
      break;
    }
    case 2:
    {
      String medi = _dripo.getBed();
      const char* chr = medi.c_str();
      sprintf(pat_channel, mqtt_channel_medreq, id);
      mqttClient.publish(pat_channel, chr);
      yield();
      return 7;
      break;
    }
    case 3:
    {
      String medi = _dripo.getMed();
      const char* chr = medi.c_str();
      sprintf(pat_channel, mqtt_channel_ratereq, id);
      mqttClient.publish(pat_channel, chr);
      yield();
      return 7;
      break;
    }
    case 4:
    {
      char e_data[80];
      int SRate = _dripo.getRateMl();
      int SIvol = _dripo.getvolInf();
      int SRtime = _dripo.getRtime();
      int Tvol = _dripo.getTvol();
      String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + "start";
      const char* chr = medi.c_str();
      sprintf(e_data, "%s-%d-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol, stateOfCharge,time4rate2set);
      sprintf(pat_channel, mqtt_channel_mon, id);
      mqttClient.publish(pat_channel, e_data);
      yield();
      time4rate2set =0;
      return 7;
      break;
    }
    case 5:
    {
      char e_data[80];
      int SRate = _dripo.getRateMl();
      int SIvol = _dripo.getvolInf();
      int SRtime = _dripo.getRtime();
      int Tvol = _dripo.getTvol();
      String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + "stop";
      const char* chr = medi.c_str();
      sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol, stateOfCharge);
      sprintf(pat_channel, mqtt_channel_mon, id);
      mqttClient.publish(pat_channel, e_data);
      yield();
      return 7;
      break;
    }
    case 6:
    {
      char e_data[80];                   // all data will merged to this
      int SRate = _dripo.getRateMl();    //get rate in ml
      int SIvol = _dripo.getvolInf();    // get infused volume
      int Tvol = _dripo.getTvol();       //get total volume
      int SRtime = _dripo.getRtime();    //get remaining time
      String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + "infusing"; //get medicine id,timetable id and status and merged
      const char* chr = medi.c_str();                                          // converted to const char to send via mqtt
      sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol, stateOfCharge);     // all data is merged
      sprintf(rate_channel, mqtt_channel_mon, id);                           // merge device id with the rate channel to publish data
      mqttClient.publish(rate_channel, e_data);                        // publish data to rate channel and data is retained true so that if a new client is
      yield() ;
      return 7;
      break;
    }
    default:
    {
//      delay(10);
      return 7;
      break;
    }
  }
    
    }

}
boolean sendInfErr(boolean Flag,String err)
{
  if(Flag == true){
      char e_data[80];                   // all data will merged to this
      int SRate = _dripo.getRateMl();    //get rate in ml
      int SIvol = _dripo.getvolInf();    // get infused volume
      int Tvol = _dripo.getTvol();       //get total volume
      int SRtime = _dripo.getRtime();    //get remaining time
      String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + err; //get medicine id,timetable id and status and merged
      const char* chr = medi.c_str();                                          // converted to const char to send via mqtt
      sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol, stateOfCharge);     // all data is merged
      sprintf(rate_channel, mqtt_channel_mon, id);                           // merge device id with the rate channel to publish data
      mqttClient.publish(rate_channel, e_data);                        // publish data to rate channel and data is retained true so that if a new client is
      yield() ;

  }
      return false;
  
}
boolean sendErrAck(boolean Flag,String err)
{
  if(Flag == true && prev_inf_save==1){
           char e_data[80];                   // all data will merged to this
      int SRate = _dripo.getRateMl();    //get rate in ml
      int SIvol = _dripo.getvolInf();    // get infused volume
      int Tvol = _dripo.getTvol();       //get total volume
      int SRtime = _dripo.getRtime();    //get remaining time
      String medi = _dripo.getMed() + "-" + _dripo.getTimetable() + "-" + err+"_ACK"; //get medicine id,timetable id and status and merged
      const char* chr = medi.c_str();                                          // converted to const char to send via mqtt
      sprintf(e_data, "%s-%d-%d-%d-%d-%d", chr, SRate, SIvol, SRtime, Tvol, stateOfCharge);     // all data is merged
      sprintf(rate_channel, mqtt_channel_mon, id);                           // merge device id with the rate channel to publish data
      mqttClient.publish(rate_channel, e_data);                        // publish data to rate channel and data is retained true so that if a new client is
      yield() ; 
  }
  return false;
}



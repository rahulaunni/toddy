//File contains most of the UI fns
//Print Dev name on screen
void UI_Logo() {



  u8g2.setFont( u8g2_font_profont22_tf );
  u8g2.setCursor(4, 64);
  u8g2.print("Dripo");
  // u8g2.drawXBM( 25, 30, siteic_width, siteic_height, siteic_bits);

}

//connecting to wifi network
void UI_Wifi()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(-1.5, 27);
  u8g2.print("connecting");
  u8g2.setCursor(8, 47);
  u8g2.print("to Wi-Fi");
  u8g2.setCursor(7, 67);
  u8g2.print("network");
  u8g2.drawXBM( 20, 85, wifi_01_width, wifi_01_height, wifi_01_bits);

}

//MAin Menu
void UI_Menu()

{
  Menu.displayc();

}


//Rate Menu-- contains monitoring mode also
void UI_Rate()
{


  //analogWriteFreq(38000);           ///set ir frequency to 38khz
  analogWrite(IR_PIN, irAmp);       // Start Ir
  if (analogRead(A0) < 505 && irAmp < 1014)
  {
    irAmp = irAmp + 1;
  }

  else if (analogRead(A0) > 535 && irAmp > 0)
  {
    irAmp = irAmp - 1;
  }
  // analogWrite(IR_PIN, 700);
  //logstatus=LogData(logtime,logstatus);      //log data on each drop
  // attachInterrupt(digitalPinToInterrupt(DROP_PIN), checkdrop, HIGH);

  u8g2.setDrawColor(1);
  String txt;
  // if (outofrange == false) {
  txt = _dripo.getRate();
  u8g2.setFont(u8g2_font_timR24_tn);
  u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 47);
  u8g2.print(_dripo.getRate());
  // }

  //  else{
  //    u8g2.setCursor(32, 47);
  //    u8g2.print("0");
  //
  //  }

  // u8g2.drawHLine(0, 64, 13);
  // u8g2.drawHLine(51, 64, 13);


  u8g2.setDrawColor(detect1);                   // change to 0 when detects otherwise 2
  u8g2.drawBox(13, 57, 38, 15);
  u8g2.setDrawColor(detect2);                   //change to 1 when detects  otherwise 0
  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(19, 68);
  u8g2.print("dpm");
  u8g2.setDrawColor(1);
  if (detect1 == 0 && detect2 == 1) //for drop notification .the dpm icons blinks in each drop
  {
    long detecttime = millis();
    if (detecttime - lastDAttempt > 200)
    {
      detect1 = 2;
      detect2 = 0;
      lastDAttempt = 0;
    }

  }


  //first state shows the rate to set in screen// idle time is made 0 to disable powersave mode
  if (MonState == 0) {
   //varaible to take time taken for rate set for usability test purpose
    idle_time = millis();      //disable powersave mode
    u8g2.setCursor(0, 92);
    u8g2.print("Rate to set");
    u8g2.setCursor(34, 126);
    u8g2.print("dpm");
    u8g2.setFont(u8g2_font_timR18_tn);
    u8g2.setCursor(0, 116);
    u8g2.print(_dripo.getR2setDPM());
    //u8g2.print(analogRead(A0));
  }

  // canceling infusion
  else if (MonState == 1) {
    u8g2.setCursor(8, 92);
    u8g2.print("Cancel?");
    dialogbox.dialog_box("No&Yes&", 102, 2);

  }

  //Ask for move to monitring state or not
  else if (MonState == 2) {
    u8g2.setCursor(5, 92);
    u8g2.print("Monitor?");
    dialogbox.dialog_box("No&Yes&", 102, 2);

  }
  //monitoring state
  else if (MonState == 3) {

    altmsg = _dripo.Alert((millis()-dropmillis));    //alert msg is created using the time elapsed btween drops
    yield();


    if (altmsg == "NO_ERR" || devAck == true)
    {

      if (altmsg == "NO_ERR")
      {
        devAck = false;
        staAck = false;

//        if (ticker_reached ) {
//
if(dcount%50 == 0 && inf_msg_send == true){   //to send infusing message for every 50th drop
  send_msg_flag = true;
  
  }
 if(send_msg_flag){   
        writeEprom = 1;
        if (prev_inf_save == 1) {
           DataStatus = 6;
        }
//      ticker_reached = false;                                                // data is send and ticker is reset
   send_msg_flag = false;
   inf_msg_send = false;
      }
      }

      exFlag = true;
      u8g2.setCursor(0, 92);
      u8g2.print("Vol infusd");
      u8g2.setCursor(38, 128);
      u8g2.print("ml");
      u8g2.setFont(u8g2_font_timR18_tn);
      u8g2.setCursor(0, 116);
      u8g2.print(_dripo.getvolInf());

    }
    // else if(devAck==true)
    //  {
    //   _errAlert.wasExecuted();
    //    u8g2.setCursor(0, 92);
    //    u8g2.print("Vol infused");
    //    u8g2.setCursor(36, 128);
    //    u8g2.print("ml");
    //    u8g2.setFont(u8g2_font_timR18_tn);
    //    u8g2.setCursor(0, 116);
    //    u8g2.print(_dripo.getvolInf());
    //  }
    else if (altmsg != "NO_ERR")
    {
      //to display error in screen
        u8g2.setFont(u8g2_font_crox2hb_tr);
       u8g2.setDrawColor(2);
       u8g2.drawBox(0,92,64,36);
       u8g2.setDrawColor(0);
       u8g2.setCursor(32-(u8g2.getStrWidth(altmsg.c_str())/2),115); 
       u8g2.print(altmsg);
       u8g2.setDrawColor(1);
       sleeper = false;
       //to send error if both stacAck and devAck is false for online infusion
       if(staAck == false && devAck == false  && exFlag == true)
       {
        if(prev_inf_save ==1 ){
                  sendmqtterrorMsgFlag = true;
        }
        if(altmsg=="Block" || altmsg == "Empty" || altmsg=="Complete"){
          beeperCount = 3;
        }
        else {
          beeperCount = 2;
        }
              exFlag = false;
prev_acktime=millis();
       }
       
      if (staAck == true)
      {
        acktime = millis();
        if (acktime - prev_acktime >= 120000)
        {
          staAck = false;
          prev_acktime = acktime;
          //_errAlert.wasExecuted();
          exFlag = true;
        }


      }

      if (staAck == false)
      {
        alerttime = millis();
        if (alerttime - prev_alerttime >= 20000)
        {
          prev_alerttime = alerttime;
          prev_acktime = alerttime;
         // _errAlert.wasExecuted();
          exFlag = true;

        }
      }
      //callErrHandlerFlag = true;
      //sleeper = _errAlert.display_err(_dripo.getTimetable(), altmsg, devAck, staAck, id, _dripo.getMed(), _dripo.getRateMl(), _dripo.getvolInf(), _dripo.getRtime(), _dripo.getTvol(), prev_inf_save, stateOfCharge);
      //yield();
      // if(callerrhandlerflag==true)
      // {
      //     sleeper=_errAlert.display_err(altmsg,devAck,staAck,id,_dripo.getMed());
      //     callerrhandlerflag=false;

      // }
      switch (get_button())

      {
        case 1:
          devAck = true;
          if (altmsg == "Empty" || altmsg == "Complete")
          {
            writeEprom=2;
            prev_inf = 0;
            if (prev_inf_save == 1)
            {
              DataStatus = 5;
            }
            state = 2;
            ui_state = 2;
            infuseMenu = 1;
            MonState = 0;
          }
          else {
            //send station ack
                  senderrAckFlag = true;
            //sleeper = _errAlert.display_err(_dripo.getTimetable(), altmsg, devAck, staAck, id, _dripo.getMed(), _dripo.getRateMl(), _dripo.getvolInf(), _dripo.getRtime(), _dripo.getTvol(), prev_inf_save, stateOfCharge);
              //yield();
            PMonState = MonState;
            MonState = 0;
          }

          //        devAck = false;
          staAck = false;
          break;

      }

    }




  }
}

void UI_infuse()

{
  if (infuseMenu == 0)
  {
    dpf.display_menu();
    switch (get_button())
    {
      case 1: if (dpf.getSelect() == "<<back") {
          infuseMenu = 2;
        }
        else {
          _dripo.setDf(dpf.getSelect());
          DataStatus = 3;
          //  infuseMenu = 1;
        }
        break;
      case 3: dpf.up();
        break;
      case 4: dpf.dwn();
        break;
    }
  }

  if (infuseMenu == 1)
  {
    bed.display_menu();
    switch (get_button())
    {
      case 1: if (bed.getSelect() == "<<back")
        {

          state = 19;
          ui_state = 19;
        }
        else {
          _dripo.setBed(bed.getSelect());
          DataStatus = 2;
          //    infuseMenu = 2;
          //  ui_state = 3;

          //  state = 9;
        }
        break;
      case 3: bed.up();
        break;
      case 4: bed.dwn();
        break;
    }
  }

  if (infuseMenu == 2)
  {
    med.display_menu();
    switch (get_button())
    {
      case 1: if (med.getSelect() == "<<back")
        {
          infuseMenu = 1;
        }
        else {
          _dripo.setMed(med.getSelect());
          DataStatus = 0;

          //        infuseMenu = 3;

          //   ui_state = 3;

          //   state = 9;
        }
        break;
      case 3: med.up();
        break;
      case 4: med.dwn();
        break;
    }
  }


  if (infuseMenu == 3)
  {
    u8g2.setDrawColor(2);
    u8g2.drawBox(0, 0, 64, 13);
    u8g2.drawBox(0, 27, 64, 13);
    u8g2.drawBox(0, 56, 64, 14);
    u8g2.drawBox(0, 86, 64, 14);
    u8g2.setDrawColor(0);

    String txt;
    u8g2.setFont(u8g2_font_crox2h_tr);
    int strwidth = u8g2.getStrWidth("Name");
    u8g2.setCursor(32 - (strwidth / 2), 11);
    u8g2.print("Name");

    strwidth = u8g2.getStrWidth("Medicine");
    u8g2.setCursor(32 - (strwidth / 2), 38);
    u8g2.print("Medicine");

    strwidth = u8g2.getStrWidth("Volume");
    u8g2.setCursor(32 - (strwidth / 2), 67);
    u8g2.print("Volume");

    strwidth = u8g2.getStrWidth("Dpf");
    u8g2.setCursor(32 - (strwidth / 2), 97);
    u8g2.print("Dpf");
    u8g2.setDrawColor(1);

    txt = _dripo.getMedName();
    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 52);
    u8g2.print(_dripo.getMedName());

    txt = _dripo.getName();
    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 26);
    u8g2.print(_dripo.getName());

    txt = _dripo.getTvol();
    u8g2.setCursor(25 - (u8g2.getStrWidth(txt.c_str()) / 2), 82);
    u8g2.print(_dripo.getTvol());
    txt = _dripo.getDf();
    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 111);
    u8g2.print(_dripo.getDf());
    u8g2.setCursor(41, 82);
    u8g2.print("ml");



    dialogbox.dialog_box("No&Yes&", 113.5, 2);
    //    String txt;
    //    txt = _dripo.getName();
    //    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 30);
    //    u8g2.print(_dripo.getName());
    //    txt = _dripo.getMedName();
    //    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 50);
    //    u8g2.print(_dripo.getMedName());
    //    txt = _dripo.getTvol();
    //    u8g2.setCursor(22 - (u8g2.getStrWidth(txt.c_str()) / 2), 70);
    //    u8g2.print(_dripo.getTvol());
    //    txt = _dripo.getDf();
    //    u8g2.setCursor(22 - (u8g2.getStrWidth(txt.c_str()) / 2), 90);
    //    u8g2.print(_dripo.getDf());
    //    u8g2.setCursor(36, 70);
    //    u8g2.print("ml");
    //    u8g2.setCursor(36, 90);
    //    u8g2.print("dpf");
    //
    //    dialogbox.dialog_box("No&Yes&", 102, 2);

    switch (get_button())
    {
      case 1: if (dialogbox.getDia() == "No") {
          infuseMenu = 0;

        }
        else if (dialogbox.getDia() == "Yes") {
           time4rate2set = millis();
          char med[35];
          char timet[35];
          String timeidcpy = _dripo.getTimetable();
          timeidcpy.toCharArray(timet, 35);

          String medidcpy = _dripo.getMed();
          medidcpy.toCharArray(med, 35);

          EEPROM.begin(512);
          EEPROM.put(40, _dripo.getDf());
          EEPROM.commit();


          EEPROM.put(50, timet);
          EEPROM.commit();

          EEPROM.put(90, med );
          EEPROM.commit();

          EEPROM.put(130, _dripo.getTvol());
          EEPROM.commit();

          EEPROM.put(150, _dripo.getrate2set());
          EEPROM.commit();
          EEPROM.end();
          prev_inf_save = 1;
          if (stateOfCharge > (10 * (_dripo.getTtime() / 60)))
          {
            //            char med[35];
            //            char timet[35];
            //            String timeidcpy = _dripo.getTimetable();
            //            timeidcpy.toCharArray(timet, 35);
            //
            //            String medidcpy = _dripo.getMed();
            //            medidcpy.toCharArray(med, 35);
            //
            //            EEPROM.begin(512);
            //            EEPROM.put(40, _dripo.getDf());
            //            EEPROM.commit();
            //
            //
            //            EEPROM.put(50, timet);
            //            EEPROM.commit();
            //
            //            EEPROM.put(90, med );
            //            EEPROM.commit();
            //
            //            EEPROM.put(130, _dripo.getTvol());
            //            EEPROM.commit();
            //
            //            EEPROM.put(150, _dripo.getrate2set());
            //            EEPROM.commit();
            //            EEPROM.end();
            //            prev_inf_save = 1;
//                                    ui_state = 3;   //testing online
//                                    state = 9;
            irAmp = 450;
            ui_state = 16;
            state = 18;
          }
          else
          {
            irAmp = 450;
            ui_state = 13;
            state = 16;
          }

        }
        break;
      case 3: dialogbox._diaup();
        break;
      case 4: dialogbox._diadwn();
        break;
    }
  }
}

///Update UI....will be removed
void UI_Update() {

  u8g2.setDrawColor(1);
  // if (up_date == true)
  // {
  u8g2.setDrawColor(2);
  u8g2.drawBox(0, 110, 64, 14);

  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_crox2h_tr);
  int strwidth = u8g2.getStrWidth(up_status.c_str());
  u8g2.setCursor(32 - (strwidth / 2), 121);
  u8g2.print(up_status.c_str());

  // }
  u8g2.setDrawColor(1);

  // u8g2.drawXBM(8, 35, update_icon_width, update_icon_height, update_icon_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Press") / 2), 10);
  u8g2.print("Press");
  u8g2.setCursor(32 - ( u8g2.getStrWidth("and Hold") / 2), 30);
  u8g2.print("and Hold");
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Select Key") / 2), 50);
  u8g2.print("Select Key");
  u8g2.setCursor(32 - ( u8g2.getStrWidth("for") / 2), 70);

  u8g2.print("for");
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Updating") / 2), 90);

  u8g2.print("Updating");



}

//Shutdown dialog box
void UI_Shutdown()
{
  u8g2.setFont(u8g2_font_crox2h_tr);

  u8g2.setDrawColor(1);

  u8g2.setCursor(32 - (u8g2.getStrWidth("Sleep") / 2), 62);
  u8g2.print("Sleep");
  dialogbox.dialog_box("No&Yes&", 72, 2);
}


//Setup MEnu
void UI_Setup()
{
  //U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R3, /* clock=*/ 1, /* data=*/2, /* cs=*/ 10);

  Setup.display_menu();
  analogWrite(IR_PIN, 0);

}

//shows tis UI when data is requestd and wifi is not connected
void UI_WifiConf()
{
  u8g2.setCursor(1, 62);
  u8g2.print("Config Wifi");
  dialogbox.dialog_box("No&Yes&", 72, 2);

}

//UI_Reset
void UI_reset()
{
  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.setCursor(9, 48);
  u8g2.print("Factory");
  u8g2.setCursor(12, 62);
  u8g2.print("Reset");
  dialogbox.dialog_box("No&Yes&", 72, 2);

}
//UI Err from Server
void UI_S_Err()
{
  u8g2.drawXBM( 15, 0, add_alert_black_36x36_width, add_alert_black_36x36_height, add_alert_black_36x36_bits);
  err_or._displayErr();
}


//just a device Menu to know the status of device.. need updation
void UI_dripo()
{
  //digitalWrite(BUZZ_PIN, HIGH);
  //tone(BUZZ_PIN,1000,700);
  //analogWriteFreq(38000);
  analogWrite(IR_PIN, irAmp);
  // analogWrite(IR_PIN, 700);
  // u8g2=U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI (U8G2_R3, /* clock=*/ 1, /* data=*/2, /* cs=*/ U8X8_PIN_NONE);
  //  Wire.beginTransmission(0x20); // transmit to device #20 (0x20)
  //  Wire.write(0x30);// sends instruction byte
  //  Wire.write(0x03);
  // Wire.endTransmission();
  //
  //    Wire.requestFrom(0x20, 2);
  //  byte MSB = Wire.read();
  //byte LSB = Wire.read();

  if (analogRead(A0) < 505 && irAmp < 1014)
  {
    irAmp = irAmp + 5;
  }

  if (analogRead(A0) > 525 && irAmp > 0)
  {
    irAmp = irAmp - 5;
  }

  u8g2.setFont(u8g2_font_profont10_tf);

  const char* DRIPO_NAME = "DRIPO-%d";

  u8g2.setCursor(0, scroller + 10);
  u8g2.print("Dev Name:");
  sprintf(id, DRIPO_NAME, ESP.getChipId());
  u8g2.setCursor(0, scroller + 22);
  u8g2.print(id);
  u8g2.setCursor(0, scroller + 34);
  u8g2.print("Address:");
  u8g2.setCursor(0, scroller + 46);
  u8g2.print(WiFi.localIP());
  u8g2.setCursor(0, scroller + 58);
  u8g2.print("Server:");
  u8g2.setCursor(0, scroller + 70);
  u8g2.print(mqtt_server);
  u8g2.setCursor(0, scroller + 82);
  u8g2.print("Version:");
  u8g2.setCursor(0, scroller + 94);
  u8g2.print(VERSION);
  u8g2.setCursor(0, scroller + 106);
  u8g2.print("Battery:");
  u8g2.setCursor(0, scroller + 118);
  u8g2.print( batteryMonitor.getSoC());
  u8g2.setCursor(0, scroller + 130);
  u8g2.print("Sesnsor Calib:");
  u8g2.setCursor(0, scroller + 142);
  u8g2.print( analogRead(A0));
  u8g2.setCursor(0, scroller + 154);
  u8g2.print("IR value");
  u8g2.setCursor(0, scroller + 166);
  //u8g2.print(ESP.getFreeSketchSpace());
  u8g2.print(irAmp);
  u8g2.setCursor(21, scroller + 166);
  u8g2.print("/900");

  //u8g2.print(ESP.getResetReason());

  u8g2.setCursor(0, scroller + 178);
  u8g2.print("---EVELABS---");

  //    u8g2.setCursor(32, 40);
  //  //u8g2.print(bigNum);
  //  u8g2.setCursor(0, 70);
  //  u8g2.print( batteryMonitor.getSoC());
  //  u8g2.setCursor(0, 100);
  //  u8g2.print(cellVoltage);



  u8g2.setFont(u8g2_font_crox2h_tr);


}

//show server err if data is requestd and Mosquitto is not connected

void UI_ServErr()
{
  u8g2.setCursor(32 - (u8g2.getStrWidth("connection") / 2), 42);
  u8g2.print("connection");
  u8g2.setCursor(32 - (u8g2.getStrWidth("error") / 2), 62);
  u8g2.print("error");
  dialogbox.dialog_box("Ok&", 72, 1);

}
//Bat LOW
void UI_batlow()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.drawXBM( 8, 35, batlow_width, batlow_height, batlow_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("BAT LOW") / 2), 100);
  u8g2.print("BAT LOW");
}

//BAttery Check Before starting Infusion as warning to show the battey level is insfficent for the insfusion
void UI_InfBatChK()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  // u8g2.drawXBM( 8, 30, batlow_width, batlow_height, batlow_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Battery") / 2), 20);
  u8g2.print("Battery");
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Won't") / 2), 40);
  u8g2.print("Won't");
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Last for") / 2), 60);
  u8g2.print("Last for");
  u8g2.setCursor(13, 80);
  u8g2.setFont(u8g2_font_crox2hb_tr);
  u8g2.print((_dripo.getTtime() / 60));
  u8g2.setCursor(36, 80);
  u8g2.print("Hrs");
  u8g2.setFont(u8g2_font_crox2h_tr);

  // u8g2.setCursor(32 - ( u8g2.getStrWidth("BAT LOW") / 2), 90);
  //  u8g2.print("BAT LOW");
  dialogbox1.dialog_box("Ok&", 100, 1);

}

//BAttery LOW UI
void UI_batchk()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.drawXBM( 8, 35, batlow_width, batlow_height, batlow_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("BAT LOW") / 2), 100);
  u8g2.print("BAT LOW");

}

//Battey Full UI
void UI_batfull()
{

  u8g2.setFont(u8g2_font_crox2h_tr);
  u8g2.drawXBM( 8, 35, batfull_width, batfull_height, batfull_bits);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("BAT FULL") / 2), 100);
  u8g2.print("BAT FULL");
}

void Off_Infuse()
{
  static int pos = 40, w = 30, vol = 500, rate = 100;
  if (Of_infuseMenu == 0)
  {

    dpf.display_menu();
    switch (get_button())
    {
      case 1: if (dpf.getSelect() == "<<back") {
          state = 19;
          ui_state = 19;
        }
        else {
          _dripo.setDf(dpf.getSelect());
          Of_infuseMenu = 1 ;
        }
        break;
      case 3: dpf.up();
        break;
      case 4: dpf.dwn();
        break;
    }
  }


  if (Of_infuseMenu == 1)
  {
    String VOLUME = String(vol);
    u8g2.setDrawColor(2);
    u8g2.drawBox(0, 0, 64, 14);
    u8g2.drawBox(0, 105, 64, 20);

    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_crox2h_tr);
    int strwidth = u8g2.getStrWidth("Volume");
    u8g2.setCursor(32 - (strwidth / 2), 11);
    u8g2.print("Volume");

    //u8g2.setDrawColor(1);
    u8g2.setDrawColor(2);
    u8g2.drawBox(0, pos, 64, w);
    u8g2.setDrawColor(1);
    strwidth = u8g2.getStrWidth("^");
    u8g2.setCursor(32 - (strwidth / 2), 43);
    u8g2.print("^");
    u8g2.setFontDirection(2);
    u8g2.setCursor(38 - (strwidth / 2), 66);
    u8g2.print("^");
    u8g2.setFontDirection(0);

    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_timR18_tn);

    strwidth = u8g2.getStrWidth(VOLUME.c_str());
    u8g2.setCursor(32 - (strwidth / 2), 63);
    u8g2.print(VOLUME);
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_crox2h_tr);
    u8g2.setCursor(43, 88);
    u8g2.print("ml");
    u8g2.setDrawColor(0);
    strwidth = u8g2.getStrWidth("Ok");
    u8g2.setCursor(32 - (strwidth / 2), 120);
    u8g2.print("Ok");

    u8g2.setDrawColor(1);


    // u8g2.drawFrame(0, 40, 64, 30);


    switch (get_button())
    {
      case 1: _dripo.setTvol(VOLUME);
        Of_infuseMenu = 2;

        break;
      case 3: if (vol < 1000) {
          vol = vol + 25;
        }
        break;
      case 4: if (vol > 50) {
          vol = vol - 25;
        }
        break;
    }
  }


  if (Of_infuseMenu == 2)
  {
    String RATE = String(rate);
    u8g2.setDrawColor(2);
    u8g2.drawBox(0, 0, 64, 14);
    u8g2.drawBox(0, 105, 64, 20);
    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_crox2h_tr);
    int strwidth = u8g2.getStrWidth("Rate");
    u8g2.setCursor(32 - (strwidth / 2), 11);
    u8g2.print("Rate");

    // u8g2.setDrawColor(1);
    u8g2.setDrawColor(2);

    u8g2.drawBox(0, pos, 64, w);
    u8g2.setDrawColor(1);

    strwidth = u8g2.getStrWidth("^");
    u8g2.setCursor(32 - (strwidth / 2), 43);
    u8g2.print("^");
    u8g2.setFontDirection(2);
    u8g2.setCursor(38 - (strwidth / 2), 66);
    u8g2.print("^");
    u8g2.setFontDirection(0);

    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_timR18_tn);

    strwidth = u8g2.getStrWidth(RATE.c_str());
    u8g2.setCursor(32 - (strwidth / 2), 63);
    u8g2.print(RATE);
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_crox2h_tr);
    u8g2.setCursor(31, 88);
    u8g2.print("ml/hr");
    u8g2.setDrawColor(0);
    strwidth = u8g2.getStrWidth("Ok");
    u8g2.setCursor(32 - (strwidth / 2), 120);
    u8g2.print("Ok");

    u8g2.setDrawColor(1);




    switch (get_button())
    {
      case 1: _dripo.setR2set(RATE);
        Of_infuseMenu = 3;

        break;
      case 3: if (rate < (250 * 60) / _dripo.getDf()) {
          rate = rate + 1;
        }
        break;
      case 4: if (rate > (5 * 60) / _dripo.getDf()) {
          rate = rate - 1;
        }
        break;
    }
  }

  if (Of_infuseMenu == 3)
  {
    u8g2.setDrawColor(2);
    u8g2.drawBox(0, 0, 64, 14);
    u8g2.drawBox(0, 48, 64, 14);
    u8g2.drawBox(0, 78, 64, 14);
    u8g2.setDrawColor(0);

    String txt;
    u8g2.setFont(u8g2_font_crox2h_tr);
    int strwidth = u8g2.getStrWidth("Rate");
    u8g2.setCursor(32 - (strwidth / 2), 11);
    u8g2.print("Rate");


    strwidth = u8g2.getStrWidth("Volume");
    u8g2.setCursor(32 - (strwidth / 2), 59);
    u8g2.print("Volume");

    strwidth = u8g2.getStrWidth("Dpf");
    u8g2.setCursor(32 - (strwidth / 2), 89);
    u8g2.print("Dpf");
    u8g2.setDrawColor(1);

    txt = _dripo.getR2setDPM();
    u8g2.setCursor(16 - (u8g2.getStrWidth(txt.c_str()) / 2), 44);
    u8g2.print(_dripo.getR2setDPM());

    txt = _dripo.getrate2set();
    u8g2.setCursor(16 - (u8g2.getStrWidth(txt.c_str()) / 2), 26);
    u8g2.print(_dripo.getrate2set());

    txt = _dripo.getTvol();
    u8g2.setCursor(16 - (u8g2.getStrWidth(txt.c_str()) / 2), 74);
    u8g2.print(_dripo.getTvol());
    txt = _dripo.getDf();
    u8g2.setCursor(32 - (u8g2.getStrWidth(txt.c_str()) / 2), 106);
    u8g2.print(_dripo.getDf());
    u8g2.setCursor(41, 74);
    u8g2.print("ml");
    u8g2.setCursor(34, 44);
    u8g2.print("dpm");
    u8g2.setCursor(34, 26);
    u8g2.print("ml/hr");


    dialogbox.dialog_box("No&Yes&", 113, 2);

    switch (get_button())
    {
      case 1: if (dialogbox.getDia() == "No") {
          Of_infuseMenu = 0;

        }
        else if (dialogbox.getDia() == "Yes") {
          EEPROM.begin(512);
          EEPROM.put(40, _dripo.getDf());
          EEPROM.commit();

          EEPROM.put(130, _dripo.getTvol());
          EEPROM.commit();

          EEPROM.put(150, _dripo.getrate2set());
          EEPROM.commit();
          //            EEPROM.put(200, 2);    //infusion started and it is not completed
          //            EEPROM.commit();
          EEPROM.end();
          prev_inf_save = 2;

          if (stateOfCharge > (10 * (_dripo.getTtime() / 60)))
          {

            //
            //            EEPROM.begin(512);
            //            EEPROM.put(40, _dripo.getDf());
            //            EEPROM.commit();
            //
            //            EEPROM.put(130, _dripo.getTvol());
            //            EEPROM.commit();
            //
            //            EEPROM.put(150, _dripo.getrate2set());
            //            EEPROM.commit();
            //            //            EEPROM.put(200, 2);    //infusion started and it is not completed
            //            //            EEPROM.commit();
            //            EEPROM.end();
            //            prev_inf_save = 2;

//                                               ui_state = 3;   //testing offline
//                                              state = 9;

            ui_state = 16;
            state  = 18;
            irAmp = 450;

          }
          else
          {
            irAmp = 450;
            ui_state = 13;
            state = 16;
          }

        }
        break;
      case 3: dialogbox._diaup();
        break;
      case 4: dialogbox._diadwn();
        break;
    }
  }


}




//calibration screen.. loading animation
void UI_Calib()
{
  u8g2.setFont( u8g2_font_crox1h_tr);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Calibrating") / 2), 20);                    ///wifi hotspot display code
  u8g2.print("Calibrating");
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Sensors") / 2), 33);
  u8g2.print("Sensors");
  if (irAmp == 1020 || irAmp == 0) {
    u8g2.setCursor(32 - ( u8g2.getStrWidth("FAILED!") / 2), 64);
    u8g2.print("FAILED!");
  }
  else {
    load.draw();
  }

  dialogbox1.dialog_box("Exit&", 108, 1);

}

void UI_OnOf()
{
  select.display_menu();

}
/*wifi config exit function with hotspot  animation */

void UI_Hotspot()
{

  u8g2.setFont( u8g2_font_crox1h_tr);
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Hotspot") / 2), 20);                    ///wifi hotspot display code
  u8g2.print("Hotspot");
  u8g2.setCursor(32 - ( u8g2.getStrWidth("Active") / 2), 33);
  u8g2.print("Active");
  //  u8g2.drawXBM( 9, 50,hotspot_width, hotspot_height, hotspot_bits);
  u8g2.drawDisc(32, 67, 4, U8G2_DRAW_ALL);
  dialogbox1.dialog_box("Exit&", 108, 1);

  hotspot.hotspot();
  hotspot1.hotspot();
  hotspot2.hotspot();

  u8g2.setFont(u8g2_font_crox2h_tr);

}



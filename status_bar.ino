void STBAR()
{
  ESP.wdtFeed();
  if (state == 2 || state == 9 || state == 7 || state == 10 || state == 17) {
     stateOfCharge = batteryMonitor.getSoC();
     yield();
    float  widthCharge = map(stateOfCharge, 0, 100, 1, 7.5);
    u8g2.drawXBM(42, 0, battery_width, battery_height, battery_bits);
    for(float i=0;i<=widthCharge;i++)
    {
       u8g2.drawLine(44+i*2, 5,44+i*2, 9);
    }
//    u8g2.drawBox(44, 5, widthCharge, 5);
    
    wifirssi = WiFi.RSSI();
    yield();
    int  widthwifi = map(wifirssi, -90, -30, 1,4);
    if (WiFi.status() == WL_CONNECTED)
    {
    for(int i=0;i<=widthwifi;i++)
    {
   u8g2.drawCircle(0,11,i*3, U8G2_DRAW_UPPER_RIGHT);
   }

    }
    else{
     //add wifi no connection icon here 
   u8g2.drawXBM(0,0 , nowifi_width, nowifi_height, nowifi_bits);

    
    }
    if (stateOfCharge > 85) {
      if (stateOfCharge == 100 && batchkflag == false)
      {
        logo_time = millis();
        prev_ui_state = ui_state;
        prev_b_state = state;
        ui_state = 15;
        state = 17;
        batchkflag = true;
      }
    }
    else if (stateOfCharge > 20)
    {
      batchkflag = false;
    }
    else if (stateOfCharge < 20)
    {
      if (stateOfCharge > 15)
      {
        batchkflag = false;
      }
      if (stateOfCharge < 15 && batchkflag == false)
      {
        logo_time = millis();
        prev_b_state = state;
        prev_ui_state = ui_state;
        ui_state = 14;
        state = 17;
        batchkflag = true;
      }
      else if (stateOfCharge < 12)
      {
        ui_state = 12;
        state = 15;
      }

    }

    if (MonState == 3 || (PMonState == 3 && MonState == 1)) {
      u8g2.drawXBM(20, 0, monitor_width, monitor_height, monitor_bits);
    }

    if ((millis()-idle_time) > 30000 && sleeper == false)
    {
      sleeper = true;
      prev_state = state;
      state = 11;
    }

    u8g2.setDrawColor(1);

  }


}


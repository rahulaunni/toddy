int wifi_connect(int WIFI_STATE)
{
  const char* DRIPO_NAME = "DRIPO-%d";

  sprintf(id, DRIPO_NAME, ESP.getChipId());

  if (WIFI_STATE == 1)
  {
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    timeout--;
    if(timeout<0)
    {
      break;
    }
  }

    if ( WiFi.status() == WL_CONNECTED && strcmp(mqtt_server, "0") != 0) {
      if (!mqttClient.connected()) {
        mqtt_reconnect();
        yield();

      }
    }

    return 2;

  }
    else if (WIFI_STATE == 2)
  {
    // ESP.wdtFeed();

    if ( WiFi.status() == WL_CONNECTED && strcmp(mqtt_server, "0") != 0 ) {
      yield();
      if (!mqttClient.connected()) {
        long now = millis();
        if (now - lastReconnectAttempt > 5000 && connection < 2) {
          lastReconnectAttempt = now;
          connection++;

          // Attempt to reconnect
          if (mqtt_reconnect()) {
            lastReconnectAttempt = 0;
            connection = 0;

          }
          
        }
  
         }
      }
          return 2;

    }

  
  if ( WIFI_STATE == 4)
  {

  
    return 5;
  }

  if ( WIFI_STATE == 5)
  {
    //server.handleClient();

    return 5;
  }
}


void handleRoot() {
  server->send(200, "text/html", "<body style='background:#ff4081;margin:0px'><form action='/action'> <br>Wifi<br><input type='text' name='WiFi' value='SSID'><br>Password<br><input type='password' name='pass' value='pass'><br>IP Address<br><input type='text' name='IP Address' value='mqtt'><br><br><input type='submit' value='Submit'></form></body>");
}

void handleResponse() {
  String wifi_n = server->arg(0);
  String wifi_p = server->arg(1);
  String mqtt_ = server->arg(2);
  wifi_n.toCharArray(wifi_name, 20);
  wifi_p.toCharArray(wifi_pass, 20);
  mqtt_.toCharArray(mqtt_server, 16);
 server->send(200, "text/html", "SUCCESS");
  EEPROM.begin(512);
  EEPROM.put(0, mqtt_server);
  EEPROM.commit();
  EEPROM.put(220, wifi_name);
  EEPROM.commit();
  EEPROM.put(240, wifi_pass);
EEPROM.commit();
  EEPROM.put(270, "0");
  EEPROM.commit();
  EEPROM.end();
  server->stop();
  ESP.restart();

}

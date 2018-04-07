/*Function reconnect the connection wit mosquitto and initilzes the subscribe channnel with QOS*/

boolean mqtt_reconnect() {
//
  mqttClient.setServer(mqtt_server, mqtt_port);         //mosquitto server and port is initilized
 mqttClient.setCallback(callback);      // callback fuction for mosquitto is initilzed. this fuction is called when a message is recieved
yield();
 //  mqttClient.connect("sanjai");

  sprintf(will_msg, mqtt_channel_will, id);

  
char data[30]="offline";
//   mqtt_encrypt(data); 
  
  if (mqttClient.connect(id,will_msg,2,true,data)) {                         // connect to mosqutto server and checks the connection
    yield();

String Status = "Online-"+ESP.getResetReason();
 const char* chr = Status.c_str(); 


//     mqtt_encrypt(data); 

    // sprintf(up_channel, mqtt_channel_update, id);
    // mqttClient.subscribe(up_channel);
    mqttClient.publish(will_msg,chr,true);                  // publishes the device status to chennel 

    //create subscrbe channels
    sprintf(r_channel_df, mqtt_channel_df, id);        
    sprintf(r_channel_pat, mqtt_channel_pat, id);
    //sprintf(r_channel_version, mqtt_channel_version, id);
    sprintf(r_channel_update, mqtt_channel_update, id);
    sprintf(r_channel_med, mqtt_channel_med, id);
    sprintf(r_channel_rate, mqtt_channel_r2set, id);
    sprintf(r_channel_staAck, mqtt_channel_staAck, id);
    sprintf(r_channel_error, mqtt_channel_error, id);


    //subscribe to channels
    mqttClient.subscribe(r_channel_pat, qos);
  //  mqttClient.subscribe(r_channel_version, qos);
    mqttClient.subscribe(r_channel_update, qos);
    mqttClient.subscribe(r_channel_df, qos);
    mqttClient.subscribe(r_channel_med, qos);
    mqttClient.subscribe(r_channel_rate, qos);
    mqttClient.subscribe(r_channel_staAck, qos);
    mqttClient.subscribe(r_channel_error, qos);

  }
  return mqttClient.connected();
}

#include <FS.h>
                #include <EEPROM.h>
//#include <ArduinoJson.h>
#include <Wire.h>
//#include "src/err_handler.h"
#include "src/MENU.h"
#include "src/LOADER.h"
#include "src/DROP.h"
#include "MAX17043.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
//#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
//#include <elapsedMillis.h>
//#include <Ticker.h>
#include "src/icons.h"
#include "src/MAINMENU.h"
#include "src/ICON.h"
#include "src/icons.h"
#include "PubSubClient.h"
//#include <WiFiClient.h>

//#include "src/Crypto.h"
//#include "src/Base64.h"

extern "C" {
#include "user_interface.h"
}
//elapsedMillis timeElapsed, logo_time, idle_time; //dataTicker;
MAX17043 batteryMonitor;
//Ticker ticker;
float wifirssi;
int stateOfCharge;
float cellVoltage;
boolean startDisplay = false;
boolean sleep = false;
//boolean ticker_reached;
boolean sleeper = false;
boolean notified = false;
boolean batchkflag = false;
boolean staAck = false;
boolean devAck = false;
boolean up_date = false;
String up_status = "Exit";
int writeEprom = 0;
int beeperCount =0;
boolean send_msg_flag = false;
boolean inf_msg_send = false;
boolean sendmqtterrorMsgFlag = false;
boolean senderrAckFlag = false;
boolean exFlag = true;



boolean outofrange = false;
boolean drop_detect = false;
int longHoldTime = 2000; // ms hold period: how long to wait for press+hold event
boolean buttonVal = HIGH; // value read from button
boolean buttonLast = HIGH; // buffered value of the button's previous state
long downTime = -1; // time the button was pressed down
long upTime = -1; // time the button was released
int debounce = 20; // ms debounce period to prevent flickering when pressing or releasing the button
boolean longHoldEventPast = false;// whether or not the long hold event happened already
ESP8266WebServer *server;

#define BUZZ_PIN        15
#define ENCODER_PINA     5
#define ENCODER_PINB     13
#define ENCODER_BTN      4
#define DROP_PIN        14
#define WAKE_PIN        16
#define IR_PIN        12
#define ADC_PIN        A0

int timeout = 50;
String altmsg = "NO_ERR";
int state = 0;
int prev_state = 0;
int prev_b_state = 0;
int ui_state = 0;
int prev_ui_state = 0;
int ui_x = 0;
int dot_x = 0;
int wifi_status = 0;
int BTN = 0;
int infuseMenu = 1;
int Of_infuseMenu = 0;

int MonState = 0;
int PMonState = 0;
int qos = 1;
int radius = 5;
int connection = 0;
int  switchon = 1000;
String VERSION = "scotch_v_1.1";
int DataStatus = 7;
long lastReconnectAttempt = 0;
unsigned long acktime;
unsigned long prev_acktime;
unsigned long alerttime;
unsigned long prev_alerttime;
unsigned int lastmillis=0;
unsigned int dropmillis=0;
long dcount=0;

int prev_inf = 0;
int prev_inf_save = 0;

unsigned long int logtime = 1;
int logstatus = 0;
unsigned long int logo_time=0;
unsigned long int idle_time=0;


long lastDAttempt = 0;
int detect1 = 2;
int detect2 = 0;
int time4rate2set =0;//variable for usability test
int irAmp = 450; //set ir value to zero
int scroller = 0;
U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R3, /* clock=*/ 1, /* data=*/3, /* cs=*/ 10);

String t1 = "INFUSE";
String t2 = "SETUP";
//String t3 = "OFFLINE";
String t4 = "SLEEP";
//ICON a[4] = {{t1, ic_opacity_black_24dp_bits, u8g2}, {t2, ic_settings_black_24dp_bits, u8g2}, {t3, offline_bits, u8g2}, {t4, ic_power_settings_new_black_24dp_bits, u8g2}};
ICON a[3] = {{t1, ic_opacity_black_24dp_bits, u8g2}, {t2, ic_settings_black_24dp_bits, u8g2}, {t4, ic_power_settings_new_black_24dp_bits, u8g2}};

MAINMENU Menu(0, a, u8g2);
char *od_f = "15&15&20&20&60&60\0";
//int Off_vol =50;
//int Off_Rate=5;
char *s_up = "wifi&wifi&system&system&update&update&reset&reset\0";
char *if_menu = "ONLINE&ONLINE&OFFLINE&OFFLINE\0";

MENU Setup("Setup", s_up, u8g2);
MENU select("Infuse", if_menu, u8g2);
//MENU  odpf("Dpf", od_f, u8g2);


MENU dpf;

MENU bed;
MENU med;
MENU dialogbox(u8g2);
MENU dialogbox1(u8g2);
LOADER load(4, 15, u8g2);
LOADER hotspot(10, u8g2);
LOADER hotspot1(15, u8g2);
LOADER hotspot2(20, u8g2);
LOADER err_or;


DROP _dripo;

char id[30];

//subscribe
char up_channel[50];
char r_channel_df[50];
char r_channel_pat[50];
char r_channel_med[50];
char r_channel_rate[50];
char r_channel_version[50];
char r_channel_update[50];
char r_channel_staAck[50];
char r_channel_error[50];

const char* mqtt_channel_version = "dripo/%s/version";               ///request from server for current version
const char* mqtt_channel_update = "dripo/%s/update";                    /// request from server for update
const char* mqtt_channel_df = "dripo/%s/df";          /// to recieve df details
const char* mqtt_channel_pat = "dripo/%s/bed";                    /// to recieve patient list
const char* mqtt_channel_med = "dripo/%s/med";                    /// to recieve med list
const char* mqtt_channel_r2set = "dripo/%s/rate2set"; /// to recieve patient details
const char* mqtt_channel_staAck = "dripo/%s/staAck"; /// station ack
const char* mqtt_channel_error = "error/%s"; /// error channel

//publish
char pat_channel[50];
char version_channel[50];
char rate_channel[50];
char log_channel[50];
char will_msg[50];
char staAck_channel[50];
const char* mqtt_channel_myversion = "dripo/%s/myversion";                  ///to send current version
//const char* mqtt_channel_rate = "dripo/%s/rate";                  ///to send rate details
const char* mqtt_channel_req = "dripo/%s/req_df";                  ///to send df details
const char* mqtt_channel_bedreq = "dripo/%s/bed_req";                  ///to send bed details
const char* mqtt_channel_medreq = "dripo/%s/med_req";                  ///to send med details
const char* mqtt_channel_ratereq = "dripo/%s/rate_req";                  ///to send rate details
const char* mqtt_channel_mon = "dripo/%s/mon";                  ///to send start/stop details
const char* mqtt_channel_log = "dripo/%s/log";                  ///to send err details
const char* mqtt_channel_will = "dripo/%s/will";                  ///to send will msg
//const char* mqtt_channel_devack = "dripo/%s/ack_dev";
/// to publish dev ack

const int mqtt_port = 1883;
//char* mqtt_server = "192.168.0.13";
char mqtt_server[20] = "0";
char wifi_name[20] = "0";
char wifi_pass[20] = "0";
char hotspot_[3]  = "0";
//char static_ip[16] = "192.168.225.66";
//char static_gw[16] = "192.168.225.1";
//char static_sn[16] = "255.255.255.0";
//char mqtt_port[6] = "1883";
int R2set_eeprom;
int df_eeprom;
int tvol_eeprom;
char med_eep[25] ;
char timet_eep[25];
long dcount_eep;
WiFiClient wclient;  //Declares a WifiClient Object using ESP8266WiFi
PubSubClient mqttClient(wclient);

//ERR_HANDLER _errAlert(u8g2, mqttClient);

void setup() {

  Wire.begin(2, 0);
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  Serial.println("boot drip");

  EEPROM.begin(512);
  EEPROM.get(0, mqtt_server);

  EEPROM.get(40, df_eeprom);

  EEPROM.get(50, timet_eep);

  EEPROM.get(90, med_eep);

  EEPROM.get(130, tvol_eeprom);

  EEPROM.get(150, R2set_eeprom);

  EEPROM.get(180, dcount_eep);

  EEPROM.get(200, prev_inf);
  EEPROM.get(220, wifi_name);
  EEPROM.get(240, wifi_pass);
  EEPROM.get(270, hotspot_);

  EEPROM.end();


  stateOfCharge = batteryMonitor.getSoC();

  if (stateOfCharge < 5)
  {
    ui_state = 12;
    state = 15;
  }
  cellVoltage = batteryMonitor.getVCell();

  pinMode(ADC_PIN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(WAKE_PIN, OUTPUT);
  pinMode(IR_PIN, OUTPUT);
  pinMode(ENCODER_BTN, INPUT_PULLUP);
  pinMode(ENCODER_PINA, INPUT_PULLUP);
  pinMode(ENCODER_PINB, INPUT_PULLUP);
  pinMode(DROP_PIN, INPUT_PULLUP);
  analogWrite(WAKE_PIN, switchon);

  attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), checkButton, CHANGE);

  attachInterrupt(digitalPinToInterrupt(DROP_PIN), checkdrop, HIGH);

  attachInterrupt(ENCODER_PINA, encoder, RISING);
  attachInterrupt(ENCODER_PINB, encoder, RISING);
  //u8g2.begin();
  batteryMonitor.reset();
  batteryMonitor.quickStart();
  //ticker.attach(20, ticker_handler);
  ESP.wdtDisable();
  ESP.wdtEnable(WDTO_8S);
  u8g2.begin();

wifi_set_sleep_type(NONE_SLEEP_T);

  if (strcmp(hotspot_, "1") == 0) {

    const char* DRIPO_NAME = "DRIPO-%d";
    IPAddress local_IP(192, 168, 4, 1);
    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    sprintf(id, DRIPO_NAME, ESP.getChipId());
    WiFi.mode(WIFI_AP);           //Only Access point
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(id, "dripo1234");  //Start HOTspot removing password will disable security
    IPAddress myIP = WiFi.softAPIP(); //Get IP address
    Serial.print("HotSpt IP:");
    Serial.println(myIP);
    server = new ESP8266WebServer(80);
    server->on("/", handleRoot);      //Which routine to handle at root location
    server->on("/action", handleResponse);
    server->begin();                  //Start server
  }
  else {
    WiFi.mode(WIFI_STA);
     WiFi.begin(wifi_name, wifi_pass);
   // WiFi.begin("EVELABS_TECH", "BQQJUDWB");
  }
  analogWriteFreq(38000);

  dpf = MENU("Dpf", od_f, u8g2);
}


void (* myFunc[21])() = {drawLogo, wifi_init, menu_1, reset_menu, Server_Err, M_infuse, M_setup, M_pwroff, update_dripo, Sho_Rate, WifiConf, Sleep, M_Offline, Developer, ServErr, batlowoff, Infbatchk, Batchk, SensorCalib, OnOfselect, Wifi_Hotspot};
void (* UI_Fn[21])() = {UI_Logo, UI_Wifi, UI_Menu, UI_Rate, UI_infuse, UI_Update, UI_Shutdown, UI_Setup, UI_WifiConf, UI_reset, UI_dripo, UI_ServErr, UI_batlow, UI_InfBatChK, UI_batchk, UI_batfull, UI_Calib, UI_S_Err, Off_Infuse, UI_OnOf, UI_Hotspot};

void loop() {
  mqttClient.loop();
  //digitalWrite(WAKE_PIN, LOW);
  analogWrite(WAKE_PIN, switchon);
   myFunc[state]();
  u8g2.clearBuffer();
  UI_Fn[ui_state]();
  STBAR();
  u8g2.sendBuffer();
  yield();
  wifi_status =  wifi_connect(wifi_status);
  DataStatus = send_req(DataStatus);
  writeEprom = write_eprom(writeEprom);
  //to send infusion error via mqtt and return will be false
  sendmqtterrorMsgFlag = sendInfErr(sendmqtterrorMsgFlag,altmsg);
  //to send err Ack to server
  senderrAckFlag = sendErrAck(senderrAckFlag,altmsg);
  //call beep 
  beeperCount = beeper(beeperCount);
  yield();
  if (strcmp(hotspot_, "1") == 0) {
    server->handleClient();
  }
}




#include <FirebaseArduino.h>          //
#include <ESP8266WiFi.h>              //
//#define WIFI_SSID "Tuấn Thành"        //
//#define WIFI_PASSWORD "tuanthanh0"      //
////////////////////////////////////////
#include <OneWire.h>                  //
#include <DallasTemperature.h>        //
#define ONE_WIRE_BUS 13//D7             // Temp Module
OneWire oneWire(ONE_WIRE_BUS);        //
DallasTemperature sensors(&oneWire);  //
//////////////////////////////////////////////////////////////////////////
#include <NTPClient.h>                                                  //
#include <ESP8266WiFi.h>                                                //
#include <WiFiUdp.h>                                                    //  TIME
const long utcOffsetInSeconds = 25200;                                  //
WiFiUDP ntpUDP;                                                         //
NTPClient timeClient(ntpUDP, "vn.pool.ntp.org", utcOffsetInSeconds);    //
//////////////////////////////////////////////////////////////////////////
#include <BH1750.h>        //
BH1750 lightMeter;        /// Light Module
///////////////////////////////
#include "Arduino.h"         // Mở rộng Module
#include "PCF8574.h"         // https://github.com/xreef/PCF8574_library
PCF8574 pcf8574a(0x23);
PCF8574 pcf8574b(0x20);       //
///////////////////////////////
#include <Servo.h>
#define SERVO1_PIN 14//TX
Servo gServo1;
////////////////////////////////////////
#include <ESP8266HTTPClient.h>        // Local Server
#include <ESP8266WebServer.h>         //   
#include <EEPROM.h>                   // 
////////////////////////////////////////
#include <LinearRegression.h>
LinearRegression lr = LinearRegression();//
///////////////////////////////////////////
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int address = 200;

const int trig = 0;     // Pb2 khoang cach
const int echo = 2;     // Pb3 khoang cach
int in3 = 16;            // in4 motor Pb4


#define PinPurifier 6        //Pa4 Relay of Purifier
#define PinMotor 7        //Pa5 Relay of Feed
#define PinCooler 5       //Pa3 Relay of Cooler
#define PinLed 4          //Pa2

int in4 = 1;              //Pb5 in4 of Feed Motor
#define PinOxi 2          //Pa0 Relay of Oxi  
#define PinWarmer 3       //Pa1 Relay of Warmer

bool keyTemp = false;
bool keyTime = false;
bool checkPush = false;
bool checkSchedule = false;
int remainSchedule = 0;
bool firstTimeTraining = true;
bool checkConnection = false;
bool checkCurrentStatus = false;

String led_START;
String  led_STOP;
String oxi_START;
String oxi_STOP;
String purifier_START;
String purifier_STOP;
String feed_START;

int t = 0;

#include "WorkScheduler.h"   // TIMER
#include "Timer.h"
WorkScheduler *batsukien;
WorkScheduler *dieukhiennonglanh;
//WorkScheduler *baothucan;
WorkScheduler *guidulieu;
WorkScheduler *hengio;
WorkScheduler *trangthaihientai;
WorkScheduler *hienthi1;
WorkScheduler *hienthi2;


ESP8266WebServer server(80);
//Variables
int i = 0;
int statusCode;
const char* ssid = "Default_SSID";
const char* passphrase = "Default_Password";
String st;
String content;

void LCDPrint(int col, int row, String content) {
  lcd.setCursor(col, row);
  lcd.print(content);
}
void LCDClear1() {
  lcd.setCursor(0, 0);
  lcd.print("                    ");
}
void LCDClear2() {
  lcd.setCursor(0, 1);
  lcd.print("                    ");
}
void LCDClear() {
  lcd.clear();
}

void setup() {
  Serial.begin(9600);
  Serial.println("Chay roi alo alo alo");
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  LCDPrint(2, 0, "Welcome to");
  LCDPrint(1, 1, "SMART AQUARIUM");
  delay(2000);
  lcd.clear();
  Timer::getInstance()->initialize();

  batsukien =  new WorkScheduler(500UL, catchEvent);
  dieukhiennonglanh =  new WorkScheduler(2000UL, stopWarmerCooler);
  //baothucan =  new WorkScheduler(5000UL, getDistance); // tuc la notiFeed
  guidulieu =  new WorkScheduler(30000UL, trueTime);
  hengio =  new WorkScheduler(10000UL, doSchedule);
  trangthaihientai = new WorkScheduler(30000UL, currentStatus);
  hienthi1 = new WorkScheduler(10000UL, LCDStatus);
  hienthi2 = new WorkScheduler(30000UL, LCDTime);

  gServo1.attach(SERVO1_PIN);

  pcf8574b.pinMode(PinLed, OUTPUT);
  pcf8574b.pinMode(PinMotor, OUTPUT);
  pcf8574b.pinMode(PinCooler, OUTPUT);
  pcf8574b.pinMode(PinOxi, OUTPUT);
  pcf8574b.pinMode(PinWarmer, OUTPUT);
  pcf8574b.pinMode(PinPurifier, OUTPUT);

  //  pcf8574b.pinMode(in3, OUTPUT);
  //  pcf8574b.pinMode(in4, OUTPUT);
  pinMode(in3, OUTPUT);
  pcf8574b.pinMode(in4, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pcf8574a.begin();
  pcf8574b.begin();

  sensors.begin(); // temp module

  Wire.begin(); //
  lightMeter.begin(); // Light Module

  if (Outage() == true) {
    //servoOpen();
    gServo1.write(120);
    delay(1000);
    gServo1.detach();
    launchWeb();
    setupAP();
    LCDClear();
    LCDPrint(3, 0, "Outage!!!!");
    delay(2000);
    LCDClear1();
    LCDPrint(2, 0, "192.168.4.1");
    LCDPrint(3, 1, "Change Wifi");
    while ((WiFi.status() != WL_CONNECTED))
    {
      if (checkConnection == false) {
        Serial.println("Cho ket noi");
        Serial.print(".");
        delay(200);
        server.handleClient();
      }
      else {
        connectWifi();
        delay(100);
        if (testWifi() == true); {
          while ((WiFi.status() == WL_CONNECTED))
          {
            LCDClear();
            LCDPrint(1, 0, "WIFI Connected");
            LCDPrint(2, 1, "Plug & play");
            Serial.println("Da ket noi thanh cong, vui long cap nguon de su dung");
            delay(1000);
          }
        }
        checkConnection = false;
        LCDClear();
        LCDPrint(0, 0, "ConnectionFailed");
        LCDPrint(2, 1, "Try Again!!!");
        Serial.println("Wifi vua nhap khong dung");
      }
    }

  }
  //do nothing else
  else {
   // servoClose();
   gServo1.write(40);
   delay(1000);
   gServo1.detach();

    Serial.println("dong servo");
    WiFi.softAPdisconnect(true);
    //try connecting wifi until connected
    connectWifi();
    LCDClear1();
    while (WiFi.status() != WL_CONNECTED) {
      LCDPrint(0, 1, "...Connecting...");
      Serial.println("Try connecting wifi");
      WiFi.reconnect();
      delay(5000);
    }
  }

  Serial.println();
  Serial.print("connected: ");
  LCDClear();
  LCDPrint(1, 0, "SMART AQUARIUM");
  LCDPrint(1, 1, "WIFI Connected");


  Serial.println(WiFi.localIP());
  Firebase.begin("smartaqua-beb30.firebaseio.com");
 // keepControl();//dua ho ca ve trang thai gan nhat truoc khi mat dien
  Firebase.stream("/HoCa");
  delay(3000);
  LCDClear2();
}

void loop() {
 
  Timer::getInstance()->update();
  batsukien->update();
  dieukhiennonglanh->update();
  guidulieu->update();
  hengio->update();
  trangthaihientai->update();
  Timer::getInstance()->resetTick();
}

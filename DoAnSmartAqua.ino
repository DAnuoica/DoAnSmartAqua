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
PCF8574 pcf8574a(0x26);
PCF8574 pcf8574b(0x20);       //
///////////////////////////////
#include <Servo.h>

#define SERVO1_PIN 1  //TX
#define SERVO2_PIN 3  //RX
Servo gServo1;
Servo gServo2;
////////////////////////////////////////
#include <ESP8266HTTPClient.h>        // Local Server
#include <ESP8266WebServer.h>         //   
#include <EEPROM.h>                   // 
////////////////////////////////////////
#include <LinearRegression.h>
LinearRegression lr = LinearRegression();//
///////////////////////////////////////////

int address = 200;

const int trig = 2;     // Pb2 khoang cach
const int echo = 3;     // Pb3 khoang cach
int in3 = 4;            // in4 motor Pb4

#define PinPurifier 4        //Pa4 Relay of Purifier
#define PinMotor 5        //Pa5 Relay of Feed
#define PinCooler 3       //Pa3 Relay of Cooler
#define PinLed 2          //Pa2

int in4 = 5;              //Pb5 in4 of Feed Motor
#define PinOxi 0          //Pa0 Relay of Oxi  
#define PinWarmer 1       //Pa1 Relay of Warmer

bool keyTemp = false;
bool keyTime = false;
bool checkPush = false;
bool checkSchedule = false;
int remainSchedule = 0;
bool firstTimeTraining = true;
bool checkConnection = false;
bool currentStatus = false;

String led_START;
String  led_STOP;
String oxi_START;
String oxi_STOP;
String purifier_START;
String purifier_STOP;
String feed_START;


#include "WorkScheduler.h"   // TIMER
#include "Timer.h"
WorkScheduler *batsukien;
WorkScheduler *dieukhiennonglanh;
WorkScheduler *baothucan;
WorkScheduler *guidulieu;
WorkScheduler *hengio;
WorkScheduler *trangthaihientai;

ESP8266WebServer server(80);
//Variables
int i = 0;
int statusCode;
const char* ssid = "Default_SSID";
const char* passphrase = "Default_Password";
String st;
String content;


void setup() {
  Serial.begin(9600);
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pcf8574a.begin();
  pcf8574b.begin();
  Timer::getInstance()->initialize();

  batsukien =  new WorkScheduler(500UL, catchEvent);
  dieukhiennonglanh =  new WorkScheduler(2000UL, stopWarmerCooler);
  baothucan =  new WorkScheduler(5000UL, getDistance); // tuc la notiFeed
  guidulieu =  new WorkScheduler(30000UL, trueTime);
  hengio =  new WorkScheduler(10000UL, doSchedule);
  trangthaihientai = new WorkScheduler(3000UL, currentStatus);
    //********** CHANGE PIN FUNCTION  TO GPIO **********
  //GPIO 1 (TX) swap the pin to a GPIO.
  pinMode(1, FUNCTION_3);
  //GPIO 3 (RX) swap the pin to a GPIO.
  pinMode(3, FUNCTION_3);
  //**************************************************
    gServo1.attach(SERVO1_PIN);
    gServo2.attach(SERVO2_PIN);
    pcf8574a.pinMode(PinLed, OUTPUT);
    pcf8574a.pinMode(PinMotor, OUTPUT);
    pcf8574a.pinMode(PinCooler, OUTPUT);
    pcf8574a.pinMode(PinOxi, OUTPUT);
    pcf8574a.pinMode(PinWarmer, OUTPUT);
    pcf8574a.pinMode(PinPurifier, OUTPUT);
    
    pcf8574b.pinMode(in3, OUTPUT);
    pcf8574b.pinMode(in4, OUTPUT);
    pcf8574b.pinMode(trig, OUTPUT);
    pcf8574b.pinMode(echo, INPUT);
  

  sensors.begin(); // temp module

  Wire.begin(); //
  lightMeter.begin(); // Light Module


  if (Outage() == true) {
    //lift  servos
    servoOpen();
    //setup access point
    launchWeb();
    setupAP();
    while ((WiFi.status() != WL_CONNECTED))
    {
      if (checkConnection == false) {
        Serial.println("Cho ket noi");
        Serial.print(".");
        delay(100);
        server.handleClient();
      }
      else {
        connectWifi();
        delay(100);
        if (testWifi() == true); {
          while ((WiFi.status() == WL_CONNECTED))
          {
            Serial.println("Da ket noi thanh cong, vui long cap nguon de su dung");
            delay(1000);
          }
        }
        checkConnection = false;
        Serial.println("Wifi vua nhap khong dung");
      }
    }

  }
  //do nothing else
  else {
    //drop servos
    servoClose();
    Serial.println("dong servo");
    WiFi.softAPdisconnect(true);
    //try connecting wifi until connected
    connectWifi();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("Try connecting wifi");
      WiFi.reconnect();
      delay(10000);
    }
    //after connect again wifi (or initial connection), get all status from Firebase
    //reset firebase status
    //write retrieved status had been saved

    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    Firebase.begin("smartaqua-beb30.firebaseio.com");
//    keepControl();//dua ho ca ve trang thai gan nhat truoc khi mat dien
    Firebase.stream("/HoCa");
  }
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
//     pushData4Trainning();
//     Serial.println("Push data for training");
//     delay(5000);
//     training();
//     delay(10000);
//     pushData4Trainning();
//     Serial.println("Push data for training");
//     delay(5000);
//    training();
//    Serial.println(lr.calculate(35.0));
//    Serial.println(lr.calculate(27.0));
//    pushAPIForecast();
//
//    Serial.println("Xong");
//     delay(1000000);
    Timer::getInstance()->update();
    batsukien->update();
    dieukhiennonglanh->update();
   // baothucan->update();
    guidulieu->update();
    hengio->update();
    trangthaihientai->update();
    Timer::getInstance()->resetTick();
  }
}

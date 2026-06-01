/************ LIBRARIES ************/
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MPU6050.h>
#include <TinyGPSPlus.h>

/************ WIFI ************/
char ssid[] = "imo";
char pass[] = "12345678";

/************ TELEGRAM ************/
#define BOT_TOKEN "8782629932:AAEsjk8RqAwdcf-JBHsTXAhG9xcNsEccgEk"
#define CHAT_ID "5487353370"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

/************ GPS ************/
TinyGPSPlus gps;
HardwareSerial gpsSerial(1);

/************ OLED ************/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/************ TEMP ************/
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/************ PULSE ************/
#define PULSE_PIN 34
int pulseValue = 0;
int bpm = 0;
int beatCount = 0;
unsigned long lastBeatTime = 0;
unsigned long lastBpmCalc = 0;

/************ MPU ************/
MPU6050 mpu;
int16_t ax, ay, az;
float accel;

/************ BUTTONS ************/
#define EMERGENCY_BUTTON 12
#define RESET_BUTTON 14

/************ VARIABLES ************/
bool fallDetected = false;
bool buttonPressed = false;
bool alertSent = false;
float temperature = 0;

/************ GPS DATA ************/
String latitude = "0";
String longitude = "0";

/************ FALL ************/
bool fallStage1 = false;
unsigned long fallTime = 0;

/************ TIMERS ************/
unsigned long lastBotCheck = 0;
unsigned long lastSend = 0;

/************ GET LOCATION ************/
String getLocation() {
  if (gps.location.isValid()) {
    latitude = String(gps.location.lat(), 6);
    longitude = String(gps.location.lng(), 6);
  }
  return "https://maps.google.com/?q=" + latitude + "," + longitude;
}

/************ MESSAGE ************/
String getFullStatus(String title) {
  String msg = title + "\n";
  msg += "BPM: " + String(bpm) + "\n";
  msg += "Temp: " + String(temperature) + " C\n";
  msg += "Fall: " + String(fallDetected ? "YES" : "NO") + "\n";
  msg += "Button: " + String(buttonPressed ? "PRESSED" : "NORMAL") + "\n";
  msg += getLocation();
  return msg;
}

/************ TELEGRAM ************/
void handleNewMessages(int n) {
  for (int i = 0; i < n; i++) {
    String text = bot.messages[i].text;

    if (text == "/status") {
      bot.sendMessage(CHAT_ID, getFullStatus("STATUS"), "");
    }

    if (text == "/reset") {
      fallDetected = false;
      buttonPressed = false;
      alertSent = false;
      bot.sendMessage(CHAT_ID, "RESET DONE", "");
    }
  }
}

/************ SETUP ************/
void setup() {
  Serial.begin(115200);

  pinMode(EMERGENCY_BUTTON, INPUT_PULLUP);
  pinMode(RESET_BUTTON, INPUT_PULLUP);

  Wire.begin(21, 22);

  // OLED INIT
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  sensors.begin();
  mpu.initialize();

  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  WiFi.begin(ssid, pass);
  client.setInsecure();

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  bot.sendMessage(CHAT_ID, "SYSTEM STARTED", "");
}

/************ LOOP ************/
void loop() {

  /******** GPS ********/
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  /******** TELEGRAM ********/
  if (millis() - lastBotCheck > 2000) {
    int n = bot.getUpdates(bot.last_message_received + 1);
    while (n) {
      handleNewMessages(n);
      n = bot.getUpdates(bot.last_message_received + 1);
    }
    lastBotCheck = millis();
  }

  /******** BPM ********/
  pulseValue = analogRead(PULSE_PIN);

  if (pulseValue > 2000 && millis() - lastBeatTime > 300) {
    beatCount++;
    lastBeatTime = millis();
  }

  if (millis() - lastBpmCalc > 10000) {  // every 10 sec
    bpm = beatCount * 6;
    beatCount = 0;
    lastBpmCalc = millis();
  }

  /******** TEMP ********/
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  /******** MPU ********/
  mpu.getAcceleration(&ax, &ay, &az);
  accel = sqrt((ax/16384.0)*(ax/16384.0) +
               (ay/16384.0)*(ay/16384.0) +
               (az/16384.0)*(az/16384.0));

  /******** FALL ********/
  if (accel < 0.6) {
    fallStage1 = true;
    fallTime = millis();
  }

  if (fallStage1 && millis() - fallTime < 800) {
    if (accel > 2.2 && !alertSent) {
      fallDetected = true;
      buttonPressed = false;
      alertSent = true;

      bot.sendMessage(CHAT_ID, getFullStatus("FALL DETECTED"), "");
      fallStage1 = false;
    }
  }

  if (millis() - fallTime > 1200) fallStage1 = false;

  /******** BUTTON ********/
  if (digitalRead(EMERGENCY_BUTTON) == LOW && !alertSent) {
    buttonPressed = true;
    fallDetected = false;
    alertSent = true;

    bot.sendMessage(CHAT_ID, getFullStatus("EMERGENCY ALERT"), "");
    delay(300);
  }

  /******** RESET ********/
  if (digitalRead(RESET_BUTTON) == LOW) {
    fallDetected = false;
    buttonPressed = false;
    alertSent = false;

    bot.sendMessage(CHAT_ID, "RESET DONE", "");
    delay(300);
  }

  /******** OLED DISPLAY ********/
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("BPM: "); display.println(bpm);
  display.print("Temp: "); display.println(temperature);
  display.print("Fall: "); display.println(fallDetected ? "YES" : "NO");
  display.print("Btn: "); display.println(buttonPressed ? "YES" : "NO");
  display.display();

  /******** AUTO SEND ********/
  if (millis() - lastSend > 10000) {
    bot.sendMessage(CHAT_ID, getFullStatus("LIVE DATA"), "");
    lastSend = millis();
  }
}
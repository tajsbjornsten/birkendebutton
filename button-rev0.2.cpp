/*
MQTT Button with ESP-01 and OTA
*/
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <ArduinoOTA.h>


// Connect to the WiFi
const char* ssid = "**********";
const char* password = "*********";
const char* mqtt_server = "**********";
const char* mqtt_topic = "home"
const char* hostnameOTA = "ButtonSleepingRoom";
const char* hostnameWiFi = "ButtonSleepingRoom";
const char* hostnameMQTT = "ButtonSleepingRoom";


// this constant won't change:
const int buttonPin0 = 0;    // the pin that the pushbutton 0 is attached to
const int buttonPin1 = 1;    // the pin that the pushbutton 1 is attached to
const int buttonPin2 = 2;    // the pin that the pushbutton 2 is attached to
const int buttonPin3 = 3;    // the pin that the pushbutton 3 is attached to
// const int chartsPin = LED_BUILTIN;       // the pin that the LED is attached to

// Variables will change for button 0:
int buttonState0 = 0;         // current state of the button
int lastButtonState0 = 0;    // previous state of the button
// Variables will change for button 1:
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;    // previous state of the button
// Variables will change for button 2:
int buttonState2 = 0;         // current state of the button
int lastButtonState2 = 0;    // previous state of the button
// Variables will change for button 3:
int buttonState3 = 0;         // current state of the button
int lastButtonState3 = 0;    // previous state of the button
// Gobal Variables will change
// int buttonPushCounter = 0;   // counter for the number of button presses





WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Attempt to connect
    if (client.connect(hostnameMQTT)) {
    } else {
      // Wait 5 seconds before retrying
      delay(5000);
    }
  } 
}



void setup()
{
  {

    client.setServer(mqtt_server, 1883);


    // initialize the button pins as a input:
    pinMode(buttonPin0, INPUT_PULLUP);
    pinMode(buttonPin1, FUNCTION_3);
    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
    pinMode(buttonPin3, FUNCTION_3);
    pinMode(buttonPin3, INPUT_PULLUP);
    // initialize the LED as an output:

  }
  ArduinoOTA.setHostname(hostnameOTA);
  WiFi.hostname(hostnameWiFi);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
ArduinoOTA.begin();
}

void loop() {
ArduinoOTA.handle();
  /*
    Button 0 Begin --------------------------------------------------------
  */

  buttonState0 = digitalRead(buttonPin0);

  if (buttonState0 != lastButtonState0) {
    // if the state has changed, increment the counter
    if (buttonState0 == LOW) {
      client.publish("home/button/0", "on"); //
      // if the current state is HIGH then the button
      // went from off to on:
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      client.publish("home/button/0", "off"); //
    }
  }
  lastButtonState0 = buttonState0;
  /*
    Button 0 End --------------------------------------------------------
  */

  /*
    Button 1 Begin --------------------------------------------------------
  */

  buttonState1 = digitalRead(buttonPin1);

  if (buttonState1 != lastButtonState1) {
    // if the state has changed, increment the counter
    if (buttonState1 == LOW) {
      client.publish("home/button/1", "on"); //
      // if the current state is HIGH then the button
      // went from off to on:
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      client.publish("home/button/1", "off"); //
    }
  }
  lastButtonState1 = buttonState1;

  /*
    Button 1 End --------------------------------------------------------
  */
  /*
    Button 2 Begin --------------------------------------------------------
  */

  buttonState2 = digitalRead(buttonPin2);

  if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
    if (buttonState2 == LOW) {
      client.publish("home/button/2", "on"); //
      // if the current state is HIGH then the button
      // went from off to on:
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      client.publish("home/button/2", "off"); //
    }
  }
  lastButtonState2 = buttonState2;
  /*
    Button 2 End --------------------------------------------------------
  */
  /*
    Button 3 Begin --------------------------------------------------------
  */
  
  buttonState3 = digitalRead(buttonPin3);
  if (buttonState3 != lastButtonState3) {
    // if the state has changed, increment the counter
    if (buttonState3 == LOW) {
      client.publish("home/button/3", "on"); //
      // if the current state is HIGH then the button
      // went from off to on:
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      client.publish("home/button/3", "off"); //
    }
  }
  lastButtonState3 = buttonState3;
  /*
    Button 3 End --------------------------------------------------------
  */
  //
  // Delay a little bit to avoid bouncing
  delay(50);
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
}

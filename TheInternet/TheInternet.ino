#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "FastLED.h"

// e' Wemos !!!
// led ws2801

// Credenziali WiFi

//char ssid[] = "ArduinoAfternoon";
//char pass[] = "lavagnamit";

char ssid[] = "GuestMFR16";

//char ssid[] = "fastweb-rm-cpe-bblaf-1";
//char pass[] = "bbstoccolma";

//int status = WL_IDLE_STATUS;
WiFiClient client;


// LEDs
#define NUM_LEDS 5

CRGB leds[]= {
    CRGB::Red,
    CRGB::Blue,
    CRGB::Orange,
    CRGB::Purple,
    CRGB::Green
};

const char* hosts[]= {
    "google.com",
    "facebook.com",
    "ebay.com",
    "twitter.com",
    "unimi.it"
};

//long times[]= {0,0,0,0,0};

#define UPPERBOUND 10000
unsigned long min=UPPERBOUND, max=0;

#define LED_DATA_PIN D2
#define LED_CLOCK_PIN D3

#define LED_DELAY_ON 100
#define LED_DELAY_OFF 20

#define MINREPEAT 5
#define MAXREPEAT 40

#define DELAYHOSTS 500

#define DELAYFLASH 100

// This function sets up the ledsand tells the controller about them
void setup() {
    //pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);

    FastLED.addLeds<WS2801, LED_DATA_PIN, LED_CLOCK_PIN, BGR>(leds, NUM_LEDS);
    leds[0]=CRGB::Red;
    FastLED.show();

    //connectWifi();

}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {

    flashAll(DELAYFLASH,CRGB::White);

    for(int count=0; count<NUM_LEDS; count++)
    {
        //flashLed(count);
        //Serial.println("flashing");

        Serial.print("host: ");
        Serial.println(hosts[count]);
        int time=timer(count);
        Serial.print("time: ");
        Serial.println(time);

        if(time > max) max = time;
        if(max > UPPERBOUND) max = min+1;

        if(time>=0 && time < min) min = time;

        Serial.print("min: ");
        Serial.print(min);
        Serial.print(", max: ");
        Serial.println(max);

        //Serial.println(time);
        flashLed(count,time);
        delay(DELAYHOSTS);
    }

    //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

    //delay(1000);
}


void flashAll(int del,CRGB color) {
    for(int pos=0; pos<NUM_LEDS; pos++) {
        CRGB saved=leds[pos];
        leds[pos]=color;
        FastLED.show();
        delay(del);
        leds[pos]=saved;
        FastLED.show();
    }

}

void flashLed(short pos, int time) {
    if(time>=min && time<=max) {
        CRGB saved=leds[pos];

        Serial.print("mapping...");
        int repeat= map(time,min,max,MINREPEAT,MAXREPEAT);
        Serial.print("repeat: ");
        Serial.print(repeat);

        for(unsigned long count=0; count<repeat; count++)
        {
            leds[pos]=CRGB::Black;
            FastLED.show();
            delay(LED_DELAY_OFF);
            leds[pos]=saved;
            FastLED.show();
            delay(LED_DELAY_ON);
        }
    }
}


void printWifiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}



void connectWifi() {
// attempt to connect to Wifi network:
    //Serial.println(status);
    //while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid);
    //WiFi.begin(ssid, pass);

    //Serial.println(status);
    //printWifiStatus();

    // wait 5 seconds for connection:
    //delay(5000);
    //}
    Serial.println("Connected to wifi");
    printWifiStatus();
}





int timer(short host) {

    if(WiFi.status()==WL_CONNECTED) {
        //printWifiStatus();

        unsigned long time=millis();

        Serial.println("\nStarting connection to server...");
        // if you get a connection, report back via serial:
        if (client.connect(hosts[host], 80)) {
            Serial.print("connected to server: ");
            Serial.println(hosts[host]);
            // Make a HTTP request:
            client.println("GET / HTTP/1.1");
            //client.println("Host: www.google.com");
            client.println();
            client.println();
            /*
            while (client.available()>0) {
                char c = client.read();
                Serial.write(c);
            }
            */
            //client.println("Connection: close");
            client.stop();
            return int(millis()-time);
        }
    } else {
        Serial.println("disconnected!!!");
        connectWifi();
        printWifiStatus();
    }
    return -1;
}

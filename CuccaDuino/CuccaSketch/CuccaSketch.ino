/*
 * ci sono Task:
 * - senza stato (ogni volta che eseguono disegnano qualcosa ex novo dove serve, senza ridisegnare alcunche' di precedente)
 * - con stato (ogni volta che eseguono disegnano il nuovo ma anche ripristinano la vecchia "memoria video")
 */

// DONE lettura seriale

// DONE interazione webclient
// rispondere ad un url (via HTTP GET)
// TODO facciamo una wiki page che permette di compilare un form che poi scatena la GET
// TODO preparare QR code della pagina wiki

// provare: wget -O - 192.168.90.23/ciao

// TODO LCD display carattere corrente (3 PIN)

// ( random pattern )

// TODO display testo human-leggibile

// TODO read sensori (PIR, ultrasuono, infrarosso, microfono, termometro-igrometro)
// Temperatura, umidita e ora/data (tutto in binario) quando in stand-by
// LED in serie (normali)

// "esci" status da qualche parte

// modulo rete (4 PIN)

////////////////////////////////
//#include <MD_Parola.h>
//#include <MD_Parola_lib.h>
#include <SPI.h>
#include <Ethernet.h>
// LED
#include "FastLED.h"

EthernetServer server(80);
EthernetClient client;
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x22, 0xD7 };
const char url[] = "www.unimi.it";

////////////////////////////////
#define NUMDISPLAYS    8
#define LEDS_PER_DISPLAY    8
#define TOTLEDS    NUMDISPLAYS*LEDS_PER_DISPLAY

#define DELAY    10

#define ANTENNA    A0

// Data pin that led data will be written out over
#define DATA_PIN 2
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define CLOCK_PIN 3

// NUM LED
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];

////////////////////////////////
// globals
//int car=0;
//int current=-1;
//int currentForClock=0;

////////////////////////////////
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 7 is connected to the DataIn
 pin 6 is connected to the CLK
 pin 5 is connected to LOAD
 We have only a single MAX72XX.
 */
#include "LedControl.h"
LedControl lc=LedControl(7,6,5,NUMDISPLAYS);

#include <TaskScheduler.h>
Scheduler runner;

// "cardiogramma"
short cursor=0;

////////////////////////////////////////
// Task callback methods prototypes
void readSerial_callback();
void readTime_callback();
//void readtemp_callback();
//void showstatus_callback();
void readTextFromSocketClient_callback();
void animateLeds_callback();
void cardio_callback();

////////////////////////////////////////
// Tasks
Task readSerial(100, TASK_FOREVER, &readSerial_callback);
Task animateLeds(30000, TASK_FOREVER, &animateLeds_callback);
Task readTime(5000, TASK_FOREVER, &readTime_callback);
Task readTextFromSocketClient(500, TASK_FOREVER, &readTextFromSocketClient_callback);
Task cardio(50, TASK_FOREVER, &cardio_callback);
/*
Task readtemp(..., TASK_FOREVER, &readtemp_callback);
Task showstatus(..., TASK_FOREVER, &showstatus_callback);
*/

/** per non sfondare coordinate */
short X(short x) {
    if(x>TOTLEDS) return 0;
    return x;
}

short arrotondaPotenza2(int v) {
//v--;
v |= v >> 1;
v |= v >> 2;
v |= v >> 4;
v |= v >> 8;
//v |= v >> 16;

//if (v == -1){
//	v++;
//}

//...    if(y>pow(2,LEDS_PER_DISPLAY)) return 0;

    return v;
}


/**
 legge da seriale e ... (butta fuori il binario)
*/
void readSerial_callback() {
    short pos=0;
    // memo: serial buffer 64 bytes
    while(Serial.available()>0) {
        char r=Serial.read();

        /*
                if(current>=NUMDISPLAYS*LEDS_PER_DISPLAY) {
                    current=0;
                }
        */
        enlighten(pos,r);    // sara' da togliere se no ci rompe le scatole qando facciamo animazioni varie
        pos++;
    }
}

/**
 cardio saltellante
*/
void cardio_callback() {
	int letto=arrotondaPotenza2(analogRead(ANTENNA)/8);

    Serial.print(F("Sin:"));
    Serial.print(letto);
    Serial.print(F(" - Pos:"));
    Serial.println(cursor);

    enlighten(cursor,letto);
    cursor=X(++cursor);
}

// TODO: DA DIVIDERE ???????
/** vede se c'e' client, lo gestisce e setta lo "stato"
*/
void readTime_callback() {
    // if you get a connection, report back via serial:
    if (client.connect(url, 80)) {
        clearDisplays();
        Serial.println(F("connected"));
        // Make a HTTP request:
        client.println(F("GET / HTTP/1.1"));
        client.println(F("Host: pippo.com"));
        client.println(F("Connection: close"));
        client.println();
        client.println();
    }
    else {
        // if you didn't get a connection to the server:
        Serial.println(F("connection failed"));
    }

    delay(100);

    int nl=0,sp=0,pos=0;

    //Serial.println(currentForClock);

    while (client.available()) {
        char c = client.read();


        if(c=='\n') nl++;
        if(c==' ') sp++;

        if(nl==1 && sp>6 && sp<8 && c!=' ') {
            enlighten(pos++,c);
            //if(currentForClock >= TOTLEDS) currentForClock=0;
            Serial.print(c);
        }

        if(nl==2) break;

    }
    client.stop();
}




/** Mette a display quello che viene scritto
*/
void readTextFromSocketClient_callback() {

    // listen for incoming clients
    EthernetClient client = server.available();
    if (client) {
        Serial.print(F("new client: "));
        Serial.println(client);
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        if(client.connected()) {
            char r='\0';
            //int counterClient=0;
            String fromClient;
            //char fromClient[64];
            short pos=0;

            // salta fino a "GET /"
            while(client.available()) {
                if(client.read()=='/') break;
            }


            // prende da "/" escluso a fine riga (HTTP/1.1\n)
            while(client.available()) {
                r=client.read();
                if(r=='/') break;
                //r  == > fromClient
                //fromClient[counterClient++]=r;
                fromClient+=r;
                Serial.write(r);
                client.write(r);
                //enlighten(pos++,r);
            }


            fromClient.remove(fromClient.lastIndexOf(F(" HTTP")));
            if(fromClient.indexOf(F("favicon.ico"))==-1 ) enlighten(fromClient);

            Serial.println();
            Serial.println(F("finito"));
            Serial.println();

            // svuota il resto
            while(client.available()) {
                r = client.read();
                Serial.write(r);
            }

            // give the web browser time to receive the data
            delay(100);
            // close the connection:
            client.stop();
            Serial.println(F("client disconnected"));
        }
    }
}


/** legge temperatura, ora, data, umidita'  e aggiorna lo "stato"
void readtemp_callback() {
    // ...
}
*/

/** Legge lo "stato" e lo spara su display
void showstatus_callback() {
    // ...
}
*/

/** Animazione con dei LED
TODO: pensare ad animazione piu' intelligente
*/
void animateLeds_callback() {
//animazione ad cazzum
    for(int i=0; i<TOTLEDS; i++) {
        enlighten(i,8*sin(i));
    }
    clearDisplays();
}


void clearDisplays() {
    /*
     The MAX72XX is in power-saving mode on startup,
     we have to do a wakeup call
     */
    for (int d=0; d<NUMDISPLAYS; d++) {
        lc.shutdown(d,false);
        /* Set the brightness to a medium values */
        lc.setIntensity(d,8);
        /* and clear the display */
        lc.clearDisplay(d);
    }
}

void setup() {
    // serial
    Serial.begin(115200);
    
    // pins
    pinMode(ANTENNA,INPUT);

    // rete
    Ethernet.begin(mac);
    server.begin();
    Serial.print(F("server is at "));
    Serial.println(Ethernet.localIP());
    delay(1000);

    // pulisce leds
    clearDisplays();

    // attiva runner
    runner.init();
    Serial.println(F("Initialized scheduler"));

    // da seriale a led
    runner.addTask(readSerial);
    Serial.println(F("added readSerial task"));
    readSerial.enable();
    Serial.println(F("enabled readSerial task"));

    // legge time e visualizza
    /*
    runner.addTask(readTime);
    Serial.println(F("added readTime"));
    readTime.enable();
    Serial.println(F("enabled readTime"));
    */

    runner.addTask(cardio);
    Serial.println(F("added cardio"));
    cardio.enable();
    Serial.println(F("enabled cardio"));

    // da socket (GET) a leds
    runner.addTask(readTextFromSocketClient);
    Serial.println(F("added readTextFromSocketClient"));
    readTextFromSocketClient.enable();
    Serial.println(F("enabled readTextFromSocketClient"));

    // animate leds
    /*
    runner.addTask(animateLeds);
    Serial.println(F("added animateLeds"));
    animateLeds.enable();
    Serial.println(F("enabled animateLeds"));
    */
    
	FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
}

/*
// Memo esistenza setLed

void pixel(int d) {
    for(int row=0; row<8; row++) {
        for(int col=0; col<8; col++) {
            delay(DELAY);
            lc.setLed(d,row,col,true);
        }
    }
}
*/

/**
	enlightens the 'position' position (with ASCII, in binary)
*/
void enlighten(int position, char car) {

    int display=position/NUMDISPLAYS;
    int internal_position=(LEDS_PER_DISPLAY-1)-(position%NUMDISPLAYS);

    // TODO check limiti

    /*  Serial.print("display: ");
        Serial.print(display);
        Serial.print(", ");
        Serial.print("internal_position: ");
        Serial.print(internal_position);
        Serial.print(", ");
        Serial.print("char: ");
        Serial.println(car);    */

    // decidere altri effetti?
    lc.setColumn(display,internal_position,0);
    delay(DELAY);
    lc.setColumn(display,internal_position,car);
}

/**
	enlightens the 'position' position (with ASCII, in binary)
*/
void enlighten(String str) {
    clearDisplays();
    for(int pos=0; pos<(str.length()); pos++) {
        enlighten(pos,str.charAt(pos));
    }
}

void loop() {
    runner.execute(); // questo sara' l'unica voce del loop

	leds[0] = CHSV(255,100,100); 
   leds[1] = CRGB(0,255,0);
   leds[2] = CRGB(0, 0, 255);
   leds[3] = CRGB(100,100,100);
   leds[4] = CRGB(255,255,255);
   FastLED.show();
    //Serial.print("position: ");
    //Serial.println(current);

    //delay(DELAY);
}

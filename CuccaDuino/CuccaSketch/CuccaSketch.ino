// (lettura seriale)

// interazione webclient
// rispondere ad un url (via HTTP GET)
// facciamo una wiki page che permette di compilare un form che poi scatena la GET
// preparare QR code della pagina wiki

// display carattere corrente (3 PIN)

// ( random pattern )

// display testo human-leggibile

// read sensori (PIR, ultrasuono, infrarosso, microfono, termometro-igrometro)
// Temperatura, umidita e ora/data (tutto in binario) quando in stand-by
// LED in serie (normali)

// "esci" status da qualche parte

// modulo rete (4 PIN)

// TODO: includere rete

////////////////////////////////
#include <SPI.h>
#include <Ethernet.h>
EthernetClient client;
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x22, 0xD7 };
const char server[] = "www.unimi.it";


////////////////////////////////
#define NUMDISPLAYS    8
#define LEDS_PER_DISPLAY    8
#define TOTLEDS    NUMDISPLAYS*LEDS_PER_DISPLAY

#define DELAY    10

////////////////////////////////
// globals
int car=0;
int current=-1;
int currentForClock=0;

////////////////////////////////
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 We have only a single MAX72XX.
 */
#include "LedControl.h"
LedControl lc=LedControl(7,6,5,NUMDISPLAYS);

#include <TaskScheduler.h>
Scheduler runner;


// Callback methods prototypes
void readserial_callback();
void web_callback();
void readtemp_callback();
void showstatus_callback();
void showtext_callback();
void animateleds_callback();

//Tasks
Task readserial(100, TASK_FOREVER, &readserial_callback);
Task animateleds(30000, TASK_FOREVER, &animateleds_callback);
Task web(10000, TASK_FOREVER, &web_callback);
/*
Task readtemp(..., TASK_FOREVER, &readtemp_callback);
Task showstatus(..., TASK_FOREVER, &showstatus_callback);
Task showtext(..., TASK_FOREVER, &showtext_callback);
*/

/**
 legge da seriale e ... (non sappiamo ancora)
*/
void readserial_callback() {
    // memo: serial buffer 64 bytes
    if(Serial.available()>0) {
        car=Serial.read();
        current++;

        if(current>=NUMDISPLAYS*LEDS_PER_DISPLAY) {
            current=0;
        }
    }
    enlighten(current,car);    // sara' da togliere se no ci rompe le scatole qando facciamo animazioni varie
}

// TODO: DA DIVIDERE ???????
/** vede se c'e' client, lo gestisce e setta lo "stato"
*/
void web_callback() {
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
		clearDisplays();
        Serial.println("connected");
        // Make a HTTP request:
        client.println(F("GET / HTTP/1.1"));
        client.println(F("Host: pippo.com"));
        client.println(F("Connection: close"));
        client.println();
        client.println();
    }
    else {
        // if you didn't get a connection to the server:
        Serial.println("connection failed");
    }

    delay(100);

    int nl=0,sp=0;

        Serial.println(currentForClock);

    while (client.available()) {
        char c = client.read();


        if(c=='\n') nl++;
        if(c==' ') sp++;
        
        if(nl==1 && sp>6 && sp<8 && c!=' ') {
            enlighten(currentForClock++,c);
            if(currentForClock >= TOTLEDS) currentForClock=0;
            Serial.print(c);
        }
        
        if(nl==2) break;

    }
    client.stop();
}
/** Mette a display quello che viene scritto
*/
void showtext_callback() {
    // ...
}


/** legge temperatura, ora, data, umidita'  e aggiorna lo "stato"
*/
void readtemp_callback() {
    // ...
}

/** Legge lo "stato" e lo spara su display
*/
void showstatus_callback() {
    // ...
}

/** Animazione con dei LED
TODO: pensare ad animazione piu' intelligente
*/
void animateleds_callback() {
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

    // rete
    Ethernet.begin(mac);
    Serial.println(Ethernet.localIP());
    delay(1000);

    clearDisplays();

    // RUNNER TASK
    runner.init();
    Serial.println(F("Initialized scheduler"));

    runner.addTask(readserial);
    Serial.println(F("added readserial task"));

    runner.addTask(web);
    Serial.println(F("added web"));

//    runner.addTask(readtemp);
//    Serial.println(F("added readtemp"));

//    runner.addTask(showstatus);
//    Serial.println(F("added showstatus"));

//    runner.addTask(showtext);
//    Serial.println(F("added showtext"));

    /*
        runner.addTask(animateleds);
        Serial.println(F("added animateleds"));
    */

////// ENABLE TASK

    readserial.enable();
    Serial.println(F("enabled readserial task"));

    /*
    animateleds.enable();
    Serial.println(F("enabled animateleds"));
    */

    web.enable();
    Serial.println(F("enabled web"));

    /*

      //  readtemp.enable();
        Serial.println(F("enabled readtemp"));

      //  showstatus.enable();
        Serial.println(F("enabled showstatus"));

      //  showtext.enable();
        Serial.println(F("enabled showtext"));

    */

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

    // check limiti

    /*
        Serial.print("display: ");
        Serial.print(display);
        Serial.print(", ");
        Serial.print("internal_position: ");
        Serial.print(internal_position);
        Serial.print(", ");
        Serial.print("char: ");
        Serial.println(car);
        */

    // decidere altri effetti?
    lc.setColumn(display,internal_position,0);
    delay(DELAY);
    lc.setColumn(display,internal_position,car);
}

void loop() {
    runner.execute(); // questo sara' l'unica voce del loop

    //Serial.print("position: ");
    //Serial.println(current);

    //delay(DELAY);
}

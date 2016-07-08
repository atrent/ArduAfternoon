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

#define NUMDISPLAYS    8
#define LEDS_PER_DISPLAY    8

#define DELAY    10

////////////////////////////////
// globals
int car=0;
int current=-1;
////////////////////////////////


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
LedControl lc=LedControl(12,11,10,NUMDISPLAYS);

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
/**
Task readserial(..., TASK_FOREVER, &readserial_callback);
Task web(..., TASK_FOREVER, &web_callback);
Task readtemp(..., TASK_FOREVER, &readtemp_callback);
Task showstatus(..., TASK_FOREVER, &showstatus_callback);
Task showtext(..., TASK_FOREVER, &showtext_callback);
Task animateleds(..., TASK_FOREVER, &animateleds_callback);
*/

/**
 legge da seriale e ... (non sappiamo ancora)
*/
void readserial_callback() {
	// ...
}

// TODO: DA DIVIDERE ???????
/** vede se c'e' client, lo gestisce e setta lo "stato"
*/
void web_callback() {
	// ...
}
/** Mette a display quello che viene scritto
*/
void showtext_callback(){
	// ...
}


/** legge temperatura, ora, data, umidita'  e aggiorna lo "stato"
*/
void readtemp_callback(){
	// ...
}

/** Legge lo "stato" e lo spara su display
*/
void showstatus_callback(){
	// ...
}

/** Animazione con dei LED
*/
void animateleds_callback(){
	// ...
}

void setup() {
    Serial.begin(115200);
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
    
    runner.init();
    Serial.println("Initialized scheduler");

//    runner.addTask(t1);
    Serial.println("added t1");

//    runner.addTask(t2);
    Serial.println("added t2");
    
//    runner.addTask(t3);
    Serial.println("added t3");

//    t1.enable();
    Serial.println("Enabled t1");
  //  t2.enable();
    Serial.println("Enabled t2");
  //  t3.enable();
    Serial.println("Enabled t3");

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
    //runner.execute(); // questo sara' l'unica voce del loop


    //Serial.print("position: ");
    //Serial.println(current);

    // memo: serial buffer 64 bytes
    if(Serial.available()>0) {
        car=Serial.read();
        current++;

        if(current>=NUMDISPLAYS*LEDS_PER_DISPLAY) {
            current=0;
        }
    }
    
    enlighten(current,car);
    
    //delay(DELAY);
}

/*
HARDWARE NOTES:
 Timer0 millis(),delay(),micros()
 Timer1 ServoTimer1
 Timer2 tone(), NewPing
*/

#include <Arduino.h>

#include <NewPing.h>      // Timer2
#include <Servo.h>        // Timer1 hw servo 

#define TRIGGER_PIN  7    // arduino trigger pin 12 ultrasonic sensor.
#define ECHO_PIN     6    // arduino echo    pin 11 ultrasonic sensor.
#define MAX_DISTANCE 300  // Maximum distance to measure.
// Maximum sensor distance is rated at 400-500cm.
#define SR04_1ServoPin 9  // SR04 sensor1 servo pin
#define RGBLedRedPin 2
#define RGBLedGreenPin 3
#define SWEEPDELAY 100

//LedControl Displ7Seg1=LedControl(12,11,10,1); // 12-Data, 11-CLK, 10-Load, 1-1module
Servo SR04_1Servo;        // create servo object to control a servo
// twelve servo objects can be created on most boards

NewPing SR04_1(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);     // NewPing setup of pins and maximum distance.


int dirChange=0;
int          SR04Servo1_Step = -1;         // variable to store/change SR04_1 servo step and direction
unsigned int SR04_1ServoLeftLimit = 140;  // variable to CALIBRATE sweep angle
unsigned int SR04_1ServoRightLimit = 40;  // variable to CALIBRATE sweep angle
unsigned int SR04Servo1_Pos = SR04_1ServoLeftLimit;         // variable to store the servo position
//boolean      SR04_1SweepDone;           // variable to remember if a HALF sweep cicle is done

const unsigned int TERMWIDTH = 200 ;
const unsigned int TERMHEIGHT = 60 ;
const unsigned int XCENTER = TERMWIDTH / 2 ;
const unsigned int YCENTER = TERMHEIGHT ;

const boolean DEBUG = false;
const boolean DEBUGVAL = false;
const char CURSOR = '+';


//boolean Calibrate = false ;
//unsigned int SerialInData ;

void setup() {

    Serial.begin(115200);                   // Open serial monitor at 115200 baud
    SR04_1Servo.attach(SR04_1ServoPin);     // initialize SR04 sensor1 servo driver
    pinMode(LED_BUILTIN,OUTPUT);            // initialize arduino internal LED port

    /*
    pinMode(RGBLedRedPin,OUTPUT);
      pinMode(RGBLedGreenPin,OUTPUT);         // RGB led
      Displ7Seg1.shutdown(0,false);      // Displ7seg1 initialization
      Displ7Seg1.setIntensity(0,8);       // Set the brightness to a medium values
      Displ7Seg1.clearDisplay(0);         // and clear the display
      SR04_1Servo.write(SR04Servo1_Pos);   // tell servo driver to go in position
      */
    clearScreen();
}

// tentativo con multilettura e media
/*
float avgPing(){
	float avg;
	for(int readCount=0;readCount<3;readCount++){
		avg=SR04_1.ping();       // Send ping, get ping time in microseconds (us)
		delay(10);
		avg+=SR04_1.ping();
		avg=avg/2;
	}
    return sqrt(avg);
    //int toBplotted=map(us,0,10000,0,TERMHEIGHT);
}
*/


void loop() {
	if(Serial.available()){
		char command=Serial.read();
		switch(command){
			case 'm': // motor off
			...
			break;
			case 'M': // motor on
			...
			break;
			case 'c': // set to middle
			...
			break;
		}
	}

    //if (Serial.available() > 0) calibration();  // enter calibration mode

    //SR04_1Servo.write(SR04Servo1_Pos);     // tell servo to go to position in variable 'pos'
    //delay(SWEEPDELAY);

    //SR04_1Servo.write(95);
    
    //int toBplotted=sqrt(SR04_1.ping());
    int toBplotted=map(sqrt(SR04_1.ping()),0,100,0,TERMHEIGHT-5);

    //plot_ncurses(SR04Servo1_Pos,30);Serial.print(toBplotted);
    plot_ncurses(SR04Servo1_Pos,toBplotted,CURSOR);

	// riferimento
    plot_ncurses(SR04Servo1_Pos,TERMHEIGHT-10,'.');

    cursorAt(0,TERMHEIGHT);
    /*
    Serial.print("ping=");
    Serial.print(us);
    Serial.print("us, angolo=");
    */
    Serial.print("angolo=");
    Serial.print(SR04Servo1_Pos);
    Serial.print(", toBplotted=");
    Serial.print(toBplotted);
    Serial.print("     ");

    //Serial.println(plot(SR04Servo1_Pos,1));
    //Serial.println("***************");


    /*
    for (int ang=0; ang<=180; ang+=5) {
        plot(ang,30);

        //Serial.print("angolo=");
        //Serial.print(ang);
        //Serial.print(", base=");
        //Serial.print(base(ang,10));
        //Serial.print(", altezza=");
        //Serial.print(altezza(ang,10));
        //Serial.println();

        //Serial.print(", altezza=");
        //Serial.print(altezza(ang,10));
        //Serial.println();

        //plot(ang,maxScreenRange());

        delay(200);
    }
    */

    SR04Servo1_Pos = SR04Servo1_Pos + SR04Servo1_Step;
    delay(SWEEPDELAY);
    
    if (SR04Servo1_Pos <= SR04_1ServoRightLimit ) {
		SR04Servo1_Pos = SR04_1ServoLeftLimit;
		clearScreen();
	}

    /*
    if (SR04Servo1_Pos <= SR04_1ServoRightLimit || SR04Servo1_Pos >= SR04_1ServoLeftLimit) {
        SR04Servo1_Step = -SR04Servo1_Step;       // switch servo direction
        dirChange++;
        //if (Serial.available() > 0) calibration();  // enter calibration mode

        // clear screen, every 2 dirchanges
        if(dirChange%2==0)clearScreen();
    }
    */

}     // main loop brace!!


void clearScreen() {
    Serial.write(27);
    Serial.write("[2J");
}

void plot(int angolo, int distanza) {
    if(DEBUG) plotDebug(angolo,distanza);
    else
        plot_ncurses(angolo,distanza,CURSOR);
}

void cursorAt(int x, int y) {

    // check sbordo
    if(x>TERMWIDTH) x=TERMWIDTH;
    if(x<0) x=0;
    if(y>TERMHEIGHT) y=TERMHEIGHT;
    if(y<0) y=0;

    // invio codici term
    Serial.write(27);
    Serial.write('[');
    Serial.print(y);
    Serial.write(';');
    Serial.print(x);
    Serial.write('H');
}

void plot_ncurses(int angolo, int distanza,char cursor) {
    if(distanza==0) return;

    cursorAt(base(angolo,distanza),altezza(angolo,distanza));

    if(DEBUGVAL) {
        Serial.print("(");
        Serial.print(angolo);
        Serial.print(",");
        Serial.print(distanza);
        Serial.print(")");
    }
    else {
        Serial.print(cursor);
    }
}

void plotDebug(int angolo, int distanza) {
    Serial.print("base: ");
    Serial.print(base(angolo,distanza));
    Serial.print(", altezza : ");
    Serial.println(altezza(angolo,distanza));
}



float radianti(int angolo) {
    return (angolo / 360.0) * 2 * 3.14;
}

int base(int angolo, int distanza) {
    return int(XCENTER + (distanza * cos(radianti(angolo))));
}

int altezza(int angolo, int distanza) {
    return int(YCENTER - (distanza * sin(radianti(angolo))));
}

unsigned int maxScreenRange() {
    return min(XCENTER,YCENTER) ;
}

/*
void calibration() {
while (Serial.available()>0) SerialInData = Serial.read(); // empty buffer
Serial.print("CALIBRATION:  1-Servo, 2-Sens. Range, 9-Exit  Value? : ");
while (Serial.available()==0) delay(10); // wait for input
SerialInData = Serial.read();
Serial.println((int)SerialInData);  // xke typecast?
switch (SerialInData) { // which calibration?
  case '1': // Servo calibration options
    Serial.print("SERVO CAL:  1-Center, 2-Left, 3-Right, 9-Exit  ");
    while (Serial.available()==0) delay(10); // wait for input
    SerialInData = Serial.read();
    switch (SerialInData) {
      case '1':
      { unsigned int SR04_1ServoCent=(SR04_1ServoLeftLimit-SR04_1ServoRightLimit)/2;
      Serial.print("Center Value:  ");
      Serial.println(SR04_1ServoCent);
      SR04_1Servo.write(SR04_1ServoCent); }
      while (Serial.available()>0) SerialInData=Serial.read();
      Serial.print("done, press Enter to recalibrate");
      while (Serial.available()==0) delay(10); // wait for input
      SerialInData=Serial.read();
      //calibrate();
      break;
      case '2':
      Serial.print("Left limit Val:  ");
      Serial.println(SR04_1ServoLeftLimit);
      SR04_1Servo.write(SR04_1ServoLeftLimit);
      break;
      case '3':
      Serial.print("Right limit Val:  ");
      Serial.println(SR04_1ServoLeftLimit);
      SR04_1Servo.write(SR04_1ServoRightLimit);
      case '9':
      break;
      default:
      Serial.println("Input error, exiting..");
      break;
    }
  break;
  case '9':
     Calibrate = false;
    break;
  default:
    Serial.println("Input error, exiting..");
    break;
  }
}
*/






/*  for (SR04Servo1_Pos = SR04_1ServoLeftLimit; SR04Servo1_Pos >= SR04_1ServoRightLimit; SR04Servo1_Pos -= SR04Servo1_Step) {  // sweep servo and measure echo delay @@@ BLEAH @@@
    SR04_1Servo.write(SR04Servo1_Pos);   // tell servo driver to go in position
    delay(300);                          // delay for the servo to reach the position
    unsigned int us = SR04_1.ping();     // Send ping, get ping time in microseconds (us)
    Serial.print("Ping: ");
    Serial.print(us);                    // DEBUG echo uS via serial terminal
    Serial.println("us");
  }
*/


/*  for (SR04Servo1_Pos = SR04_1ServoRightLimit; SR04Servo1_Pos <= SR04_1ServoLeftLimit; SR04Servo1_Pos += SR04Servo1_Step) {  // sweep servo and measure echo delay @@@ BLEAH @@@
    SR04_1Servo.write(SR04Servo1_Pos);   // tell servo to go to position in variable 'pos'
    delay(300);                          // delay for the servo to reach the position
    unsigned int us = SR04_1.ping();     // Send ping, get ping time in microseconds (uS)
    Serial.print("Ping: ");
    Serial.print(us);                    // DEBUG echo uS via serial terminal
    Serial.println("us");
  }
*/


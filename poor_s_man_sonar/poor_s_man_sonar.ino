/*
HARDWARE NOTES:
 Timer0 millis(),delay(),micros()
 Timer1 ServoTimer1
 Timer2 tone(), NewPing
*/


#include <NewPing.h>      // Timer2
#include <Servo.h>        // Timer1 hw servo 


#define TRIGGER_PIN  7    // arduino trigger pin 12 ultrasonic sensor.
#define ECHO_PIN     6    // arduino echo    pin 11 ultrasonic sensor.
#define MAX_DISTANCE 100  // Maximum distance to measure.
// Maximum sensor distance is rated at 400-500cm.
#define SR04_1ServoPin 9  // SR04 sensor1 servo pin
#define RGBLedRedPin 2
#define RGBLedGreenPin 3

//LedControl Displ7Seg1=LedControl(12,11,10,1); // 12-Data, 11-CLK, 10-Load, 1-1module
Servo SR04_1Servo;        // create servo object to control a servo
// twelve servo objects can be created on most boards

NewPing SR04_1(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);     // NewPing setup of pins and maximum distance.


int          SR04Servo1_Step = -9;         // variable to store/change SR04_1 servo step and direction
unsigned int SR04_1ServoLeftLimit = 140;  // variable to CALIBRATE sweep angle
unsigned int SR04_1ServoRightLimit = 50;  // variable to CALIBRATE sweep angle
unsigned int SR04Servo1_Pos = SR04_1ServoLeftLimit;         // variable to store the servo position
//boolean      SR04_1SweepDone;           // variable to remember if a HALF sweep cicle is done
const unsigned int TERMWIDTH = 60 ;
const unsigned int TERMHEIGHT = 20 ;
const unsigned int XCENTER = TERMWIDTH / 2 ;
const unsigned int YCENTER = TERMHEIGHT ;

const boolean DEBUG = false;

boolean Calibrate = false ;
unsigned int SerialInData ;

void setup() {

    Serial.begin(115200);                   // Open serial monitor at 115200 baud
    SR04_1Servo.attach(SR04_1ServoPin);     // initialize SR04 sensor1 servo driver
    pinMode(LED_BUILTIN,OUTPUT);            // initialize arduino internal LED port

    /*pinMode(RGBLedRedPin,OUTPUT);
      pinMode(RGBLedGreenPin,OUTPUT);         // RGB led
      Displ7Seg1.shutdown(0,false);      // Displ7seg1 initialization
      Displ7Seg1.setIntensity(0,8);       // Set the brightness to a medium values
      Displ7Seg1.clearDisplay(0);         // and clear the display
      SR04_1Servo.write(SR04Servo1_Pos);   // tell servo driver to go in position
    */
}

void loop() {

//if (Serial.available() > 0) calibration();  // enter calibration mode

    SR04_1Servo.write(SR04Servo1_Pos);     // tell servo to go to position in variable 'pos'
//SR04_1Servo.write(95);

    unsigned int us = SR04_1.ping();       // Send ping, get ping time in microseconds (us)
    /*Serial.print("Ping: ");
    Serial.print(us);                      // DEBUG echo uS via serial terminal
    Serial.println("us");
    Serial.println(SR04Servo1_Pos); */
//Serial.println(plot(SR04Servo1_Pos,1));
    //Serial.println("***************");


    for (int ang=0; ang<180; ang+=10) {
        plot(ang,20);
        /*
        Serial.print("angolo=");
        Serial.print(ang);
        Serial.print(",");
        Serial.print(base(ang,10));
        Serial.print(",");
        Serial.print(altezza(ang,10));
        */
        //plot(ang,maxScreenRange());

        delay(500);
    }

    /*
        SR04Servo1_Pos = SR04Servo1_Pos + SR04Servo1_Step;
        delay(300);
        if (SR04Servo1_Pos <= SR04_1ServoRightLimit || SR04Servo1_Pos >= SR04_1ServoLeftLimit) {
            SR04Servo1_Step = -SR04Servo1_Step;       // switch servo direction
    //if (Serial.available() > 0) calibration();  // enter calibration mode
        }
    */

}     // main loop brace!!


void plot(int angolo, int distanza) {
    if(DEBUG) plotDebug(angolo,distanza);
    else
        plot_ncurses(angolo,distanza);
}


void plot_ncurses(int angolo, int distanza) {
    Serial.write(27);
    Serial.write('[');
    Serial.print(base(angolo,distanza));
    Serial.write(';');
    Serial.print(altezza(angolo,distanza));
    Serial.write('H');
    Serial.write('x');
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


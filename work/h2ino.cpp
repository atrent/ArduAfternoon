// picocom -b115200 --imap lfcrlf  /dev/ttyACM0

/*
	*************************
	* H2INO by Matt Huntin' *
        *              rev 0.1b *
	*************************


	TODO:
	- misura frequenza
	- rifinire modifica lib TM1638
	- provare ping median di newping
	- calibrature via bottoni
	- radiohead/virtualwire
*/


#include <Arduino.h>
#include <TM1638.h>
#include <NewPing.h>


#define LED	B00100000    // LED, digital pin 13, PORTB

// H20 level
#define SR04_TRIG	2
#define SR04_ECHO	4
#define SR04_DISTMAX	150
unsigned int watLev;  // h20 lev. in cm, should be percent?
unsigned int watMeasures[8];
byte watMeasNum=0;
byte watMeasErr=0;
bool watMeasFault=0;
byte watMeasDiff=0;
byte watMeasMinThr=20;  // @@@ about equal to watFull
byte watEmpty=125;
byte watFull=30;

NewPing sr04(SR04_TRIG,SR04_ECHO,SR04_DISTMAX);

// led keyboard on PORTB, arduino pin 8(lsb)-13(msb) (6,7 crystal!)
//#define LDK1_DATA	8
#define LDK1_DATA	B00000001
//#define LDK1_CLK	9
#define LDK1_CLK	B00000010
//#define LDK1_STR	10
#define LDK1_STR	B00000100
#define DISPL_BRT	1
byte keys;

TM1638 ldk1(LDK1_DATA,LDK1_CLK,LDK1_STR);  //data,clk,str


// Flow-metering
byte flowFreq=0;
byte flowFreqAcc=0;  // to test displ dot..

// scheduler
unsigned long time;
//unsigned long lastLED;
//unsigned long LEDIntv;
unsigned int upTime;

unsigned long watLevIntv=120;  // measure/process h20 distance evey 120ms
unsigned long watLevLast=0;

unsigned long debugIntv=2000;
unsigned long debugLast=0;



void setup() {
  Serial.begin(115200);
  Serial.write(27);
  Serial.write('[');  // ASCII escape ..
  Serial.write('2');
  Serial.write('J');  // .. clear entire screen;
  Serial.print(F("H2uino, rev 0.1b\n"));

  ldk1.setupDisplay(true,DISPL_BRT); // active,dim
  DDRB = DDRB | LED;  // pin 13 set to output
  }


void WatLevel() {
  if (watMeasNum<7) {
//    ldk1.setupDisplay(0,DISPL_BRT);    //TM1638 OFF
    watMeasures[watMeasNum]=sr04.ping_cm();
//    ldk1.setupDisplay(true,DISPL_BRT); // TM1638 ON
    watMeasNum++;
    }
  else {
    unsigned int watMeasTot=0;
    byte watMeasCntOk=0;
    unsigned int watMeasMax=0;
    unsigned int watMeasMin=0;
    watMeasErr=0;  // @@@ bogus during medium/errors computation
    for (watMeasNum=0; watMeasNum<7; watMeasNum++) {    // sizeof() array ?
      unsigned int watMeasBuf=watMeasures[watMeasNum];  // buf to avoid array cycling
      // jump on lost pings
      if ((watMeasBuf>watMeasMinThr) && (watMeasBuf<SR04_DISTMAX)) {
        watMeasCntOk++;
        watMeasTot+=watMeasBuf;
        // min-max process
        if (watMeasMin==0)         watMeasMin=watMeasBuf;
        if (watMeasBuf>watMeasMax) watMeasMax=watMeasBuf;
        if (watMeasBuf<watMeasMin) watMeasMin=watMeasBuf;
      }
      else {
        watMeasErr++;
        // sonar fault detection
        if (watMeasErr==7) {
          watMeasFault=true;
          return;
        }
      }
    }
    unsigned int watDist=watMeasTot/watMeasCntOk;  // water level distance
    watLev=watEmpty-watDist;
    watMeasDiff=watMeasMax-watMeasMin;
    watMeasNum=0;
    watMeasFault=false;
  }
}


void Freq






void Debug() {
  if (watLev<SR04_DISTMAX) {
    Serial.print(F("\nDEBUG: watLev = "));
    Serial.println(watLev);
    }
  else Serial.println(F("[GUAI] sonar: calibratura errata"));

  if (!watMeasErr) {
    Serial.print(F("DEBUG: watMeasErr = "));
    Serial.println(watMeasErr);
  }
  if (watMeasDiff>0) {
    Serial.print(F("DEBUG: watMeasDiff = "));
    Serial.println(watMeasDiff);
  }
  if (watMeasFault) {
    Serial.println(F("[GUAI] sonar: no echo!"));
  }
  upTime=time/1000;
  Serial.print(F("DEBUG: upTime = "));
  Serial.println(upTime);
}


void LedsDrive() {  // barled
  byte leds=0;  // min leds on
  unsigned int wMax=watEmpty-watFull;
  byte b=map(watLev,0,wMax,0,7); // how many leds on
  if (b) {
    for (byte i=0;i<b;i++) {
      leds=(leds<<1)|B00000001;
    }
  }
  else leds=0;
  ldk1.setLEDs(leds);
}


// display drive per digit - must write entire space for dots to lighton
void DisplNum (unsigned int valueToDispl, byte initPos, byte dots) {
    byte digitNum=4;
    unsigned int div=pow(10,digitNum-1);

    bool isLZ=true;  // last num is a zero
    for (byte i=digitNum;i>0;i--) {
      byte digitBuf=(valueToDispl/div)%10; // MSN first
      div=div/10;
      byte digitPos=initPos+digitNum-i;
      byte dotOn=(dots<<digitPos)&B10000000;  // check the right dot bit

      if (!digitBuf && isLZ) {
        ldk1.clearDisplayDigit(digitPos,dotOn); // pos,dot
      }
      else {
        isLZ=false;
        ldk1.setDisplayDigit(digitBuf,digitPos,dotOn); // digit,pos,dot
      }
    }
}

void DisplDrive() {
  if ((watLev<SR04_DISTMAX) && !watMeasFault) {

    //water level related
    byte dots=0;
    if (watMeasDiff) {
      for (byte i=0;i<watMeasDiff;i++) {
        dots=(dots>>1)|B00001000;
      }
    }
    else dots=0;

    //flow meter level related
    byte dotsL=0;
/*    if (flowFreqAcc) {
      for (byte i=0;i<flowFreqAcc;i++) {
        dotsL=(dotsL>>1)|B10000000;
      }
    }
    else dotsL=0;
*/
    dots=dots|dotsL; // computed dots byte

    DisplNum(upTime,0,dots);
    DisplNum(watLev,4,dots);

  }
  else ldk1.setDisplayToError();
}


void loop() {
  time=millis();

  if (time-watLevLast>=watLevIntv) {
    WatLevel();
    time=millis();
    watLevLast=time;   //  is time useless??
  }

  if (time-debugLast>debugIntv) {
    Debug();
    LedsDrive();
    DisplDrive();
    time=millis();
    debugLast=time;
  }
}


int main(void) {
    init();
    setup();
    for (;;) {
      loop();
      }
}





//  SchedCheckUpdate();

// update time???
//  if ((time-lastSchedCheck)>schedCheckIntv) {
//    SchedCheck();
//    lastSchedCheck=micros();
//   }




/*
// scheduler check update
void SchedCheckUpdate() {
  pwmTaskTotDelay+=pwmTaskDelay;  // TODO max-min!?
  }

void SchedCheck() {  //every schedCheckIntv
  schedDelay=pwmTaskTotDelay/pwmTogTaskN;
  pwmTogTaskN=0;
  pwmTaskTotDelay=0;

  Serial.print("\nSchedCheck:  uptime=");
  unsigned long t = millis()/1000;
  Serial.print(t);
  Serial.print("s");
  Serial.print("\nSchedCheck:  schedDelay=");
  Serial.print(schedDelay);
  Serial.print("us");
  }
*/





/*
void DisplDotBar() {
  ldk1.clearDisplay();
  ldk1.setDisplay(dbar);
  for (short i=0; i<8; i++) {
    if (i==7 && dbar[i]==DPAT) {
     for (i=0; i<8; i++) {
       dbar[i]=0;
       }
     return;
    }
    if (dbar[i] != DPAT) {
      dbar[i] = DPAT;
      return;
    }
  }
}
*/

// 7seg drive
/*
void displDrive() {
const char string[] = "       OUR FUTURE IS OURS        ";
int base = 0;
const char* pos = string + base + 8;

if (pos >= string && pos + 8 < string + sizeof(string)) {
  ldk1.setDisplayToString(pos);
  } else {
  ldk1.clearDisplay();
  }
//base++;

  if (base == sizeof(string) - 8) {
    base = -1 * 8;
  }
*/

//short dbar[8];
//const short DPAT = 128;  // led pattern (dot)

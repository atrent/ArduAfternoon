// Program to demonstrate the MD_Parola library
//
// Simplest program that does something useful - Hello World!

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#if USE_LIBRARY_SPI
#include <SPI.h>
#endif

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may 
// need to be adapted
#define	MAX_DEVICES	1
#define	CLK_PIN		6
#define	DATA_PIN		7
#define	CS_PIN		5

// Hardware SPI connection
//MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);
// Arbitrary output pins
MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup()
{
	Serial.begin(9600);
  P.begin();
  P.displayText("1", LEFT, 10, 5, PRINT, NO_EFFECT);
}

void loop()
{
  P.displayAnimate();
 Serial.println("loop"); 
  delay(500);
}

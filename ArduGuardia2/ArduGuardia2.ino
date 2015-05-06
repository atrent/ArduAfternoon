#include <IRremote.h>

#define FORWARD LOW
#define BRAKE HIGH
#define NO_BRAKE LOW
#define MAX_SPEED 100

int speedA = 0;
int brakeA = BRAKE;
int directionA = FORWARD;

int speedB = 0;
int brakeB = BRAKE;
int directionB = FORWARD;

int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup(){
	pinMode(12, OUTPUT); //Initiates Motor Channel A pin
    pinMode(9, OUTPUT); //Initiates Brake Channel A pin
    pinMode(3, OUTPUT); //Initiates motor Channel A pin (full speed)

    //Setup Channel B
    pinMode(13, OUTPUT); //Initiates Motor Channel B pin
    pinMode(8, OUTPUT);  //Initiates Brake Channel B pin
    pinMode(11, OUTPUT); //Initiates motor Channel B pin (half speed)

    irrecv.enableIRIn(); // 


    Serial.begin(115200);
}

void loop(){
    delay(500);


    //RANGE CHECK A AND B
/*	if(speedA>MAX_SPEED){
		speedA = MAX_SPEED;
	}

	if(speedA<0){
		speedA = 0;
	}

	if(speedB>MAX_SPEED){
		speedB = MAX_SPEED;
	}

	if(speedB<0){
		speedB = 0;
	}
*/

	//Motor A velocita'
	digitalWrite(12, directionA); //Establishes forward direction of Channel A
	digitalWrite(9, brakeA);   //Disengage the Brake for Channel A
	analogWrite(3, speedA);   //Spins the motor on Channel A at full speed

	//Motor B velocita' 
	digitalWrite(13, directionB);  //Establishes forward direction of Channel B
	digitalWrite(8, brakeB);   //Disengage the Brake for Channel B
	analogWrite(11, speedB);    //Spins the motor on Channel B at half speed

/*	brakeA = NO_BRAKE;
	brakeB = NO_BRAKE;

	speedA-=5;
	speedB+=5;
*/	//Serial.println(speedB);

	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		irrecv.resume(); // Receive the next value
	}

    delay(100);
}

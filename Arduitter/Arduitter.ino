/**
 * ======================================== IMPORTANTE ==============================================
 * ====																							 ====
 * ==== ATTENZIONE CHE L'ACCOPPIATA DROPBEAR E				   									 ====
 * ==== ServerAliveInterval DI sshd_config (LOCALE)												 ====
 * ==== FA FALLIRE L'OTA																		 ====
 * ==== link esempio errore:								   									 ====
 * ==== http://www.geeetech.com/forum/viewtopic.php?p=32939&sid=695ae9eb0f4c91a5594fcb2605db996b ====
 * ====																							 ====
 * ==================================================================================================
 * 
 */


#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>


#define FORWARD LOW
#define BACKWARD HIGH
#define BRAKE HIGH
#define NO_BRAKE LOW
#define MAX_SPEED 100
#define SHIFT 30


#define SPEED 50

#define TEMPOPARI 1000
#define TEMPOASIMMETRICO 500

//#define DURATION 3000


// Listen to the default port 5555, the Yún webserver
// will forward there all the HTTP requests you send
//YunServer server;
//YunClient client;
BridgeServer server;
BridgeClient client;


// status
int speedA = 0;
int brakeA = BRAKE;
int directionA = FORWARD;

int speedB = 0;
int brakeB = BRAKE;
int directionB = FORWARD;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(12, OUTPUT); //direction
    pinMode(9, OUTPUT); //Brake
    pinMode(3, OUTPUT); //speed

    //Setup Channel B
    pinMode(13, OUTPUT); //direction
    pinMode(8, OUTPUT);  //brake
    pinMode(11, OUTPUT); //speed
    
    resetStatus();

    //Serial.begin(9600);

    // Bridge startup
    pinMode(13, OUTPUT);
    //blink();
    Bridge.begin();
    //blink();

    // Listen for incoming connection only from localhost
    // (no one from the external network could connect)
    server.listenOnLocalhost();
    server.begin();
    
    
    //for(int i=0;i<20;i++) blink();
}

void loop() {
	//blink();
    // Get clients coming from server
    client = server.accept();

    // There is a new client?
    if (client) {
        // Process request
        process(client);

        // Close connection and free resources.
        client.stop();
    }

    /*
    Serial.print("speedA: ");
    Serial.print(speedA);
    Serial.print("  speedB: ");
    Serial.print(speedB);
    Serial.println();
    */

	//blink();
}











/** avanti per DURATION secondi
*/
void forward(YunClient client, int repeat) {
    speedA=SPEED;
    brakeA = NO_BRAKE;
    directionA = FORWARD;

    speedB=SPEED;
    brakeB = NO_BRAKE;
    directionB = FORWARD;

	//blink();

    apply(client,TEMPOPARI*repeat);
}


void backward(YunClient client, int repeat) {
    speedA=SPEED;
    brakeA = NO_BRAKE;
    directionA = BACKWARD;

    speedB=SPEED;
    brakeB = NO_BRAKE;
    directionB = BACKWARD;

	////blink();
    apply(client,TEMPOPARI*repeat);
}

// TODO: verificare lato motore
void leftwheelforward(YunClient client, int repeat) {
    speedA=SPEED;
    brakeA = NO_BRAKE;
    directionA = FORWARD;

	//blink();
	apply(client,TEMPOASIMMETRICO*repeat);
}


// TODO: verificare lato motore
void leftwheelbackward(YunClient client, int repeat) {
    speedA=SPEED;
    brakeA = NO_BRAKE;
    directionA = BACKWARD;

	//blink();
    apply(client,TEMPOASIMMETRICO*repeat);
}

// TODO: verificare lato motore
void rightwheelforward(YunClient client, int repeat) {
    speedB=SPEED;
    brakeB = NO_BRAKE;
    directionB = FORWARD;

	//blink();
    apply(client,TEMPOASIMMETRICO*repeat);
}

// TODO: verificare lato motore
void rightwheelbackward(YunClient client, int repeat) {
    speedB=SPEED;
    brakeB = NO_BRAKE;
    directionB = BACKWARD;

	//blink();
    apply(client,TEMPOASIMMETRICO*repeat);
}

void rotateLeft(YunClient client, int repeat) {
    speedA=SPEED;
    brakeA = NO_BRAKE;
    directionA = BACKWARD;
    speedB=SPEED;
    brakeB = NO_BRAKE;
    directionB = FORWARD;

	//blink();
    apply(client,TEMPOASIMMETRICO*repeat);
}

void rotateRight(YunClient client, int repeat) {
    speedA=SPEED;
    brakeA = NO_BRAKE;
    directionA = FORWARD;
    speedB=SPEED;
    brakeB = NO_BRAKE;
    directionB = BACKWARD;

	//blink();
    apply(client,TEMPOASIMMETRICO*repeat);
}


/** riporta tutto allo stato di quiete
*/
void resetStatus() {
    speedA = 0;
    brakeA = BRAKE;
    directionA = FORWARD;

    speedB = 0;
    brakeB = BRAKE;
    directionB = FORWARD;
}

/** applica lo stato per DURATION secondi
*/
void apply(YunClient client, int duration) {
    client.println(F("V1.2 applying..."));
	writeStatus();
    delay(duration);
    resetStatus();
    writeStatus();
}


void writeStatus(){
    digitalWrite(12, directionA); //Establishes direction of Channel A
    digitalWrite(9, brakeA);   //Brake for Channel A
    analogWrite(3, speedA);   //Spins the motor on Channel A

    //Motor B velocita'
    digitalWrite(13, directionB);  //Establishes direction of Channel B
    digitalWrite(8, brakeB);   //Brake for Channel B
    analogWrite(11, speedB);    //Spins the motor on Channel B
}

/* no perche' sono gestiti dallo script su openwrt
void snapshot(){}
void play(){}
*/










/*
  Arduino Yún Bridge example

 This example for the Arduino Yún shows how to use the
 Bridge library to access the digital and analog pins
 on the board through REST calls. It demonstrates how
 you can create your own API when using REST style
 calls through the browser.

 Possible commands created in this shetch:

 * "/arduino/digital/13"     -> digitalRead(13)
 * "/arduino/digital/13/1"   -> digitalWrite(13, HIGH)
 * "/arduino/analog/2/123"   -> analogWrite(2, 123)
 * "/arduino/analog/2"       -> analogRead(2)
 * "/arduino/mode/13/input"  -> pinMode(13, INPUT)
 * "/arduino/mode/13/output" -> pinMode(13, OUTPUT)

 This example code is part of the public domain

 http://www.arduino.cc/en/Tutorial/Bridge

 */


// http://192.168.90.22/arduino/LED/23

//TODO: Migliorare parsing

void process(YunClient client) {
    // read the command
    String command = client.readStringUntil('/');
    int param=(client.parseInt()%10)+1;

    if (command == "forward") {
        forward(client,param);
    }

    if (command == "backward") {
        backward(client,param);
    }

    if (command == "leftwheelforward") {
        leftwheelforward(client,param);
    }

    if (command == "leftwheelbackward") {
        leftwheelbackward(client,param);
    }

    if (command == "rightwheelforward") {
        rightwheelforward(client,param);
    }

    if (command == "rightwheelbackward") {
        rightwheelbackward(client,param);
    }

    if (command == "rotateleft") {
        rotateLeft(client,param);
    }

    if (command == F("rotateright")) {
        rotateRight(client,param);
    }

    if (command == F("LED")) {
        blink(client,param);
    }

}

void blink(BridgeClient br, int test){
	for(int i=0;i<10;i++){
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
	}
	client.println(F("V1.2 applying..."));
	writeStatus();
}


/*
void digitalCommand(YunClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  }
  else {
    value = digitalRead(pin);
  }

  // Send feedback to client
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" set to "));
  client.println(value);

  // Update datastore key with the current pin value
  String key = "D";
  key += pin;
  Bridge.put(key, String(value));
}
*/


/*
void analogCommand(YunClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/analog/5/120"
  if (client.read() == '/') {
    // Read value and execute command
    value = client.parseInt();
    analogWrite(pin, value);

    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" set to analog "));
    client.println(value);

    // Update datastore key with the current pin value
    String key = "D";
    key += pin;
    Bridge.put(key, String(value));
  }
  else {
    // Read analog pin
    value = analogRead(pin);

    // Send feedback to client
    client.print(F("Pin A"));
    client.print(pin);
    client.print(F(" reads analog "));
    client.println(value);

    // Update datastore key with the current pin value
    String key = "A";
    key += pin;
    Bridge.put(key, String(value));
  }
}
*/


/*
void modeCommand(YunClient client) {
  int pin;

  // Read pin number
  pin = client.parseInt();

  // If the next character is not a '/' we have a malformed URL
  if (client.read() != '/') {
    client.println(F("error"));
    return;
  }

  String mode = client.readStringUntil('\r');

  if (mode == "input") {
    pinMode(pin, INPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as INPUT!"));
    return;
  }

  if (mode == "output") {
    pinMode(pin, OUTPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as OUTPUT!"));
    return;
  }

  client.print(F("error: invalid mode "));
  client.print(mode);
}
*/

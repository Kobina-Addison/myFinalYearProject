#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Ultrasonic.h>
#include <Key.h>
#include <Arduino.h>
#define IR_INPUT_PIN    2   // INT0
#define NO_LED_FEEDBACK_CODE   // Activate this if you want to suppress LED feedback or if you do not have a LED. This saves 14 bytes code and 2 clock cycles per interrupt.
#include "TinyIRReceiver.hpp"
SoftwareSerial gsmSerial(7, 8); // RX, TX pins
String receivedMessage = ""; // Variable to store multi-part messages



#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

volatile struct TinyIRReceiverCallbackDataStruct sCallbackData;
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'}
};
byte rowPins[ROWS] = {A3, A2, A1, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 11, 10}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



int seconds = 0;
int limit1 = 4;
int limit2 = 9;
int forwardPin = 6;
int reversePin = 5;
int echoPin = 3; //reverse connection on the board, leave the pcb
int trigPin = 0; //reverse connection on the board, leave the pcb
int dist = 0;
char password[7]; // initialize the password array with size 5, including null terminator
char storedPassword[7]; // initialize the stored password array with size 5, including null terminator

int addr = 0;
int trials = 3;
const int buttonPin = 9;
const int buttonPin2 = 4;
int buttonState;
int lastButtonState = LOW;

int buttonState2;
int lastButtonState2 = LOW;

unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTime2 = 0;

unsigned long debounceDelay = 50;
String lcdState = "Closed";
int val = 0;
String gateState = "Closed";
unsigned long seconds2 = 0;

int counter = 10;

int state2 = 0;
bool delayComplete = false;
String defaultDisplay = "CLOSED";
Ultrasonic ultrasonic(echoPin, trigPin);

#include <millisDelay.h>

const unsigned long LED_DELAY = 11000; // in mS (10sec)
millisDelay ledDelay; // the delay object

const unsigned long PRINT_DELAY = 1000; // in mS (2sec)s
millisDelay printDelay; // the delay object

int state = 0;


void setup() {
  lcd.init();
  lcd.backlight();
  welcomeScreen();
  offState();
  gsm();
  // put your setup code here, to run once:
  initPCIInterruptForTinyReceiver();
  EEPROM.get(addr, storedPassword); // read the stored password from EEPROM


  pinMode(forwardPin, OUTPUT);
  pinMode(reversePin, OUTPUT);
  // pinMode(trigPin, INPUT_PULLUP);
  //pinMode(echoPin, INPUT_PULLUP);
  pinMode(limit1, INPUT_PULLUP);
  pinMode(limit2, INPUT_PULLUP);
  pinMode(buttonState, INPUT_PULLUP);
  pinMode(buttonState2, INPUT_PULLUP);


  // Just to know which program is running on my Arduino

  Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
  delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
  // Just to know which program is running on my Arduino
#if defined(ESP8266)
  Serial.println();
#endif
  Serial.println(F("START " __FILE__ " from " __DATE__));
  if (!initPCIInterruptForTinyReceiver()) {
    Serial.println(F("No interrupt available for pin " STR(IR_INPUT_PIN))); // optimized out by the compiler, if not required :-)
  }
  Serial.println(F("Ready to receive NEC IR signals at pin " STR(IR_INPUT_PIN)));
  lcd.clear();



}

void loop() {
  // put your main code here, to run repeatedly:
  char key = customKeypad.getKey(); // read the keypad

  gsmRecieve();
  val = ultrasonic.read();




  if (key) {
    if (key == 'A') {
      state = 1;

    }

    if (key == 'B') {
      state = 2;

    }
  }

  switch (state) {
    case 0:
      defaultState();

      break;
    case 1:
      passwordManager();
      break;

    case 2://ir control
      passwordReset();
      break;

    case 3:// ir control
      forwardMotoring();

      break;

    case 4:
      reverseMotoring();
      break;
    case 5:
      timmedForwardMotoring();
      break;
    case 6:
      keyOpening();
      break;
    case 7:
      reverseMotoring2();
      break;
      case 8:// ir control
      forwardMotoring2();

      break;




  }
}

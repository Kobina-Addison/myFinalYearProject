#include <IRremote.hpp>
#include <EnableInterrupt.h>

volatile int state1 = LOW;
volatile int state2 = LOW;

int closePin=3;
int openPin=0;
int irPin=2;

void setup() {
  pinMode(closePin,INPUT_PULLUP);
  pinMode(openPin,INPUT_PULLUP);
       enableInterrupt(closePin, blink1, CHANGE);
         enableInterrupt(openPin, blink2, CHANGE);

    /*
     * The IR library setup. That's all!
     */
    IrSender.begin(irPin); // Start with IR_SEND_PIN as send pin and if NO_LED_FEEDBACK_CODE is NOT defined, enable feedback LED at default feedback LED pin

   
   
}



uint16_t sAddress1 = 0xFA77;// change command and addresses
uint8_t sCommand1 = 0x1E;
uint8_t sRepeats1 = 4;

uint16_t sAddress2 = 0xFA77;
uint8_t sCommand2 = 0x2F;
uint8_t sRepeats2 = 4;

void loop() {
 
  if(state1==HIGH){
    IrSender.sendNEC(sAddress1, sCommand1, sRepeats1);
  }
  if(state2==HIGH){
    IrSender.sendNEC(sAddress2, sCommand2, sRepeats2);
        

  }
}
void blink1() {
   //ISR function
   state1 = !state1; //toggle the state when the interrupt occurs
}

void blink2() {
   //ISR function
   state2 = !state2; //toggle the state when the interrupt occurs
}

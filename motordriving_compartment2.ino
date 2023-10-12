bool action = false;
int i = 0;
void timmedForwardMotoring() {
  val = ultrasonic.read();

  if (action == false) {
    action = true;
    ledDelay.start(LED_DELAY);
    printDelay.start(PRINT_DELAY);
  }
  printDelay.repeat(); // for next print
 
  lcd.setCursor(0, 0);
  lcd.print("GATE WILL CLOSE");
  lcd.setCursor(0, 1);
  lcd.print("IN T MINUS");
  lcd.setCursor(12, 1);
  lcd.print(ledDelay.remaining() / 1000);
  val = ultrasonic.read();


  if (val < 10 && !ledDelay.justFinished()) {
    ledDelay.start(LED_DELAY);
    printDelay.start(PRINT_DELAY);
  }

  if (val > 10 && ledDelay.justFinished()) {
    lcd.clear();
    action = false;
    updateDisplay("CLOSING");
    state = 7;
  }

  currentMillis = millis();
  if (currentMillis - previousTime > eventInterval) {
    previousTime = currentMillis;

    lcd.clear();
  }
}
void keyOpening() {

  digitalWrite(forwardPin, HIGH);
  digitalWrite(reversePin, LOW);
  int reading = digitalRead(limit1);
  if (reading == LOW) {
    //add the forward motoring code here
    offState();
    if (!gateOpen) {

      offState();
      gateOpen = true;
      gateClosed = false;

      updateDisplay("OPEN");
      defaultDisplay = "OPEN";
      state = 5;
    }

  }
  else {
    if (!gateClosed) {

      gateClosed = true;
      gateOpen = false;
      updateDisplay("OPENING");
    }
  }
  if (gateOpen == false) {
    updateDisplay("OPENING");

  }
}

bool gateOpen = false;
bool gateClosed = false;
bool timmed = false;


void updateDisplay(const String& status1) {
  currentMillis = millis();
  if (currentMillis - previousTime > eventInterval) {
    previousTime = currentMillis;
    lcd.clear();

  }


  lcd.setCursor(0, 0);
  lcd.print("GATE STATUS:");
  lcd.setCursor(0, 1);
  lcd.print(status1);
  lcd.display();

}

void forwardMotoring() {
  digitalWrite(forwardPin, HIGH);
  digitalWrite(reversePin, LOW);
  int reading = digitalRead(limit1);

  if (reading == LOW) {
    
    // Add the forward motoring code here
    offState();

    if (!gateOpen) {
      offState();
      gateOpen = true;
      gateClosed = false;
      
      defaultDisplay = "OPEN";
      defaultState ();
      //state = 0;
    }
    


  }
  else {
    if (!gateClosed) {
      gateClosed = true;
      gateOpen = false;
     defaultDisplay="OPENING";
     defaultState ();
     //state = 0;
    }
  }

}


void forwardMotoring2() {
  digitalWrite(forwardPin, HIGH);
  digitalWrite(reversePin, LOW);
  int reading = digitalRead(limit1);

  if (reading == LOW) {
    
    // Add the forward motoring code here
    offState();

    if (!gateOpen) {
      offState();
      gateOpen = true;
      gateClosed = false;
      
      defaultDisplay = "OPEN";
      defaultState ();
      state = 5;
    }
    


  }
  else {
    if (!gateClosed) {
      gateClosed = true;
      gateOpen = false;
     defaultDisplay="OPENING";
     defaultState ();
     //state = 0;
    }
  }

}



void reverseMotoring() {
  digitalWrite(forwardPin, LOW);
  digitalWrite(reversePin, HIGH);
  int reading2 = digitalRead(limit2);

  if (reading2 == LOW) {
    offState();

    if (!gateClosed) {
      gateClosed = true;
      gateOpen = false;
      defaultDisplay = "CLOSED";
      defaultState ();
      //state = 0;
    }

  }
  else {
    if (!gateOpen) {
      gateOpen = true;
      gateClosed = false;
      defaultDisplay ="CLOSING";
      defaultState ();
      //state = 0;
      
    }
    if (gateClosed == false && val < 10) {
      state = 3;
    }
  }

}

void reverseMotoring2() {

  digitalWrite(forwardPin, LOW);
  digitalWrite(reversePin, HIGH);
  int reading2 = digitalRead(limit2);
  //add the reverse motoring code here
  if (reading2 == LOW) {

    offState();
    if (!gateClosed) {
      gateClosed = true;
      gateOpen = false;
      updateDisplay("CLOSED");
    }
    if (gateOpen == false) {
      defaultDisplay = "CLOSED";
      state = 0;
    }
  }
  else {

    if (!gateOpen) {
      gateOpen = true;
      gateClosed = false;
      updateDisplay("CLOSING");
    }
    if (gateClosed == false && val < 10) {
      state = 8;
    }

  }
}

void offState() {
  digitalWrite(forwardPin, LOW);
  digitalWrite(reversePin, LOW);

}

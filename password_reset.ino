const int DEBOUNCE_TIME2 = 50;
unsigned long lastKeyPressTime2 = 0;
void(* resetFunc) (void) = 0; // Declare reset function at address 0

void passwordReset() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RESET PASSWORD:");

  memset(password, 0, sizeof(password)); // clear the password buffer

  while (true) {
    char key = customKeypad.getKey();
    if (key != NO_KEY && (millis() - lastKeyPressTime2) > DEBOUNCE_TIME2) {
      lastKeyPressTime2 = millis();

      if (strlen(password) < passwordLength) {
        password[strlen(password)] = key;
        lcd.setCursor(strlen(password), 1);
        lcd.print('*');
      }
    }

    if (key == '#') {
      EEPROM.put(addr, password);
      lcd.clear();
      lcd.print("PASSWORD SAVED!");
      delay(1000);
      memset(password, 0, sizeof(password));
       resetScreen();
        resetFunc(); 
      break; // exit the while loop and return from the function
    } else if (key == '*') {
      memset(password, 0, sizeof(password));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RESET PASSWORD:");
    }
  }
}

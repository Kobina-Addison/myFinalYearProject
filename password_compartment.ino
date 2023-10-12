const int DEBOUNCE_TIME = 50;
unsigned long lastKeyPressTime = 0;
int passwordLength=6;

void passwordManager() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER PASSWORD:");

  memset(password, 0, sizeof(password)); // clear the password buffer

  while (true) {
    char key = customKeypad.getKey();
    if (key != NO_KEY && (millis() - lastKeyPressTime) > DEBOUNCE_TIME) {
      lastKeyPressTime = millis();

      if (strlen(password) < passwordLength) {
        password[strlen(password)] = key;
        lcd.setCursor(strlen(password), 1);
        lcd.print('*');
      }
    }

    if (key == 'D') {
      lcd.clear();

      if (strcmp(password, storedPassword) == 0) {
        lcd.setCursor(0, 0);
        lcd.print("ACCESS GRANTED");
        
        state=6;
        
      } else {
        lcd.setCursor(0, 0);
        lcd.print("ACCESS DENIED");
      }

      delay(2000);
      lcd.clear();
      memset(password, 0, sizeof(password));
      
      break; // exit the while loop and return from the function
    } else if (key == '*') {
      memset(password, 0, sizeof(password));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ENTER PASSWORD:");
    }
  }
}

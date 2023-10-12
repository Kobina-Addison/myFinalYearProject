void welcomeScreen() {
  lcd.setCursor(0, 0); // set the cursor position to the top left corner
  lcd.print("LOADING FIRMWARE"); // print "Loading system" on the first row
  lcd.setCursor(0, 1); // set the cursor position to the second row
  for (int i = 0; i < 16; i++) {
    lcd.write(char(255));  // print a full block for the progress bar
    delay(1000); // wait for 0.1 second
  }
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("WELCOME");
  delay(2000);
}

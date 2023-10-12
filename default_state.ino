unsigned long previousTime = 0;   // Stores the previous time
const unsigned long eventInterval = 1000; // Interval in milliseconds (2 seconds)
unsigned long currentMillis = 0;

void defaultState () {
  currentMillis=millis();
if(currentMillis-previousTime>eventInterval){
  previousTime=currentMillis;
 lcd.clear();
  
}
   seconds2 = 0;
  lcd.setCursor(0,0);
lcd.print("GATE STATUS:");
lcd.setCursor(0,1);
lcd.print(defaultDisplay);
 
  
}

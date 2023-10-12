void gsm(){
   gsmSerial.begin(9600);
  delay(1000);
gsmSerial.println("AT+CMGF=1");
  delay(1000);
gsmSerial.println("AT+CNMI=2,2,0,0,0");

}
void gsmRecieve(){

   if (gsmSerial.available()) {
    char c = gsmSerial.read();
    receivedMessage += c; // Add character to message buffer
    
    if (receivedMessage.startsWith("+CMT:")) { // First part of multi-part message
      int endIndex = receivedMessage.indexOf("\r\n"); // Find end of message header
      if (endIndex != -1) {
        receivedMessage = receivedMessage.substring(endIndex + 2); // Remove message header
      }
    }
    
    if (receivedMessage.endsWith("\r\n")) { // End of message
     
      // Process complete message here
    
      receivedMessage = ""; // Clear message buffer
    }
  }
   if( receivedMessage=="Open"){
        state=3;
       
        
      }
       if( receivedMessage=="Close"){
       state=4;
       
      }
}

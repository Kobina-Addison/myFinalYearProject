
#if defined(ESP8266) || defined(ESP32)
void IRAM_ATTR handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat)
#else
void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat)
#endif
{

#if defined(ARDUINO_ARCH_MBED) || defined(ESP32)
  // Copy data for main loop, this is the recommended way for handling a callback :-)
  sCallbackData.Address = aAddress;
  sCallbackData.Command = aCommand;
  sCallbackData.isRepeat = isRepeat;
  sCallbackData.justWritten = true;
#else


  if (aCommand == 0x1E) { // change the addresses and commands
    state = 3;



  }

  if (aCommand == 0x2F) {
    state = 4;



  }

#endif
}

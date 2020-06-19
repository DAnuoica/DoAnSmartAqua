void switchLed(bool value) {
  Serial.println("Switch Led");
  pcf8574a.digitalWrite(PinLed, !value);
  }
void switchFeed(bool value) {
  Serial.println("Switch Feed");
   if(value == true) controlFeed(value);
  }
void switchCooler(bool value) {
  Serial.println("Switch Cooler");
   pcf8574a.digitalWrite(PinCooler, !value); 
  }
void switchOxi(bool value) {
  Serial.println("Switch Oxi");
   pcf8574a.digitalWrite(PinOxi, !value); 
  }

void switchWarmer(bool value) {
  Serial.println("Switch Warmer");
  pcf8574a.digitalWrite(PinWarmer, !value); 
  }
void switchPurifier(bool value) {
  Serial.println("Switch Purifier");
  pcf8574a.digitalWrite(PinPurifier, !value); 
  }

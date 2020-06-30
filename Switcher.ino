void switchLed(bool value) {
  Serial.println("Switch Led");
  LCDClear2();
  if (value) {
    LCDPrint(0, 1, "Turn On Led");
  } else LCDPrint(0, 1, "Turn Off Led");
  pcf8574b.digitalWrite(PinLed, !value);
}
void switchFeed(bool value) {
  Serial.println("Switch Feed");
  LCDClear2();
  if (value) {
    LCDPrint(0, 1, "Turn On Feed");
  } else LCDPrint(0, 1, "Turn Off Feed");
  if (value == true) controlFeed(value);
}
void switchCooler(bool value) {
  Serial.println("Switch Cooler");
  LCDClear2();
  if (value) {
    LCDPrint(0, 1, "Turn On Cooler");
  } else LCDPrint(0, 1, "Turn Off Cooler");
  pcf8574b.digitalWrite(PinCooler, !value);
}
void switchOxi(bool value) {
  Serial.println("Switch Oxi");
  LCDClear2();
  if (value) {
    LCDPrint(0, 1, "Turn On Oxi");
  } else LCDPrint(0, 1, "Turn Off Oxi");
    pcf8574b.digitalWrite(PinOxi, !value);
}

void switchWarmer(bool value) {
  Serial.println("Switch Warmer");
  LCDClear2();
  if (value) {
    LCDPrint(0, 1, "Turn On Warmer");
  } else LCDPrint(0, 1, "Turn Off Warmer");
  pcf8574b.digitalWrite(PinWarmer, !value);
}
void switchPurifier(bool value) {
  Serial.println("Switch Purifier");
  LCDClear2();
  if (value) {
    LCDPrint(0, 1, "Turn On Purifier");
  } else LCDPrint(0, 1, "TurnOff Purifier");
  pcf8574b.digitalWrite(PinPurifier, !value);
}
void turnOffAll() {
  pcf8574b.digitalWrite(PinLed,HIGH );
  pcf8574b.digitalWrite(PinMotor, HIGH);
  pcf8574b.digitalWrite(PinOxi,HIGH );
  pcf8574b.digitalWrite(PinWarmer,HIGH );
  pcf8574b.digitalWrite(PinPurifier,HIGH );
  pcf8574b.digitalWrite(PinCooler,HIGH );
  }

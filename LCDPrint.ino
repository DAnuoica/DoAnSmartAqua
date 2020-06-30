void LCDStatus() {
  LCDClear();
  LCDPrint(0,0, "Nhiet do: " + String(getCurrentTemp()));
  LCDPrint(0,1, "Anh sang: " + String(getCurrentLight()));
  }
void LCDTime() {
  LCDClear();
  LCDPrint(1, 0, "SMART AQUARIUM");
  LCDPrint(0,1, getTime());
  }  

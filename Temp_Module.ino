/*
      red       VCC  ---- 5V (Arduino)
      black     GND  ---- GND (Arduino)
      yellow    DATA ----  2  (Arduino)  16 (wemos)
*/

int getCurrentTemp()
{
  sensors.requestTemperatures();
  // Serial.println(sensors.getTempCByIndex(0));
  delay(50);
  // return round (sensors.getTempCByIndex(0));
  return 28;
}

void stopWarmerCooler ()
{
  if (keyTemp == true) {
    int requestTemp = Firebase.getInt("HoCa/Request");
    int currentTemp = getCurrentTemp();
    Serial.println("Vao che do thay doi nhiet do");
    Serial.print("Nhiet do hien tai cua ho ca:");
    Serial.println(currentTemp);
    Serial.print("Nhiet do tren Firebase: ");
    Serial.println(requestTemp);
    //kiem tra neu currentTemp = fbTemp thi keyTemp = false
    if (currentTemp == requestTemp)
    {
      keyTemp = false;
      switchCooler(false);
      switchWarmer(false);
      Serial.println("Tat tat ca dieu khien nong lanh...");
    }
    else if (currentTemp < requestTemp) {
      Serial.println("Nguoi dung yeu cau tang nhiet do");
      switchCooler(false); // Firstly, switch off the Cooler
      Serial.println("Tat cooler va purifier khong doi");
      switchWarmer(true); // Switch on the Warmer
      Serial.println("Bat warmer");
    }
    else if (currentTemp > requestTemp) {
      Serial.println("Nguoi dung yeu cau giam nhiet do");
      switchCooler(true); // Firstly, switch off the Cooler
      switchPurifier(true); //
      Serial.println("Bat cooler va purifier");
      switchWarmer(false); // Switch on the Warmer
      Serial.println("Tat warmer");
    }
    delay(200);
  }

}

//pushing DATA
void currentStatus() {
  Firebase.setInt("HoCa/Temp", getCurrentTemp());
  Firebase.setInt("HoCa/Light", getCurrentLight());
  delay(50);
  }
void pushData() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["time"] = getTime();
  root["temp"] = getCurrentTemp();
  root["light"] = getCurrentLight();
  root["led"] = Firebase.getBool("HoCa/Led");
  String name = Firebase.push("HoCa/logs", root);
  if (Firebase.failed()) {
    Serial.println(Firebase.error());
    //      return;
  }
  delay(50);
}
void pushData4Trainning() {
  int value = (int)EEPROM.read(address) + 1;
  if (value == 501) {
    EEPROM.write(address, 1);
    delay(5);
    EEPROM.commit();
    value = 1;
  }
  delay(5);
  Serial.print("EEPPROm hien tai   :  ");
  Serial.println(EEPROM.read(address));
  Serial.println("Push data for tranning");
  String pathAPITemp = "data/" + (String)value + "/APITemp";
  String pathTemp = "data/" + (String)value + "/Temp";
  float api = -99.9;
  getAPICurrent(api);
  float temp = getCurrentTemp();
  if (api != -99.9 && temp > -50 && temp < 60) { //kiem tra gia tri co nghia thi moi thuc hien
    Serial.println(pathAPITemp);
    Serial.println(pathTemp);
    Firebase.setFloat(pathAPITemp, api);
    Firebase.setFloat(pathTemp, temp);
    if (Firebase.failed()) {
      Serial.println(Firebase.error());
      //      return;
    }

    EEPROM.write(address, value);
    delay(5);
    EEPROM.commit();
  }

  delay(50);
}
float dataAPI(int i) {
  String pathAPITemp = "data/" + (String)i + "/APITemp";
  float APITemp = Firebase.getFloat(pathAPITemp);
  return APITemp;
}
float dataTemp(int i) {
  String pathTemp = "data/" + (String)i + "/Temp";
  float Temp = Firebase.getFloat(pathTemp);
  return Temp;
}
void training() {
  int value = (int)EEPROM.read(address);
  delay(5);
  if (firstTimeTraining == true) {
    Serial.println("Train lan dau");
    int i = 1;
    while (i <= value) {
      
      double api = (double)dataAPI(i);
      double temp = (double) dataTemp(i);
      Serial.println("i=  " +String( i));
      Serial.println("api:  " + String (api));
      Serial.println("temp:  " + String(temp));
      lr.learn(api, temp);
      i++;
      delay(100);
    }
    firstTimeTraining = false;
    Serial.println("End learn");
  }
  else //train nhung lan sau
  {
    Serial.println("Train khong lan dau, lan sau");
    lr.learn(dataAPI(value), dataTemp(value));
    Serial.println("End learn");
  }
  delay(50);
}
//void Forecast() {
//  float * arr = new float[4];
//  *(arr) = 100.0;
//  getAPIForecast(arr);
//  if (*(arr) != 100.0) {
//    Firebase.setFloat("HoCa/forecast/day1/min", (float)lr.calculate(*(arr + 0)));
//    delay(50);
//    Firebase.setFloat("HoCa/forecast/day1/max", (float)lr.calculate(*(arr + 1)));
//    delay(50);
//    Firebase.setFloat("HoCa/forecast/day2/min", (float)lr.calculate(*(arr + 2)));
//    delay(50);
//    Firebase.setFloat("HoCa/forecast/day2/max", (float)lr.calculate(*(arr + 3)));
//    delay(50);
//    Serial.println("Da tinh toan xong");
//  }
//  else Serial.println("Da xay ra loi APIForecast");
//
//
//}













//void pushData(){
//    String path = "HoCa/Temp";
//    String pathPush = "HoCa/logs/";
//    pathPush+=getTime();
//    String pathTemp = pathPush + "Temp";
//    String pathLight = pathPush + "Light";
//    String pathTest = pathPush + "Test";
////    Serial.println(pathTemp);
//    int currentTemp = getCurrentTemp();
//    Serial.println(currentTemp);
//    Firebase.setInt(pathTemp, currentTemp);
//    Firebase.setInt(pathLight, getCurrentLight());
//    Firebase.setInt(pathTest, 100);
//  //  Firebase.setInt(path, currentTemp);
//  if (Firebase.failed()) {
//      Serial.print("setting /number failed:");
//      Serial.println(Firebase.error());
////      return;
//  }
//    delay(50);
//  }

//void getAPIForecast(float *arr) {
void pushAPIForecast() {
  const char *host = "http://dataservice.accuweather.com/forecasts/v1/daily/5day/352954?apikey=%09p4b8lGaDgn8Zk1qcafzPn8tJi16MJuyP&metric=true";
  HTTPClient http;    //Declare object of class HTTPClient
  Serial.print("Request Link:");
  Serial.println(host);
  http.begin(host);     //Specify request destination
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload from server
  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);   //Print HTTP return code
  Serial.print("Returned data from Server:");
  if (httpCode == 200)
  {
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    //const size_t capacity = 2993 + 5 * JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(5) + 6 * JSON_OBJECT_SIZE(2) + 18 * JSON_OBJECT_SIZE(3) + 2 * JSON_OBJECT_SIZE(5) + 5 * JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(9);
    const size_t capacity = 6000;
    DynamicJsonBuffer jsonBuffer(capacity);
    // Parse JSON object
    JsonObject& root = jsonBuffer.parseObject(payload);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return ;
    }
    // Decode JSON/Extract values
    Serial.println(F("Response:"));
    JsonArray& DailyForecasts = root["DailyForecasts"];
    JsonObject& DailyForecasts_1 = DailyForecasts[1];
    JsonObject& DailyForecasts_2 = DailyForecasts[2];

    JsonObject& DailyForecasts_1_Temperature_Minimum = DailyForecasts_1["Temperature"]["Minimum"];
    float day1min = DailyForecasts_1_Temperature_Minimum["Value"]; // 26.6

    JsonObject& DailyForecasts_1_Temperature_Maximum = DailyForecasts_1["Temperature"]["Maximum"];
    float day1max = DailyForecasts_1_Temperature_Maximum["Value"]; // 32.8

    JsonObject& DailyForecasts_2_Temperature_Minimum = DailyForecasts_2["Temperature"]["Minimum"];
    float day2min = DailyForecasts_2_Temperature_Minimum["Value"]; // 26.3

    JsonObject& DailyForecasts_2_Temperature_Maximum = DailyForecasts_2["Temperature"]["Maximum"];
    float day2max = DailyForecasts_2_Temperature_Maximum["Value"]; // 34.5

    
    Serial.println("Bat dau push du lieu");
    delay(1000);
    Firebase.setFloat("HoCa/forecast/day1/min", (float)lr.calculate((double)day1min));
    delay(1000);
    Firebase.setFloat("HoCa/forecast/day1/max", (float)lr.calculate((double)day1max));
    delay(1000);
    Serial.println("push du lieu thu 2");
    Firebase.setFloat("HoCa/forecast/day2/min", (float)lr.calculate((double)day2min));
    delay(1000);
    Firebase.setFloat("HoCa/forecast/day2/max", (float)lr.calculate((double)day2max));
    delay(1000);
    Serial.println("Da tinh toan xong");

    //        Serial.print("Nhiet do thap nhat ngay 1: ");
    //       Serial.println(DailyForecasts_1_Temperature_Minimum_Value);
    //        Serial.print("Nhiet do cao nhat ngay 1: ");
    //       Serial.println(DailyForecasts_1_Temperature_Maximum_Value);
    //        Serial.print("Nhiet do thap nhat ngay 2: ");
    //       Serial.println(DailyForecasts_2_Temperature_Minimum_Value);
    //        Serial.print("Nhiet do cao nhat ngay 2: ");
    //       Serial.println(DailyForecasts_2_Temperature_Maximum_Value);
  }
  else
  {
    Serial.println("Error in response");
  }

  http.end();  //Close connection
  delay(5000);  //GET Data at every 5 seconds
}

void getAPICurrent(float &temp){
  const char *host ="http://dataservice.accuweather.com/currentconditions/v1/352954?apikey=ULfuqPUt8d5Nk1sZoTJXKKeopuFk300u";
  HTTPClient http;    //Declare object of class HTTPClient
  Serial.print("Request Link:");
  Serial.println(host);
  http.begin(host);     //Specify request destination
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload from server
  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);   //Print HTTP return code 
  Serial.print("Returned data from Server:");  
  if(httpCode == 200)
  {
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = 434+ JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(10);
    //const size_t capacity = 3306+ 5*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(5) + 6*JSON_OBJECT_SIZE(2) + 14*JSON_OBJECT_SIZE(3) + 6*JSON_OBJECT_SIZE(5) + 5*JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(9);
    DynamicJsonBuffer jsonBuffer(capacity);
   // Parse JSON object
    JsonArray& root = jsonBuffer.parseArray(payload);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return;
    }
   // Decode JSON/Extract values
    Serial.println(F("Response:"));
    JsonObject& root_0 = root[0];
    JsonObject& root_0_Temperature_Metric = root_0["Temperature"]["Metric"];
    temp = root_0_Temperature_Metric["Value"]; // 32.2
   Serial.println(temp);
  }
  else
  {
    Serial.println("Error in response");
  }

  http.end();  //Close connection
  
  delay(5000);  //GET Data at every 5 seconds
  }

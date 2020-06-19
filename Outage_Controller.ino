bool Outage() {
//  int value = analogRead(A0); 
//  float volt = (value /(1023.0 *(5/3.3)))*5;
//  Serial.println(volt);
//  if(volt>1) return false;
//  return true;
return false;
}
void servoOpen() {
  gServo1.write(170);
  gServo2.write(10);
  for (int i = 160; i > 30; i = i - 20) {
    gServo1.write(i);
    gServo2.write(180 - i);
    delay(1000);
  }
}
void servoClose() {
  for (int i = 40; i < 180; i = i + 20) {
    gServo1.write(i);
    gServo2.write(180 - i);
    delay(1000);
  }

}

void connectWifi() {
  Serial.println("Reading EEPROM ssid");

  String esid;
  for (int i = 0; i < 32; ++i) {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");

  String epass = "";
  for (int i = 32; i < 96; ++i) {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);

  WiFi.begin(esid.c_str(), epass.c_str());
}
bool testWifi(void) {
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 30 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print(".");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void launchWeb() {
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<div class= 'table'><table border=\"0\" width=\"100%\" cellspacing=\"20px\"><tr><th colspan=\"2\">DANH SÁCH WIFI KHẢ DỤNG</th></tr><tr><th>Tên WIFI</th><th>Cường độ</th></tr>";
  for (int i = 0; i < n; ++i)
  {

    // Print SSID and RSSI for each network found
    st += "<tr> <td>";
    st += WiFi.SSID(i);
    st += "</td> <td>";
    st += WiFi.RSSI(i);
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "   *";
    st += "</td> </tr>";

  }
  st += "  </table></div>";
  delay(100);
  WiFi.softAP("Smart Aquarium Premium", "");
  Serial.println("Initializing_softap_for_wifi credentials_modification");
  launchWeb();
  Serial.println("over");
}

void createWebServer()
{
  {
    server.on("/", []() {

      IPAddress ip = WiFi.softAPIP();
      String head = String ("<head><meta charset=\"UTF-8\"> <title>Thay đổi WIFI</title><style>") +
                    "body{padding:30px 300px 500px;font-size: 20px;}" +
                    ".heade{color:green;width: 100%;height:100px;text-align:center;padding-top: 10px;}" +
                    ".table1{color:red;width: 100%;height:30px;text-align:center;}" +
                    ".table {color: black;width: 100%;height: auto;text-align: center; margin-bottom: 20px;margin-top: 50px;}" +
                    ".table li:hover{color: green;}" +
                    "</style></head>";
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>" + head;
      content += "<body> <div class=\"heade\"><h1>Smart Aquarium manager</h1><hr></div>";
      content += "<div class=\"table\" border=\"0\" width=\"100%\" cellspacing=\"20px\"><form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "<hr>";
      String temp = String("<div class=\"table1\">") +
                    "<form method='get' action='setting'>" +
                    "<table border=\"0\" width=\"100%\" cellspacing=\"20px\">" +
                    "<tr>" +
                    "<th colspan=\"2\">Thay Đổi Kết Nối</th>" +
                    "</tr>" +
                    "<tr>" +
                    "<th>SSID :</th>" +
                    "<th><input type=\"text\" name='ssid' placeholder=\"Nhập tên WIFI\" length=32></th>" +
                    "</tr>" +
                    "<tr>" +
                    "<th>Password :</th>" +
                    "<th><input type=\"password\" name='pass' placeholder=\"Nhập mật khẩu\" length=64></th>" +
                    "</tr>" +
                    "<tr>" +
                    "<th colspan=\"2\"><input type=\"submit\" value=\"Kết Nối\"></th>" +
                    "</tr>" +
                    "</table>" +
                    "</form>" +
                    "</div>";
      content += temp;
      //content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
      content += "</body></html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });

    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");

        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        EEPROM.commit();

        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        checkConnection = true;
        //ESP.reset();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);

    });
  }
}

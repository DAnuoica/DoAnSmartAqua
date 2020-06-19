void controlFeed(bool value) {
    pcf8574a.digitalWrite(PinMotor, !value); 
    analogWrite(in3, 255);
    pcf8574a.digitalWrite(in4, HIGH);
    delay(5000);
    String path = "HoCa/Feed/value";
    Firebase.setBool(path, false);
    pcf8574a.digitalWrite(PinMotor, HIGH);
   }

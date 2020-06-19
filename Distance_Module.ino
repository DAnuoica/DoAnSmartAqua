/*
  Kết nối:
            HCSR04                          Arduino             wemos        code
            VCC                               5V
            GND                               GND
            TRIG                              8                 2             16    p0
            ECHO                              7                 5             14    p1

   Nạp code mở Serial Monitor chọn No line ending, baud 9600.
*/
void notiFeed() {
  Serial.println("Het thuc an");
  delay(50);
}
void percentFeed(int a) {
  Firebase.setInt("HoCa/Feed/remain", a);
  delay(20);
}
void getDistance()
{
  Serial.println("Do khoang cach de");
  int distance = 10;

  //unsigned long duration; // biến đo thời gian
  //    int distance;           // biến lưu khoảng cách
  //    /* Phát xung từ chân trig */
  //    digitalWrite(trig,0);   // tắt chân trig
  //    delayMicroseconds(2);
  //    digitalWrite(trig,1);   // phát xung từ chân trig
  //    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  //    digitalWrite(trig,0);   // tắt chân trig
  //    /* Tính toán thời gian */
  //    // Đo độ rộng xung HIGH ở chân echo.
  //    duration = pulseIn(echo,HIGH);
  //    // Tính khoảng cách đến vật.
  //    distance = int(duration/2/29.412);
  //    /* In kết quả ra Serial Monitor */
  // //   Serial.print(distance);
  // //   Serial.println("cm");
  //    return distance;
  if      (distance == 8) percentFeed(10);
  else if (distance == 7) percentFeed(20);
  else if (distance == 6) percentFeed(30);
  else if (distance == 5) percentFeed(50);
  else if (distance == 4) percentFeed(80);
  else if (distance < 4) percentFeed(100);
  else if (distance > 8) {
    percentFeed(0);
    notiFeed();
  }
}

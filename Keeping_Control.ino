void keepControl() {
  Serial.println("Cap nhat lai trang thai lan cuoi su dung");
  bool arr[4];
  arr[0] = Firebase.getBool("HoCa/Feed/value");
  arr[1] = Firebase.getBool("HoCa/Oxi/value");
  arr[2] = Firebase.getBool("HoCa/Led/value");
  arr[3] = Firebase.getBool("HoCa/Purifier/value");
  delay(100);
  Firebase.setBool("HoCa/Feed/value", false);
  delay(100);
  Firebase.setBool("HoCa/Oxi/value", false);
  delay(100);
  Firebase.setBool("HoCa/Led/value", false);
  delay(100);
  Firebase.setBool("HoCa/Purifier/value", false);
  delay(100);
  Firebase.setBool("HoCa/Feed/value", arr[0]);
  delay(100);
  Firebase.setBool("HoCa/Oxi/value", arr[1]);
  delay(100);
  Firebase.setBool("HoCa/Led/value", arr[2]);
  delay(100);
  Firebase.setBool("HoCa/Purifier/value", arr[3]);
  delay(100);  
 }

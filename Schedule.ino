void setSchedule(bool check) {
  checkSchedule = check;
  if (checkSchedule) {
    led_START = Firebase.getString("HoCa/Led/start"); if (led_START != "") remainSchedule++;
    led_STOP = Firebase.getString("HoCa/Led/stop"); if (led_STOP != "") remainSchedule++;
    feed_START = Firebase.getString("HoCa/Feed/start"); if (feed_START != "") remainSchedule++;

    oxi_START = Firebase.getString("HoCa/Oxi/start"); if (oxi_START != "") remainSchedule++;
    oxi_STOP = Firebase.getString("HoCa/Oxi/stop"); if (oxi_STOP != "") remainSchedule++;
    purifier_START = Firebase.getString("HoCa/Purifier/start"); if (purifier_START != "") remainSchedule++;
    purifier_STOP = Firebase.getString("HoCa/Purifier/stop"); if (purifier_STOP != "") remainSchedule++;
    Serial.println("Da cai dat hen gio");
    LCDClear2();
    LCDPrint(0, 1, "Schedule: ON");
  }
  else {
    remainSchedule = 0;
    LCDClear2();
    LCDPrint(0, 1, "Schedule: OFF");
  }
}

void doSchedule() {
  Serial.println("check schedule");
  Serial.println(remainSchedule);
  Serial.println(checkSchedule);
  if (checkSchedule == true) {
    Serial.println("do schedule");
    String timeS = getTime();

    //HEN GIO NONG LANH
    //  if(coolwarm_START == timeS) {
    //    keyTemp == true ;
    ////    stopWarmerCooler(0);
    //stopWarmerCooler();
    //    if(--remainSchedule == 0)  checkSchedule = false;
    //  }
    //  if(coolwarm_STOP == timeS) {
    //      keyTemp = false;
    //      switchCooler(false);
    //      switchWarmer(false);
    //      switchPurifier(false);
    //      Serial.println("Tat so nong lanh...");
    //      if(--remainSchedule == 0)  checkSchedule = false;
    //  }

    
    //HEN GIO LED
    if (led_START == timeS) {
      Serial.println("LED sang");
      led_START = "";
      Firebase.setBool("HoCa/Led/value", true);
      Firebase.setString("HoCa/Led/start", "");
      if (--remainSchedule == 0)  {
        checkSchedule = false;
        Firebase.setBool("HoCa/Schedule", false);
      }
    }
    if (led_STOP == timeS) {
      led_STOP = "";
      Serial.println("LED tat");
      Firebase.setBool("HoCa/Led/value", false);
      Firebase.setString("HoCa/Led/stop", "");
     if (--remainSchedule == 0)  {
        checkSchedule = false;
        Firebase.setBool("HoCa/Schedule", false);
      }
    }
    //HEN GIO OXI
    if (oxi_START == timeS) {
      Serial.println("Oxi bat");
      oxi_START = "";
      Firebase.setBool("HoCa/Oxi/value", true);
      Firebase.setString("HoCa/Oxi/start", "");
      if (--remainSchedule == 0)  {
        checkSchedule = false;
        Firebase.setBool("HoCa/Schedule", false);
      }
    }
    if (oxi_STOP == timeS) {
      oxi_STOP = "";
      Serial.println("Oxi tat");
      Firebase.setBool("HoCa/Oxi/value", false);
      Firebase.setString("HoCa/Oxi/stop", "");
     if (--remainSchedule == 0)  {
        checkSchedule = false;
        Firebase.setBool("HoCa/Schedule", false);
      }
    }
    //HEN GIO PURIFIER
    if (purifier_START == timeS) {
      Serial.println("Bat Purifier");
      purifier_START = "";
      Firebase.setBool("HoCa/Purifier/value", true);
      Firebase.setString("HoCa/Purifier/start", "");
      if (--remainSchedule == 0)  {
        checkSchedule = false;
        Firebase.setBool("HoCa/Schedule", false);
      }
    }
    if (purifier_STOP == timeS) {
      purifier_STOP = "";
      Serial.println("Tat Purifier");
      Firebase.setBool("HoCa/Purifier/value", false);
      Firebase.setString("HoCa/Purifier/stop", "");
     if (--remainSchedule == 0)  {
        checkSchedule = false;
        Firebase.setBool("HoCa/Schedule", false);
      }
    }
//HEN GIO FEED
    if (feed_START == timeS) {
      Serial.println("Cho an");
      feed_START = "";
      Firebase.setBool("HoCa/Feed/value", true);
      Firebase.setString("HoCa/Feed/start", "");
      if (--remainSchedule == 0)  {
        checkSchedule = false;
        Firebase.setBool("HoCa/Schedule", false);
      }
    }
   
  }

}

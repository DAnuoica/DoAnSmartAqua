void trueTime() {
  timeClient.update();
int  h = timeClient.getHours();
int  m = timeClient.getMinutes();
  if(h % 4 == 0) {
    if(!checkPush) {
      pushData();
      checkPush = true;
      }
    }
  else checkPush = false;
  }
  
  String getTime(){
    timeClient.update();
    return timeClient.getFormattedTime();
    }

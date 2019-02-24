/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include "ESP8266WiFi.h"
#include <SSD1306Wire.h>

SSD1306Wire  display(0x3c, D1, D2);

void setup() {
  Serial.begin(115200);

  //display
  display.init();
  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);  
    
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  display.drawString(0,0,"Wifi Init Done");
  display.display();

  delay(1000);   
  Serial.println("Setup done");
}

String checkStrength(int val) {
  Serial.print(val);
  Serial.print(" ");
  
  /* didn't want to deal with negative values */
  val = abs(val);
  if (val >= 90)
  {
    return "Unusable";
  }
  else if (val < 90 && val >= 80)
  {
    return "Not good";
  }
  else if (val < 80 && val >= 70)
  {
    return "Okay";
  }
  else if (val < 70 && val >= 67)
  {
    return "Very Good";
  }
  else if (val < 67 && val >= 30)
  {
    return "Amazing";
  }
  else if (val < 30)
  {
    return "Unbelievable!";
  }
}

void loop() {
  display.clear();
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  String output;
  String SSID;
  String strength;
  String encryption;
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      SSID = WiFi.SSID(i);
      Serial.print(SSID);
      Serial.print(" (");
      strength = checkStrength(WiFi.RSSI(i));
      Serial.print(strength);
      Serial.print(")");
      encryption = (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
      Serial.println(encryption);  
      delay(10);

      output = SSID + " " + strength + encryption;
      display.drawString(0,i*10,output);
      display.display();
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}

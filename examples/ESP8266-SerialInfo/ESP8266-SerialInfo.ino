/*

  Easy to Use example of ESP8266Info Library

  This example shows the calling convention for the various functions.

  For more information about this library please visit us at
  http://github.com/boseji/ESP8266Info

  Created by Abhijit Bose (boseji) on 20/01/16.
  Copyright 2016 - Under creative commons license 3.0:
        Attribution-ShareAlike CC BY-SA

  @version API 1.0.0
  @author boseji - salearj@hotmail.com

*/
#include <ESP8266Info.h>

void setup() {

  // Configure the Serial Port
  Serial.begin(115200);

  // Calling the ESPInfo Functions
  ESP8266info();  
  ESP8266info_Wifi();

}

void loop() {
  // put your main code here, to run repeatedly:

}

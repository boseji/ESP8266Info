// ---------------------------------------------------------------------------
// Created by Abhijit Bose (boseji) on 20/01/16.
// Copyright 2016 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
//
// Thread Safe: No
// Extendable: Yes
//
// @file ESPInfo.cpp
// A simple Library to Print the ESP8266 Internal Module Info
// 
// @brief 
//
// @version API 1.0.0
//
//
// @author boseji - salearj@hotmail.com
// ---------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include "ESP8266Info.h"

#ifdef ESP8266 /* Happy to Complied in ESP8266 ! */

extern "C" {
#include "user_interface.h"
}


const char cmsg1[]={
  "\r\n\r\n\r\n"
  "==================\r\n"
  " ESP Module Info\r\n"
  "==================\r\n"
  "\r\n"
  " Flash Info:\r\n"
  "-------------\r\n"
};
const char cmsg2[]={
  "\r\n"
  " WiFi Info:\r\n"
  "------------\r\n"
};
#define STATION_IF 0x00
#define SOFTAP_IF 0x01
void infomac(uint8_t *mac)
{
  uint32_t i;
  for(i=0;i<6;i++)
    if(i<5)
      Serial.printf("%02X-",mac[i]);
    else
      Serial.printf("%02X\r\n",mac[i]);
}
bool ESP8266info() {
  FlashMode_t ideMode = ESP.getFlashChipMode();
  uint8_t mac[6];
  
  if(!Serial)
  { 
  	return false;
  }

  Serial.print(cmsg1);  
  Serial.printf("Flash ID   : %08X\r\n",ESP.getFlashChipId());
  Serial.printf("Flash Size : %u\r\n", ESP.getFlashChipRealSize());
  Serial.printf("Flash Speed: %u\r\n", ESP.getFlashChipSpeed());
  Serial.printf("Flash Mode : %s\r\n", 
    (ideMode == FM_QIO ? "QIO" : 
     ideMode == FM_QOUT ? "QOUT" : 
     ideMode == FM_DIO ? "DIO" : 
     ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
  Serial.print(cmsg2);
  wifi_get_macaddr(STATION_IF,mac);  
  Serial.print("Station MAC: ");
  infomac(mac);
  wifi_get_macaddr(SOFTAP_IF,mac);  
  Serial.print("SoftAP  MAC: ");
  infomac(mac);
  return true;
}

#endif /* End of ESP8266 System Level Selection */

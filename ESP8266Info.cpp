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
};
const char cmsg2[]={
  "\r\n"
  " WiFi Info:\r\n"
  "------------\r\n"
};
const char cmsg3[]={
  "\r\n"
  " SPI Flash Info:\r\n"
  "-----------------\r\n"
};
const char cmsg4[]={
  "\r\n"
  " WiFi Station Configuration Info:\r\n"
  "----------------------------------\r\n"
};

void infomac(uint8_t *mac)
{
  uint32_t i;
  for(i=0;i<6;i++)
    if(i<5)
      Serial.printf("%02X-",mac[i]);
    else
      Serial.printf("%02X\r\n",mac[i]);
}
void infoip(struct ip_info *ipf)
{
  /*
    struct ip_info {
      struct ip_addr ip;
      struct ip_addr netmask;
      struct ip_addr gw;
    };
    struct ip_addr {
        uint32 addr;
    };
  */
  Serial.print(" IP      ADDR :");
  Serial.printf(IPSTR,IP2STR(ipf->ip.addr));
  Serial.print("\r\n NetMask ADDR :");
  Serial.printf(IPSTR,IP2STR(ipf->netmask.addr));
  Serial.print("\r\n Gateway ADDR :");
  Serial.printf(IPSTR,IP2STR(ipf->gw.addr));
  Serial.println();
}
bool ESP8266info() {

  if(!Serial)
  { 
  	return false;
  }

  Serial.print(cmsg1);  
  
  return ESP8266info_MACids() && ESP8266info_Flash();
}

bool ESP8266info_MACids()
{
  uint8_t mac[6];
  
  if(!Serial)
  { 
  	return false;
  }
  Serial.print(cmsg2);
  if(wifi_get_macaddr(STATION_IF,mac))
  {  
    Serial.print("Station MAC: ");
    infomac(mac);
  }
  if(wifi_get_macaddr(SOFTAP_IF,mac))
  {
    Serial.print("SoftAP  MAC: ");
    infomac(mac);
  }
  return true;
}

bool ESP8266info_Flash()
{
  FlashMode_t ideMode = ESP.getFlashChipMode();
  
  if(!Serial)
  { 
    return false;
  }
  Serial.print(cmsg3);
  Serial.printf("Flash ID   : %08X\r\n",ESP.getFlashChipId());
  Serial.printf("Flash Size : %u\r\n", ESP.getFlashChipRealSize());
  Serial.printf("Flash Speed: %u\r\n", ESP.getFlashChipSpeed());
  Serial.printf("Flash Mode : %s\r\n", 
    (ideMode == FM_QIO ? "QIO" : 
     ideMode == FM_QOUT ? "QOUT" : 
     ideMode == FM_DIO ? "DIO" : 
     ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
}

bool ESP8266info_Wifi()
{
  struct station_config stc;
  /*
    struct station_config {
      uint8 ssid[32];
      uint8 password[64];
      uint8 bssid_set;
      uint8 bssid[6];
    };
  */
  struct ip_info ipf;
  /*
    struct ip_info {
      struct ip_addr ip;
      struct ip_addr netmask;
      struct ip_addr gw;
    };
    struct ip_addr {
        uint32 addr;
    };
  */
  if(!Serial)
  { 
    return false;
  }
  Serial.print(cmsg4);
  if(wifi_get_opmode() & 0x01) // Should be in Station Mode
  {  
    if(wifi_station_get_config(&stc))
    {
      Serial.printf("SSID      : %s\r\n", stc.ssid);
      Serial.printf("Password  : %s\r\n", stc.password);
      if(stc.bssid_set == 1)
      {
        Serial.print("BSSID: ");
        infomac(stc.bssid);
      }
      if(wifi_station_get_connect_status() == STATION_GOT_IP)
      {
        if(wifi_get_ip_info(STATION_IF,&ipf))
        {
          infoip(&ipf);
        }
        else
        {
          Serial.println("*** !!! Failed to get IP Address Info !!! ***");
        }
      }
      else
      {
        Serial.println("*** Network Not Connected ***");
      }
    }
    else
    {
      Serial.println("*** !!! Failed to get Station mode Info !!! ***");
    }
  }
  else
  {
    Serial.println("*** Not Configured in Station Mode ***");
  }
  return true;
}


#endif /* End of ESP8266 System Level Selection */

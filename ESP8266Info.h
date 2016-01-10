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
// @file ESPInfo.h
// A simple Library to Print the ESP8266 Internal Module Info
// 
// @brief 
//
// @version API 1.0.0
//
//
// @author boseji - salearj@hotmail.com
// ---------------------------------------------------------------------------
#ifndef _ESP8266INFO_H_
#define _ESP8266INFO_H_

#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <inttypes.h>
#include <Print.h>


#ifndef ESP8266
//------------------------------<<<<

#define ESP8266info()

//------------------------------>>>>
#else /* Happy to Complied in ESP8266 ! */
//------------------------------<<<<

/**
 * Prints the Info about the ESP8266 Module under Use
 *
 * @return False - In case the Serial port has not been Initialized
 */
bool ESP8266info();

//------------------------------>>>>
#endif /* End of ESP8266 System Level Selection */

#endif /* End of _ESP8266INFO_H_ */
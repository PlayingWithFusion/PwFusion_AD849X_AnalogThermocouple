/***************************************************************************
* File Name: SEN30103_4ch_exaxmple.ino
* Processor/Platform: Arduino Uno R3 (tested)
* Development Environment: Arduino 1.0.5
*
* Designed for use with with Playing With Fusion AD8494/8495 Analog 
* thermocouple board, SEN-30103
*   ---> (K-type)
*   ---> (J-type)
*
* Copyright © 2014 Playing With Fusion, Inc.
* SOFTWARE LICENSE AGREEMENT: This code is released under the MIT License. 
* 
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
* DEALINGS IN THE SOFTWARE.
* **************************************************************************
* REVISION HISTORY:
* Author			Date		Comments
* J. Steinlage			2014Oct21	Original version
* J. Steinlage                  2015Jan18       Added notes, release version 00
*
* Playing With Fusion, Inc. invests time and resources developing open-source
* hardware and code. Please support Playing With Fusion and continued open-source 
* development by buying products from Playing With Fusion!
*
* **************************************************************************
* APPLICATION NOTES:
* This file configures then runs a program on an Arduino Uno to read a 4-ch
* AD8494/5 analog thermocouple amplifier/conditioner breakout board and print
* results to a serial port. This code:
*    - Configure the Arduino to read analog input channels in a 0-5V config (Uno/Mega)
*    - Configure the UART port to broadcast results to a computer
*    - Calls the 'PlayingWithFusion_AD849x' library to read and return temperature results
*    - Writes formatted information to the serial port with proper engineering units
*  Circuit Setup:
*    Arduino Uno   Arduino Mega  -->  SEN-30103
*    A0            "             -->  TC0 output
*    A1            "             -->  TC1 output
*    A2            "             -->  TC2 output
*    A3            "             -->  TC3 output
*    GND           "             -->  GND
*    5V            "             -->  5V
*   Note: the SEN-30103 plugs directly into the Arduino header across the 
*   power and analog input headers. This board can be used with 3.3V micros
*   by either supplying the 5V input with 3.3V or by removing "L1", 
*   populating the 0603 part next to R4 with a zero ohm resistor and 
*   supplying the 3.3V input with a maximum of 3.3V.
*
*   For wider-range temperature handling, this board can be used with higher
*   voltage equipment. Simply supply the '5V' input with up to 18V to enable
*   full-range output of the amplifiers.
***************************************************************************/


// include Playing With Fusion AD8494/AD8495 libraries
#include <PlayingWithFusion_SEN30103.h>         // core library
#include <PlayingWithFusion_SEN30103_STRUCT.h>  // struct library

// analog pin connections
const int TC0_PIN = 0;
const int TC1_PIN = 1;
const int TC2_PIN = 2;
const int TC3_PIN = 3;

// initialize thermocouple channels
PWFusion_SEN30103 tc_ch0(TC0_PIN);
PWFusion_SEN30103 tc_ch1(TC1_PIN);
PWFusion_SEN30103 tc_ch2(TC2_PIN);
PWFusion_SEN30103 tc_ch3(TC3_PIN);

void setup() {
  Serial.begin(115200);

  // setup for the the analog inputs
  analogReference(DEFAULT);    // set to ~5V input by default (Uno/Mega)
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  // setup time
  delay(100);
}


void loop() 
{
  delay(1000);  // short delay to let you read results as they are produced
  
  static struct var_AD849x TC_CH0;
  static struct var_AD849x TC_CH1;
  static struct var_AD849x TC_CH2;
  static struct var_AD849x TC_CH3;
  double tmp;
  
  // Configure the offset present in your board... uncomment the relevant configuration code
  
  // 0V offset config (SEN-30103-J0 or SEN-30103-K0)
//  TC_CH0.Offset_sel = 0;
//  TC_CH1.Offset_sel = 0;
//  TC_CH2.Offset_sel = 0;
//  TC_CH3.Offset_sel = 0;

  // 1.245V offset config (SEN-30103-J1 or SEN-30103-K1)
  TC_CH0.Offset_sel = 1;
  TC_CH1.Offset_sel = 1;
  TC_CH2.Offset_sel = 1;
  TC_CH3.Offset_sel = 1;
  
  // Custom offset. you must specify a xxx.Offset_alt value if '2' is set in Offset_sel
//  TC_CH0.Offset_sel = 2;                         // 2 = you tell it the offset
//  TC_CH0.Offset_alt = 2.5;                       // alternate offset voltage (set to custom value)
//  TC_CH1.Offset_sel = 2;                         // 2 = you tell it the offset
//  TC_CH1.Offset_alt = 2.5;                       // alternate offset voltage (set to custom value)
//  TC_CH2.Offset_sel = 2;                         // 2 = you tell it the offset
//  TC_CH2.Offset_alt = 2.5;                       // alternate offset voltage (set to custom value)
//  TC_CH3.Offset_sel = 2;                         // 2 = you tell it the offset
//  TC_CH3.Offset_alt = 2.5;                       // alternate offset voltage (set to custom value)
  
  
  // Update TC readings
  struct var_AD849x *an_tc_ptr;
  
  an_tc_ptr = &TC_CH0;
  tc_ch0.SEN30103_update_temp(an_tc_ptr);       // Update thermocouple readings 
  
  an_tc_ptr = &TC_CH1;
  tc_ch1.SEN30103_update_temp(an_tc_ptr);       // Update thermocouple readings 
  
  an_tc_ptr = &TC_CH2;
  tc_ch2.SEN30103_update_temp(an_tc_ptr);       // Update thermocouple readings 
  
  an_tc_ptr = &TC_CH3;
  tc_ch3.SEN30103_update_temp(an_tc_ptr);       // Update thermocouple readings 
  
  // Print thermocuple info to serial port
  Serial.print("TC 0: ");                      // Print TC0 header
  Serial.print(TC_CH0.TC_temp,0);             // print TC temperature - integer value
  Serial.print(" degC  ");                    // print units
  
  Serial.print("TC 1: ");                      // Print TC0 header
  Serial.print(TC_CH1.TC_temp,0);             // print TC temperature - integer value
  Serial.print(" degC  ");                    // print units
  
  Serial.print("TC 2: ");                      // Print TC0 header
  Serial.print(TC_CH2.TC_temp,0);             // print TC temperature - integer value
  Serial.print(" degC  ");                    // print units
  
  Serial.print("TC 3: ");                      // Print TC0 header
  Serial.print(TC_CH3.TC_temp,0);             // print TC temperature - integer value
  Serial.println(" degC");                    // print units

}


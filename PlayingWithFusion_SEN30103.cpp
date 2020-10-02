/***************************************************************************
* File Name: PlayingWithFusion_SEN30103.cpp
* Processor/Platform: Arduino Uno R3 (tested)
* Development Environment: Arduino 1.0.5
*
* Designed for use with with Playing With Fusion AD849x thermocouple
* breakout boards: SEN-30103 (J-type or K-type)
*
* Copyright © 2015 Playing With Fusion, Inc.
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
* J. Steinlage		2015Jan18	Original release version
*
* Playing With Fusion, Inc. invests time and resources developing open-source
* hardware and code. Please support Playing With Fusion and continued 
* open-source development by buying products from Playing With Fusion!
*
* **************************************************************************/

#include "PlayingWithFusion_SEN30103.h"

PWFusion_SEN30103::PWFusion_SEN30103(int8_t tc_pin)
{
  // Function to initialize thermocouple channel, load private variables
  _tc_pin = tc_pin;
  
  // no other config should be necessary
}

void PWFusion_SEN30103::SEN30103_update_temp(struct var_AD849x *tc_ptr)
{
  // Function to unpack and store MAX31865 data
  float _an_volts_in;
  float _temp_float;
  
  _an_volts_in = (float)analogRead(_tc_pin)*(float)5/(float)1023; // read the TC channel
  if(0 == tc_ptr->Offset_sel){_temp_float = _an_volts_in;}
  else if(1 == tc_ptr->Offset_sel){_temp_float = _an_volts_in - 1.245;}
  else if(2 == tc_ptr->Offset_sel){_temp_float = _an_volts_in - tc_ptr->Offset_alt;}
  else{_temp_float = 15;}
  
  tc_ptr->TC_temp = _temp_float / 0.005;

  return;
}


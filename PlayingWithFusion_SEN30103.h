/***************************************************************************
* File Name: PlayingWithFusion_SEN30103.h
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

#ifndef PWF_SEN30103_h
#define PWF_SEN30103_h

#include "Arduino.h"			// use "WProgram.h" for IDE <1.0
#include "avr/pgmspace.h"
#include "util/delay.h"
#include "stdlib.h"
#include "PlayingWithFusion_SEN30103_STRUCT.h"

class PWFusion_SEN30103
{
 public:
  PWFusion_SEN30103(int8_t tc_pin);
  void SEN30103_update_temp(struct var_AD849x *tc_ptr);
  
 private:
  int8_t _tc_pin;
};


#endif

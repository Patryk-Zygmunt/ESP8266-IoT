// pins_arduino.h

#ifndef _PINS_ARDUINO_h
#define _PINS_ARDUINO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#define PIN_WIRE_SDA (4)
	#define PIN_WIRE_SCL (5)

	static const uint8_t SDA = PIN_WIRE_SDA;
	static const uint8_t SCL = PIN_WIRE_SCL;

	#define LED_BUILTIN 16

	static const uint8_t D0 = 16;
	static const uint8_t D1 = 5;
	static const uint8_t D2 = 4;
	static const uint8_t D3 = 0;
	static const uint8_t D4 = 2;
	static const uint8_t D5 = 14;
	static const uint8_t D6 = 12;
	static const uint8_t D7 = 13;
	static const uint8_t D8 = 15;
	static const uint8_t D9 = 3;
	static const uint8_t D10 = 1;

	#include "../generic/common.h"
#else
	#include "WProgram.h"
#endif


#endif


#include "PinStateMock.h"



PinStateMock::PinStateMock()
{
	setAllInPins(0);
	setAllOutPins(0);

}


PinStateMock::~PinStateMock()
{
}

int PinStateMock::getInPinState(int pin)
{
	return pinIn[pin];
}


int PinStateMock::getOutPinState(int pin)
{
	return pinOut[pin];
}

void PinStateMock::setInPinState(int pin, int state)
{
	pinIn[pin] = state;
}

void PinStateMock::setOutPinState(int pin, int state)
{
	pinOut[pin] = state;
}

void PinStateMock::setAllInPins(const int state)
{
	for (int i = 0; i < PIN_IN_AMOUNT; i++) {
		pinIn[i] = state;
	}
}

void PinStateMock::setAllOutPins(const int state)
{
	for (int i = 0; i < PIN_OUT_AMOUNT; i++) {
		pinOut[i] = state;
	}
}





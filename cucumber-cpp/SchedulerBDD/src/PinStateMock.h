#include "IPinState.h"

class PinStateMock: IPinState{




	
public:

	static const  int PIN_IN_AMOUNT = 10;
	static const  int PIN_OUT_AMOUNT = 10;
	
	PinStateMock();
	~PinStateMock();

	// Inherited via IPinState
	int getInPinState(int pin) override;
	int getOutPinState(int pin) override;
	void setInPinState(int pin, int state) override;
	void setOutPinState(int pin, int state) override;
	void setAllInPins(const int pinAmount) override;
	void setAllOutPins(const int pinAmount) override;

private:

	int pinOut[PIN_OUT_AMOUNT];
	int pinIn[PIN_IN_AMOUNT];
};

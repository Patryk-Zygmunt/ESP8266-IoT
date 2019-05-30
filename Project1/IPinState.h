#pragma once
class IPinState
{
public:
	virtual int getInPinState(int pin) = 0;
	virtual int getOutPinState(int pin) = 0;
	virtual void setInPinState(int pin, int state) = 0;
	virtual void setOutPinState(int pin, int state) = 0;
	virtual void setAllInPins(const int state) = 0;
	virtual void setAllOutPins(const int state) = 0;
	

	IPinState();
	~IPinState();

};


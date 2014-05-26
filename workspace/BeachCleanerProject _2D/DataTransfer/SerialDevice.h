/*
 * SerialDevice.h
 *
 *  Created on: 30/12/2013
 *      Author: rgap
 */

#ifndef SERIALDEVICE_H_
#define SERIALDEVICE_H_

#include <string>
#include <SerialStream.h>

class SerialDevice {
private:
	std::string devicePath;
public:
	LibSerial::SerialStream* serialStream;
	SerialDevice(); //"/dev/ttyACM1"
	void setDevice(std::string devicePath_);
	void initializeSerialDevice();
	virtual ~SerialDevice();
};

#endif /* SERIALDEVICE_H_ */
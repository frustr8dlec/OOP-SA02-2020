#pragma once

#include <string>
#include <exception>


struct Bus
{
	long arrive;
	long depart;
	int passengers;
	std::string name;
	int platform;
};

enum BusError
{
	NoData = 1,
	Unknown = 2
};

class BusException : public std::exception
{
public:
	BusException(const char* errMessage, BusError errorType) :m_ErrMessage(errMessage),
		m_ErrorType(errorType) {}

	// overriden what() method from exception class
	const char* what() const noexcept { return m_ErrMessage; }
	BusError GetError() { return m_ErrorType; }
private:
	const char* m_ErrMessage;
	BusError m_ErrorType;
};

class IBusReader
{
public:
	virtual Bus readData(long timeSeconds) = 0;
};
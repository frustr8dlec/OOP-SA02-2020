#pragma once

#include <memory>
#include "IBusReader.h"
#include "FakeStationData.hpp"
#include "FakeTimer.hpp"

class Statistics
{
private:
	std::shared_ptr<IBusReader> _stationData;
	std::shared_ptr<ITimer> _timer;

public:
	Statistics(const std::shared_ptr<IBusReader>& reader, const std::shared_ptr<ITimer>& timer);
	~Statistics();

	// 3rd
	long readData();
	long sampleCount(long duration) { return -1; };
	long sampleTotal() { return -1; };
	// 1st
	double averageDuration(long startTime, long endTime) { return -1.0; }


};


Statistics::Statistics(const std::shared_ptr<IBusReader>& reader, const std::shared_ptr<ITimer>& timer)
{
	_stationData = reader;
	_timer = timer;
	_timer->start();
}


Statistics::~Statistics()
{
}

long Statistics::readData() 
{
	Bus BusSample;

	long timeOfSample = _timer->time(); 
	
	try {
		BusSample = this->_stationData->readData(timeOfSample);
	}
	catch (BusException& e) {
		if (e.GetError() == BusError::NoData)
		{
			throw std::runtime_error("No Bus data at this time!");
		}
		else if (e.GetError() == BusError::Unknown)
		{
			throw std::runtime_error("Unknown error occurred when reading Bus data!");
		}
			
	}
	catch (...)
	{
		throw std::runtime_error("Things went really bad when reading Bus data!");
	}

	// TODO: Code to store the data in the data structure

	return BusSample.depart; // Return the second that the sample was taken at.
};

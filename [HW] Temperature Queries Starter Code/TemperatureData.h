/*
 * TemperatureData.h
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */

#ifndef TEMPERATUREDATA
#define TEMPERATUREDATA

#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

struct TemperatureData {
	// Put data members here
	string id;
	int year;
	int month;
	double temperature;
	
	TemperatureData();
	TemperatureData(string id, int year, int month, double temperature);
	virtual ~TemperatureData();
	bool operator<(const TemperatureData& b);
};

#endif /* TEMPERATUREDATA */

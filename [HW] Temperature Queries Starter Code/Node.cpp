#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "Node.h"

using namespace std;

// Default constructor
Node::Node() : data(), next(nullptr){
	data.id = "1234";
	data.year = -1;
	data.month = -1;
	data.temperature = -99.99;
} // remember to initialize next to nullptr

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature) : data(), next(nullptr) {
	data.id = id;
	data.year = year;
	data.month = month;
	data.temperature = temperature;
}
// remember to initialize next to nullptr

bool Node::operator<(const Node& b) {
	return this->data < b.data;
}

#include "TemperatureDatabase.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

// Default constructor/destructor. Modify them if you need to.

TemperatureDatabase::TemperatureDatabase() : records{LinkedList()}, curr_year(0) {
     time_t t = time(0);
     tm* now = localtime(&t);
     this->curr_year = now->tm_year + 1900;
}

TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	// Implement this function for part 1
	
	string maxDat;
    string id;
    int year;
    int month;
    double temp;
    
    ifstream filestrm(filename);

    if (filestrm.is_open()){
        cout << "Error: Unable to open input.dat" << endl;
    }

    while (getline(filestrm, maxDat)){

        istringstream stream_data(maxDat);
        stream_data >> id;
        if (stream_data.fail()){
            cout << "Error: Other invalid input" << endl;
            continue;
        }
        stream_data >> year;
        if (stream_data.fail()){
            cout << "Error: Other invalid input" << endl;
            continue;
        }
        stream_data >> month;
        if (stream_data.fail()){
            cout << "Error: Other invalid input" << endl;
            continue;
        }

        stream_data >> temp;

        if (stream_data.fail()){
            cout << "Error: Other invalid input" << endl;
            continue;
        }
        else if (year <= 1800 || year > 2022){
            cout << "Error: Invalid year "<< year << endl;
            continue;
        }
        else if (month <=0 || month > 12){
            cout << "Error: Invalid month "<< month << endl;
            continue;
        }
        else if (temp >50 || temp <-50){
            cout << "Error: Invalid temperature "<< temp << endl;
            continue;
        }

        records.insert(id, year,month,temp);
    }

}

// Do not modify
void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}




void TemperatureDatabase::performQuery(const string& filename) {

    ifstream fstr(filename);
    ofstream osrt("result.dat");

    int intbeg = 0;
    int intstop = 0;

    string lnstr = string();
    stringstream sstr = stringstream();
    vector<string> vecspl = vector<string>();

     if (!fstr.is_open()) {

          cout << "Error: Unable to open " << filename << endl;
          return;

     }

     if (!osrt.is_open()) {

          cout << "Error: Unable to open result.dat\n";
          return;

     }
     
     while (true) {

          vecspl.clear();
          lnstr = string();
          getline(fstr, lnstr);

          if (fstr.eof() && lnstr.empty()){
               return;
          }

          sstr.clear();
          sstr.str(lnstr);

          while (!sstr.eof()) {

               string temp = string();
               sstr >> temp;
               vecspl.push_back(temp);

          }

          if (vecspl.size() != 4) {
               cout << "Error: Other invalid query\n";
               continue;
          }

          if (vecspl.at(1) != "AVG" && vecspl.at(1) != "MODE") {
               cout << "Error: Unsupported query " << vecspl.at(1) << endl;
               continue;
          }

          try {
               intbeg = stoi(vecspl.at(2));
          } catch (const std::exception& err) {
               cout << "Error: Other invalid input" << endl;
               continue;
          }

          try {
               intstop = stoi(vecspl.at(3));
          } catch (const std::exception& err) {
               cout << "Error: Other invalid input" << endl;
               continue;
          }

          if (intstop < intbeg) {
               cout << "Error: Invalid range " << vecspl.at(2) << "-" << vecspl.at(3) << endl;
               continue;
          }

          if (intbeg < 1800 || intbeg > curr_year) {
               cout << "Error: Invalid range " << vecspl.at(2) << "-" << vecspl.at(3) << endl;
               continue;
          }

          if (intstop < 1800 || intstop > curr_year) {
               cout << "Error: Invalid range " << vecspl.at(2) << "-" << vecspl.at(3) << endl;
               continue;
          }

          if (vecspl.at(1) == "AVG") {
            
            string id = vecspl.at(0);

            Node* node = this->records.getHead();
            
            double sum = 0;
            int count = 0;

            while (node != nullptr) {

                TemperatureData data = node->data;

                if (data.id == id) {
                    if (intbeg <= data.year && data.year <= intstop) {
                            
                            sum += data.temperature;
                            ++count;
                    }
                }

                node = node->next;
            }

            string final = count ? to_string(this->round((sum / count) * 10000.0) / 10000.0) : "unknown";


            if (final != "unknown") {

                final.erase(final.find_last_not_of('0') + 1, string::npos);
                if (final.back() == '.'){
                    final = final.substr(0, final.size() - 1);
                }
            }


            osrt << id + " " + to_string(intbeg) + " " + to_string(intstop) + " AVG " + final + "\n";
            
          }

          if (vecspl.at(1) == "MODE") {

            string id = vecspl.at(0);

            Node* node = this->records.getHead();
            vector<int> counts = vector<int>(101, 0);

            while (node != nullptr) {
                TemperatureData data = node->data;

                if (data.id == id) {
                    if (intbeg <= data.year && data.year <= intstop) {
                            ++counts.at(round(data.temperature) + 50);
                    }
                }

                node = node->next;
            }

            int max = -1, index = 0;
            for (size_t i = 0; i < counts.size(); ++i) {
                if (counts.at(i) >= max) {
                    max = counts.at(i);
                    index = static_cast<int>(i) - 50;
                }
            }

            string mode = max == 0 ? "unknown" : to_string(index);
            osrt << id + " " + to_string(intbeg) + " " + to_string(intstop) + " MODE " + mode + "\n";

          }
     }
}



int TemperatureDatabase::round(double num) {

    return num < 0 ? static_cast<int>(num - 0.5) : static_cast<int>(num + 0.5);

}
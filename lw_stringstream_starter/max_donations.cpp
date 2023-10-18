#include <iostream>
#include <sstream>
#include <fstream>
using std::cin, std::cout, std::endl, std::string, std::getline,
      std::ifstream, std::istringstream;

int main() {
  string filename;
  cout << "Enter donation filename: ";
  cin >> filename;
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Failed to open file " << filename << "." << endl;
    return 1;
  }
  
  double maxTotalDonation = 0;
  int maxTotalCollector = 0;
  
  // read data

  while (!ifs.eof()){
    
    int uin;
    ifs >> uin;
    string data;
    getline(ifs, data);
    istringstream line(data);
    double val = 0.0;
    double sum = 0.0;
    int count = 0;

    while (line >> val){
      count += 1;
      sum += val;
    }

    if (count > 1 && sum > maxTotalDonation){
      maxTotalDonation = sum;
      maxTotalCollector = uin;
    }
  }

  if (maxTotalDonation == 0){
    cout << "No donations." << endl;
  }
  else{
    cout << "Highest donation total: " << maxTotalDonation << endl;
    cout << "-- collected by id: " << maxTotalCollector << endl;
  }

}

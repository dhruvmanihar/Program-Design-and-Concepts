#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <fstream>

using std::string;
using std::cin;
using namespace std;


//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data from standard in
//---------------------------------------------------------
bool get_runner_data( double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
  //TODO
  // Update function to return the correct boolean values based on the parameters
	
	for (unsigned int i = 0; i <= SIZE; ++i){

		cin >> timeArray[i];
		cin >> countryArray[i];
		cin >> numberArray[i];
		cin >> lastnameArray[i];

		//time validation
		if (timeArray[i] < 0){
			return false;
		}

		//country validation
		if (countryArray[i].length() != 3){
			return false;
		}

		for (unsigned int k = 0; k < 3; ++k){

			if((!isupper(countryArray[i][k])) || (!isalpha(countryArray[i][k])))
				return false;
	
			//number validations

			if(numberArray[i] > 99){
				cout << numberArray[i];
				return false;
			}

		}


		//last name

		for (unsigned int j = 0; j < lastnameArray[i].length(); ++j){

			if (!isupper(lastnameArray[i][0])){
				return false;
			}

			if( (lastnameArray[i].length() < 2) || (!isalpha(countryArray[i][j])) ){
				return false;
			}

		}

	}

	return true;

	
	/*bool time = true;
	bool country = true;
	bool number = true;
	bool name = true;

	//time validation

	for (int i = 0; i < 9; ++i){

		if (timeArray[i] > 0){
			continue;
		}else{
			return false;
		}

		time = true;

	}

	//country validation

	for (int i = 0; i < 9; ++i){

		if ((countryArray[i]).length() == 3){
			continue;
		}else{
			return false;
		}

		for (int j = 0; j < 3; j++){
			string some = countryArray[i];
			
			if (some[j] >= 'A' && some[j] <= 'Z'){
				continue;
			}else{
				return false;
			}

		}

		country = true;

	}
	
	//number validation
	for (int i = 0; i < 9; ++i){

		if (numberArray[i] >= 1 && numberArray[i] <= 99){
			continue;
		}else{
			return false;
		}

		number = true;

	}

	//name validation

	for (int i = 0; i < 9; ++i){

		if ((lastnameArray[i]).length() > 1){
			continue;
		}else{
			return false;
		}

		for (int j = 0; j < 3; j++){
			string some2 = lastnameArray[i];
			
			if ( ( some2[j] >= 'A' && some2[j] <= 'Z' ) || ( some2[j] >= 'a' && some2[j] <= 'z' ) ){
				continue;
			}else{
				return false;
			}

		}		

	}
		
	//final check
	if (time && country && number && name){
		return true;
	}

	return false; // set so it will compile

	*/

	

}
	




//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	for (int i = 0; i < 9; i ++){
		if (ary[i] != 0.0){
			ary[i] = 0.0;
		}
	}
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	for (int i = 0; i < 9; i ++){
		
		if (ary[i] != 0){
			ary[i] = 0;
		}
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	for (int i = 0; i < 9; i++){
	  if (ary[i] != "N/A"){
		  ary[i] = "N/A";
	  }
  	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{

	/*for (unsigned int i = 0; i <= SIZE; i++) {
		double timeUnit = timeArray[i];
		int rank = 1;
		for (unsigned int j = 0; j < SIZE; j++) {
			if (j == i) {
				continue;
			}
			if (timeUnit > timeArray[j]) {
				rank++;
			}
		}
		rankArray[i] = rank;
  	}*/

	for (unsigned int l = 0; l <= SIZE; l++){
		
		int minimum = -1;
		
		for (unsigned int j = 0; j < SIZE; j++) {
			if (rankArray[j] == 0) {
				if (timeArray[minimum] > timeArray[j] || minimum == -1) {
					minimum = j;
				}
			}
		}
	
		rankArray[minimum] = l;
			
	}

}
	



//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}
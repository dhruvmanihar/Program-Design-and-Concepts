#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	
	bool result;
	
	if ((a >= 10) && (b < 10000) && (a <= b)){
		result = true;
	}
	else{
		result = false;
	}

	return result;
}

//new function countDigit implemented
int countDigit(int n)
{
	int count = 0;
	while (n != 0)
	{
		n = n / 10;
		++count;
	}
	return count;
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise

	int digit, digit2;



	char identifier = 'N';
	while (number / 10 != 0) {
		digit = number % 10;
		number = number / 10;
		if (countDigit(number) != 1) {
			digit2 = number % 10;
		}
		else {
			digit2 = number;
		}

		if (digit2 < digit) {
			if (identifier == 'M') {
				return 'N';
			}
			else {
				identifier = 'M';
			}
		}
		else if (digit2 > digit) {
			if (identifier == 'V') {
				return 'N';
			}
			else {
				identifier = 'V';
			}
		}
		else if (digit2 == digit) {
			return 'N';
		}

	}
	return identifier;

}





void count_valid_mv_numbers(int a, int b) {
	
	int numM = 0;
	int numV = 0;
	int intA = a;
	
	while (a <= b)
	{
		if (classify_mv_range_type(a) == 'M')
			numM++;
		else if (classify_mv_range_type(a) == 'V')
			numV++;
		a++;
	}
	
	cout << "There are " << numM << " mountain ranges and " << numV << " valley ranges between " << intA << " and " << b << "." << endl;


	
}
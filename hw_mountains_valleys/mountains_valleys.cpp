#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	// TODO(student): print prompt for input

	cout << "Enter numbers 10 <= a <= b < 10000: ";
	
	// TODO(student): read the numbers from standard input

	int in1;
	int inum2;

	cin >> in1;
	cin >> inum2;

	// TODO(student): validate input (and reprompt on invalid input)

	while (!is_valid_range(in1, inum2))
	{
		if (!is_valid_range(in1, inum2)){

			cout << "Invalid Input" << endl;
			cout << "Enter numbers 10 <= a <= b < 10000: ";
			cin >> in1 >> inum2;

		}
			
	}
	
	

	// TODO(student): compute and display solution

	count_valid_mv_numbers(in1, inum2);
	
	return 0;
}
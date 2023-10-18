#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

    bool stop = false;

    while(!stop){

        cout << ">> ";

        string userIn;
        getline(cin,userIn);


        if(userIn == "quit" || userIn == "q"){
            stop = true;
            break;
            
        }else {

			string first;
			string second;
            string fin;
			char port;
			int portP;
			int userinputLen = userIn.length();

			for (int i = 0; i < userinputLen; i++) {
				if (userIn.at(i) == ' ') {
					portP = i;
					i = userinputLen;
				}if (i == userinputLen) {
					continue;
				}
				else {
					first.push_back(userIn.at(i));
				}
			}

			port = userIn.at(portP + 1);

			for (int i = portP + 3; i < userinputLen; i++) {
				second.push_back(userIn.at(i));
			}

			if (port == '+') {
				fin = add(first, second);
			}
			if (port == '*') {
				fin = multiply(first, second);
			}
			

            cout << endl << "ans =" << endl << endl << "    " << fin << endl << endl;
		}
	}

    cout << endl << "farvel!";

}


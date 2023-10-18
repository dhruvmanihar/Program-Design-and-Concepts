#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() {

    string password;
    string backwards;


    cout << "Please enter your text input: ";
    cin >> password;
    cout << "input: " << password;

    //string array[5] = {"a","e","i","o","u"};
    //string array[5] = {"@", "3", "!", "0", "^"};
    
    for (int i = 0; i < password.size(); i++){
        char placement = password.at(i);

        switch (placement){
            case('a'):
            password.replace(i, 1, "@");
            break;
            case('e'):
            password.replace(i, 1, "3");
            break;
            case('i'):
            password.replace(i, 1, "!");
            break;
            case('o'):
            password.replace(i, 1, "0");
            break;
            case('u'):
            password.replace(i, 1, "^");
            break;
        }

    }

    for (int i = password.size() - 1; i >= 0; i--){

        backwards = backwards + password.at(i);
    }

    cout << endl << "output: " << password << backwards;

    return 0;
}

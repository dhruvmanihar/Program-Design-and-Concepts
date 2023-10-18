#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() {

    string origSentence;
    string digits;
    string finalSent;
    int size;
    int start = 0;

    cout << "Please enter obfuscated sentence: ";
    cin >> origSentence;

    cout << "Please enter deobfuscation details: ";
    cin >> digits;

    for (int i = 0; i < digits.size(); i++){

        size = (int)digits[i] - 48;

        if (i == digits.size() - 1)
            finalSent = finalSent + origSentence.substr(start, size);
        else
            finalSent = finalSent + origSentence.substr(start, size) + " ";

        start += size;    
    }

    cout << "Deobfuscated sentence: " << finalSent;

    return 0;
}

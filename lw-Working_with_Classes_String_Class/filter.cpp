#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() {

    string word;
    string filter;
    int startIn;
    string replace;

    cout << "Please enter the sentence: ";
    getline(cin, word);
    cout << endl << "Please enter the filter word: ";
    cin >> filter;

    startIn = word.find(filter);

    for(int i = 0; i < filter.size(); i++){
        replace += "#";
    }

    while (word.find(filter) != string::npos){
        word.replace(startIn, filter.size(), replace);
    }


    return 0;

}

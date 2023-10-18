#include <iostream>
#include <iomanip>
#include <fstream>

using std::cin;
using std::cout;
using namespace std;


//Question 1

int main() {
    
    //declare and read in input, use long long to get any type of input
    long long int n; 
    cin >> n; 
    cout << "n = " << n << " outputs a rating of ";

    //intialize loopint to keep seperate from initital input
    long long int loopint = n;

    //intialize i for digit place and total 
    long long int i = 1;
    int total = 0;

    //checks for input 0 and outputs result
    if (n == 0 || n == -0){
        cout << "0 = (0)";
    }

    //until input int n reaches 0 or -0 loop will run
    while (loopint != 0 || loopint != -0){
        
        //check if input is positive
        if (n > 0){
            //check if rightmost digit is divisible by poition
            if (((loopint % 10) % i) == 0){
                total += 1;
    
                //to make previous digit rightmost now
                loopint /= 10;

                //checks for next digit now
                i++
            }
        //for negative numbers
        }else{
            //check if rightmost digit is not divisible by poition
            if (((loopint % 10) % i) != 0){
                //total subtracts because total should be negative
                total -= 1;
    
                //to make previous digit rightmost now
                loopint /= 10;

                //checks for next digit now
                i++
            }
        }

    }

    //continues output from above
    cout << total;


    
    return 0;
}


/////end of question 1










//Question 2

void decode(char alphabet[], unsigned int nums1[], unsigned int nums2[], unsigned int size){

    //intialize alphabet length to 0
    int alphlenght = 0;

    //length of alphabet
    while (alphlenght != "\0"){
        alphlenght += 1;
    }
    
    //error exceptions
    //if alphabet length 0
    if (alphabet == "\0" || ){
        throw std::invalid_argument("Alphabet length is 0");
    }
    //check for invalid letters though char ascii table (assuming all are lower case as given in examples)
    for (int i = 0; i < alphlenght; i++){
        if (alphabet [i] < 97 || alphabet[i] > 122){
            throw std::invalid_argument("Alphabet contains invalid characters");
        }
    }


    //loop to decode 
    for (int i = 0; i < size; i++){
        
        int j;

        //in order to alternate between nums 1 and nums 2
        if ((int i % 2) == 0){
            int j = nums1[i];
        }else{
            int j = nums2[i];
        }
        

        //used for wrap around
        if (j > alphlenght){
            for (int k = 0; k < alphlenght; k++){
                //temp is to keep track of total iterations because k can loop
                int temp = 0; 
                if (temp = j){
                    cout << aplhabet[k];
                }
                
                //resets loop for wrap around
                if (k == alphlenght-1){
                    k = 0;
                }
                temp ++;

            }
        //used for non wrap
        }else{
            cout << alphlenght[i];
        }

    }

 

}


////end of question 2
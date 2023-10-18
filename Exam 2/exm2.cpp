#include <iostream>
#include <iomanip>
#include <fstream>

using std::cin;
using std::cout;
using namespace std;


//question 3

# include <iostream>

struct backQueue {
    char* array = nullptr;
    int capacity = 0;
    int size = 0;
};
 
void push(backQueue& queue, char character) {

    //for resizing array

    //set to 1 if array is nullptr
    if (queue.array == nullptr){
        queue.capacity = 1;
    }

    if(queue.capacity <= (queue.size + 1))
        {
            queue.capacity *= 2;
            char* temp = new char[queue.capacity];
            for (int i = 0; i < queue.size; i++){
                temp[i] = queue.array[i];
            }
            delete[] queue.array;
            queue.array = temp;

        }
        
    

    if (queue.capacity == 1){ //only works for capacity 1

            //add character value to first spot and update size
            queue.array[0] = character;
            queue.size++;
            
    }else{ //for all other capactities
            
            char* temp2 = new char[queue.capacity];

            //copies array into temp2 array but all vallues are shifted one index to right 

            for (int i = 0; i < queue.size +1 ; i++){
                temp2[i + 1] = queue.array[i];
            }
            
            //delete for memeory
            delete[] queue.array;

            //reassign
            queue.array = temp2;

            //add character value to first spot and update size
            queue.array[0] = character;
            queue.size++;

        }

}

 
char pop(backQueue& queue) {
    
    if(queue.size == 0){
		return '\0';
    }

	int result = queue.array[queue.size - 1];
	queue.size--;

	return result;
 
}
 
int main() {
    backQueue q;
 
    push(q, 'a');
    std::cout << pop(q) << '\n';
 
    // OPTIONAL TODO: add more test cases

   
    delete[] q.array;
}
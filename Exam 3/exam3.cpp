#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <ctime>

using std::cin;
using std::cout;
using namespace std;


//question 2

#include <iostream>
#include <cassert>
using std::cout, std::endl;
 
class Friends {
   int* count;
 
 public:
   Friends(int num) : count{nullptr} {
      count = new int[1]{num};
   }
      
   // TODO: add destructor

    ~Friends (){
        for (unsigned int i=0; i<count.size(); ++i) { 
            delete [] count[i]; // delete each individual array placed on the heap
        }
        delete [] count;
        count = nullptr;
    }
    
   // TODO: add copy constructor  

   Friends(const Friends& t) : count{nullptr} {

        count = new int[1]{t};
        delete t[];
    }

    void Friends::copy(const Array& a) 
    {
    // Copy a's elements into the elements of *this 
    int *p = ptr_to_data;
    int *q = a.ptr_to_data + num_elts;
    while (p > ptr_to_data)
         *--p = *--q;
    }


   // TODO: add copy assignment operator    

   Friends& operator=(const Friends& t) {

        if (ptr_to_data != rhs.ptr_to_data)
        {
        setSize(rhs.num_elts);
       	copy(rhs);
        }
        return *this;
        
   }

   void Friends::setSize(int n) 
    {
    if (n != num_elts)
       {
        delete[] ptr_to_data;               // Delete old elements, 
        num_elts = n;                       // set new count, 
       	ptr_to_data = new int[n];         // and allocate new elements 
       }
    }

}


 
int main() {
   Friends v(42);
   Friends v2(v);
   
   assert(v == 42);
   assert(v2 == 42);
 
   v2.increment();
 
   assert(v == 42);
   assert(v2 == 43);
   
   v2 = v;
   
   assert(v == 42);
   assert(v2 == 42);
   
   v2.increment();
 
   assert(v == 42);
   assert(v2 == 43);
   
   cout << "So long, and thanks for all the fish!" << endl;
      
   return 0;
}





//question 3

struct Node {
 public:
    double value; 
    Node* next;
    Node(double num) : value{num}, next{nullptr} {}
};
 
class CircList {
 private:
    Node* listptr;
    int size; //size of list
 public:
    // Constructor
    CircList() : listptr{nullptr} {}

    // The insertNode function inserts a node with num copied to its value
    // member so that the list remains sorted in non-decreasing order.                 
    void insertNode(double num);
    // TODO(student): implement this function
 
    void print(std::ostream& os=std::cout) const {
        // assumed to exist
        // prints the list to the output stream (default: stdout)
    }
 
    // The mergeArray function merges the array passed into dArray into the
    //  ordered list.     	 
    void mergeArray(double dArray[], size_t size);
    // TODO(student): implement this function
 
};


void insertNode(double num){


    if (index>size || index < 0) {
            return;
        }

            Node* current= head;
            head == nullptr;
            Node* new_node = new Node(value);
            

            //only executes if inserting at head
            if (index == 0) {
                new_node->next = current;
                
                head = new_node;
            }
            else {
                
                for(int i=0;i<index-1;++i) {
                    current= current->next;
                }
            
                new_node->next = current->next;
                current->next = new_node;
            }
    
    
    // Increase size whenever inserting nod
    size++;

}


void mergeArray(double dArray[], size_t size){

    //sort array in ascending order
    for(int i=0; i<size; i++)
    {
        for(int j=i+1; j<size; j++)
        {
            //If there is a smaller element found on right of the array then swap it.
            if(dArray[j] < dArray[i])
            {
                double temp = dArray[i];
                dArray[i] = dArray[j];
                dArray[j] = temp;
            }
        }
    }

    insertNode(dArray[]);


}




//question 4

# include <iostream>
# include <string>
 
// scene struct
struct SnowGlobe {
    std::string scene = "";
    std::string size = "";
};
 
// outputs scene titles
void outputScenes(SnowGlobe**& snowglobes, unsigned int& shelves) {
    std::cout << "Shelf:\n";
 
    for (unsigned int shelf = 0; shelf < shelves; shelf++) {
        for (unsigned int snowglobe = 0; snowglobe < 5; snowglobe++) {
            std::cout << snowglobes[shelf][snowglobe].scene<< " ";
        }
        std::cout << '\n';
    }
 
    std::cout << '\n';
}
 
// adds shelf
void addShelf(SnowGlobe**& snowglobes, unsigned int& shelves) {
    // TODO: add shelf for 5 snowglobes

    //adds shelves and makes 5 capapcity
    for (int i = 0; i < shelves; i++)
    {
        for (int j = 0; j < 5; j++){//adds 5 snowglobes to shelves
            snowglobes [i][j] = nullptr;
        }
    }

}
 
// adds SnowGlobe
void addSnowGlobe(SnowGlobe**& snowglobes, unsigned int& shelves, std::string _Scene, std::string _Size) {
    // TODO: add snowglobe to shelf

    //make new snowglobe
    SnowGlobe newAdd;
    newAdd.scene = _Scene;
    newAdd.size = _Size;

    //tries to add snowglobe
    try{
        for (int i = 0; i < snowglobes[i].size; i++){

            for int j = 0; j < 5; j++{
                
                if (snowglobes[i][j] == nullptr){
                    snowglobes[i][j] == newAdd; // adds new snowglobe if empty spot on shelve
                    return;
                }
            }
            
        }

        addShelf(snowglobes, 1); //adds shelf if runst through loop and all positions are filled
    }
    //if any error, adds new shelve and tries again, just for redundancy in case of error
    catch (...){

        addShelf(snowglobes, 1);

        for (int i = 0; i < snowglobes[i].size; i++){
            if (snowglobes[i][j] == nullptr){
                snowglobes[i][j] == newAdd
            }
        }
    }


}
 
int main() {
    std::string Scene;
    std::string Size;
 
    SnowGlobe** snowglobes = nullptr;
    unsigned int shelves = 0;
 
    while (true) {
        std::cout << "Enter name of snowglobe (q to exit): ";
        std::cin >> Scene;
 
        if (Scene == "q") {
            break;
        }
 
        std::cout << "Enter the size: ";
 
        Size = "";
        std::cin >> Size;
 
        addSnowGlobe(snowglobes, shelves, Scene, Size);
 
        outputScenes(snowglobes, shelves);
    }
 
    // deallocate dynamic memory
    if (snowglobes != nullptr) {
        for (unsigned int shelf = 0; shelf < shelves; shelf++) {
            delete[] snowglobes[shelf];
        }
 
        delete[] snowglobes;
    }
}

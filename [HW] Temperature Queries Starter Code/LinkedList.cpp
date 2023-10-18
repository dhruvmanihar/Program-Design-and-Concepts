#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "LinkedList.h"
#include "Node.h"

using std::string;
using std::to_string;
using std::ostream;
using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr){
	// Implement this function
}

LinkedList::~LinkedList() {
	// Implement this function
	this->clear();
}

LinkedList::LinkedList(const LinkedList& source) : head(nullptr), tail(nullptr) {
	// Implement this function
	if (source.getHead() == nullptr){
        head = nullptr, tail = nullptr;
    }

    Node* originalP = source.head;

    while(originalP != nullptr){

        this->insert(originalP->data.id,originalP->data.year,originalP->data.month,originalP->data.temperature);
        originalP = originalP->next;

    }

}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// Implement this function
	
    if (this == &source){
        return *this;
    }

    this->clear();

    if (source.getHead() == nullptr){
        head = nullptr, tail = nullptr;
    }

    Node* originalP = source.head;

    while(originalP != nullptr){

        this->insert(originalP->data.id,originalP->data.year,originalP->data.month,originalP->data.temperature);
        originalP = originalP->next;

    }

    return *this;

}

void LinkedList::insert(string location, int year, int month, double temperature) {
	// Implement this function

    Node* nextN = new Node(location, year, month, temperature);

     if (!this->head){
          this->head = nextN;
          this->tail = nextN;
          return;
     }

   
     if (*nextN < *this->head){
          nextN->next = this->head;
          this->head = nextN;
          return;
     }


     if (*this->tail < *nextN){
          this->tail->next = nextN;
          this->tail = nextN;
          return;
     }

     Node* node = this->head;

     while (*node < *nextN){

        nextN->next = node;
        node = node->next;

     }

     nextN->next->next = nextN;

     nextN->next = node;
}
    


void LinkedList::clear() {
	// Implement this function
    if (!this->head){
        return;
    }

    Node* cont = this->head, *next;

    while(cont){

        next = cont -> next;
        delete cont;
        cont = next;

    }

    this -> head = nullptr;
    this -> tail = nullptr;

}

Node* LinkedList::getHead() const {
	// Implement this function it will be used to help grade other functions
	return this->head;
}

string LinkedList::print() const {

	string outputString = string();

	// Implement this function
    
    if (this->head == nullptr){

        return outputString;

    }

    Node* node = this->head;
     
    while (node != nullptr) {

        string endFin = to_string(node->data.temperature);

        endFin.erase(endFin.find_last_not_of('0') + 1, string::npos);

        if (endFin.back() == '.'){
            endFin = endFin.substr(0, endFin.size() - 1);
        }

        outputString += node->data.id + " " + to_string(node->data.year) + " " + to_string(node->data.month) + " " + endFin + "\n";
        
        node = node->next;
     }
    

	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}

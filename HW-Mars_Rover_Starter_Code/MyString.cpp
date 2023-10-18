
#include <iostream>
#include <fstream>
#include <tuple>
#include <limits>
#include <stdexcept>
#include "MyString.h"

MyString::MyString(): strLen{0}, strCap{15}, strChar{new char[15]} {
	
    for (size_t i = 0; i < this->strCap; ++i){
        
        this->strChar[i] = static_cast<char>(0);

    }

}

MyString::MyString(const MyString& string): strLen(string.strLen), strCap(string.strCap), strChar(nullptr){

	strChar = new char[strCap];

	for(size_t i = 0; i < string.length(); i++){
		strChar[i] = string.strChar[i];
    }
		
	strChar[strLen] = '\0';
}

MyString::MyString(const char* str) : strLen{0}, strCap{15}, strChar{nullptr} {

     if (str == nullptr)
          throw std::invalid_argument("");

     size_t i = npos;
     while (str[++i]) {}

     this->strLen = i;

     while (this->strLen > this->strCap){
          this->strCap *= 2;
     }

     this->strChar = new char[this->strCap];

     for (i = 0; i < this->strCap; ++i)
          this->strChar[i] = i < this->strLen ? str[i] : static_cast<char>(0);

}

MyString::~MyString(){
	delete[] strChar;
}

void MyString::resize(size_t newSize){
	
    if (newSize < this->strLen)
        this->strLen = newSize;
     
     this->strCap = newSize;
     
     this->strChar[newSize] = static_cast<char>(0);
}

size_t MyString::capacity() const{
	return strCap;
}

size_t MyString::size() const{
	return strLen;
}

size_t MyString::length() const{
	return strLen;
}

const char* MyString::data() const{
	return strChar;
}

bool MyString::empty() const{
	if(this->length() == 0){
		return true;
    }
	
	return false;
}

const char& MyString::front() const{
	return strChar[0];
}

const char& MyString::at(size_t index) const{
	if(index >= length()){

		throw std::invalid_argument("");

    }

	return strChar[index];
}

void MyString::clear(){

	for (size_t i = 0; i < this->strLen; ++i){

        this->strChar[i] = static_cast<char>(0);

    }

    this->strLen = 0;
    this->strCap = 1;
}

//

MyString& MyString::operator= (const MyString& string)
{
	delete[] strChar;

	strLen = string.length();
	strCap = string.capacity();

	strChar = new char[strCap];

	for(size_t i = 0; i < string.length(); i++){
		strChar[i] = string.strChar[i];
    }
	
	strChar[strLen] = '\0';

	return *this;
}

MyString& MyString::operator+= (const MyString& string)
{
	size_t tempSize = strLen;

	for(size_t i = 0; i < string.length(); i++){
		if(strCap == i + tempSize){
			resize(strCap * 2);
        }
		strLen += 1;

		strChar[i + tempSize] = string.at(i);
	}
	
	strChar[strLen] = '\0';
	return *this;

}

size_t MyString::find(const MyString& string, size_t index) const
{
	for(size_t i = index; i < length(); i++){

		bool ifTrue = true;

		if(strChar[i] == string.at(0)){

			if(string.length() == 1){
				return i;
            }

			for(size_t j = 0; j < string.length(); j++){
                
				if(strChar[i + j] != string.at(j)){

					ifTrue = false;
					break;

				}
            }

			if(ifTrue){
				return i;
            }
		}
	}

	return -1;
}

std::ostream& operator<< (std::ostream& os, const MyString& string)
{
	for(size_t i = 0; i < string.length(); i++){

        os << string.at(i);

    }
		
	return os;
}

bool operator==(const MyString& left, const MyString& right) noexcept {

     if (left.size() != right.size()){
          return false;
     }

     for (size_t i = 0; i < left.size(); ++i){
          
          if (left.at(i) != right.at(i))
               return false;
    }

     return true;
}

MyString operator+(const MyString& left, const MyString& right) {

     return MyString(left) += MyString(right);

}

#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <fstream>
#include <tuple>
#include <limits>
#include <stdexcept>

class MyString
{
	private:
		size_t strLen;
		size_t strCap;
		char* strChar;
	
	public:
        
        static const size_t npos = 18446744073709551615UL;

		MyString();
		MyString(const MyString& string);
		MyString(const char* string);
		~MyString();
		
		void resize(size_t currentSize);
		size_t capacity() const;
		size_t size() const;
		size_t length() const;
		const char* data() const;
		
		bool empty() const;
		const char& front() const;
		const char& at(size_t index) const;
		void clear();
		
        
		MyString& operator= (const MyString& string);
		MyString& operator+= (const MyString& string);
		size_t find(const MyString& string, size_t index = 0) const;

        //extra
        friend bool operator==(const MyString& left, const MyString& right) noexcept;
        friend MyString operator+(const MyString& left, const MyString& right);

		
};

        std::ostream& operator<< (std::ostream& os, const MyString& string);
		
	

#endif
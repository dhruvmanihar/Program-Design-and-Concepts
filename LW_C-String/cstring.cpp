#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)
  unsigned int i = 0;
  
  while ((str[i]) != '\0'){
    i++;
  }

  return i;

}

unsigned int find(char str[], char character) {
  
  for (unsigned int i = 0; i < length(str); ++i){

    if (str[i] == character){

      return i;

    }

  }

  return length(str);

}



bool equalStr(char first[], char second[]) {
  
  if (length(first) != length(second)){

    return  false;

  }
  
  for (unsigned int i = 0; i < length(first); ++i){

      if (first[i] == second[i]){
        
        continue;

      }else{

        return false;
        break;

      }

  }
  
  return true;
}
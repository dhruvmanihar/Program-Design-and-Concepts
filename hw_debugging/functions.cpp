#include <iostream>

int Largest(int a, int b, int c) {
  int d = a;
  if (b > d) {
    d = b;
  }
  if (c > d) {
    d = c;
  }
  return d;
}

bool SumIsEven(int a, int b) {
  
  int total = a+b;
  if((total%2) == 0){
    return true;
  }else{
    return false;
  }
}

int BoxesNeeded(int apples) {
  
  if (apples > 0)
  {
    if (apples%20 == 0){
      return (apples/20);
    }
    else{
      return (1+ (apples/20));
    }
  }
  return 0;

}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  
  double aPer = double(A_correct) / double(A_total);
  double bPer = double(B_correct) / double(B_total);

  if (A_correct < 0 || A_correct > A_total){
    throw std::invalid_argument("");
  }
  if (A_total <= 0){
    throw std::invalid_argument(""); 
  }
  if (B_correct < 0 || B_correct > B_total){
    throw std::invalid_argument("");
  }
  if (B_total <= 0){
    throw std::invalid_argument("");
  }

  if (aPer > bPer){
    return true;
  }else{
    return false;
  }

}


bool GoodDinner(int pizzas, bool is_weekend) {

  if (pizzas >= 10 && pizzas <= 20 && (is_weekend == false)) {
    return true;
  }else if ((is_weekend) && (pizzas >= 10)) {
    return true;
  }else{
    return false;
  }

}


int SumBetween(int low, int high) {

  int value = 0;
  if (low > high){
    throw std::invalid_argument("");
  }else if (low == high){
    value = low;
    return value;
  }
  else if (abs(low) == abs(high)){
    return 0;
  }
  else if((high==0 || low == 0) && (low == INT32_MIN || high == INT32_MIN)){
    throw std::overflow_error("");
  }
  else if (low == -INT32_MAX && high == INT32_MAX-1){
    return -INT32_MAX;
  }else if (low == -INT32_MAX+1 && high == INT32_MAX){
    value = INT32_MAX;
    return value;
  }
  

  if (low == high){
    return low;
  }

  if (low < 0 && high > 0){
    int cancel = high * -1;
    if (low < cancel){
      high = cancel - 1;
    }
    if (low == cancel){
      return 0;
    }
    if (low > cancel){
      low = low * -1 + 1;
    }
  }

  for (int n = low; n <= high; n++) {
    if (value > INT32_MAX - n && n > 0){
      throw std::overflow_error("");
    }
    if (value < INT32_MIN - n && n < 0){
      throw std::overflow_error("");
    }
    value += n;
  }
  return value;

}

int Product(int a, int b) {

  if (a > 0 && b > 0){
    if (b > (INT32_MAX / a)){
        throw std::overflow_error("");
      }
    if (a > (INT32_MAX/ b)){
        throw std::overflow_error("");
      }
  }

  if (a < 0 && b < 0){
    if (b < (INT32_MAX / a)){
        throw std::overflow_error("");
      }
    if (a < (INT32_MAX / b)){
        throw std::overflow_error("");
      }
  }

  if (a > 0 && b < 0){
    if (b < (INT32_MIN / a)){
        throw std::overflow_error("");
      }
  }

  if (a < 0 && b > 0) {
    if (a < (INT32_MIN / b)){
        throw std::overflow_error("");
      }
  }



  if (a == 0 || b == 0){
    return 0;
  }

  return a * b;
}




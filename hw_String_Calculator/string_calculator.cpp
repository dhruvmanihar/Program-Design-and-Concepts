#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;



unsigned int digit_to_decimal(char digit) {
    
    if (digit == '1' || digit == '2' || digit == '3' || digit == '4' || digit == '5' || digit == '6' || digit == '7' || digit == '8' || digit == '9' || digit == '0') {
		int dtd = (int)digit - 48;
		return dtd;
	}
	else {
		throw std::invalid_argument("Invalid Argument");
	}
}

char decimal_to_digit(unsigned int decimal) {
    
    switch (decimal)
    {
    case 0:
        return '0';
        break;
    case 1:
        return '1';
        break;
    case 2:
        return '2';
        break;
    case 3:
        return '3';
        break;
    case 4:
        return '4';
        break;
    case 5:
        return '5';
        break;
    case 6:
        return '6';
        break;
    case 7:
        return '7';
        break;
    case 8:
        return '8';
        break;
    case 9:
        return '9';
        break;
    default:
        throw std::invalid_argument("Argument Invalid");
    }

}

int min(int a, int b) {

    if (a>b)
        return b;
    else 
        return a;


}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    
    if (num == "-00000" || num == "00000") {
		return "0";
	}
	
    if (num[0] == '-') {
		num[0] = '0';
		num.erase(0, min(num.find_first_not_of('0'), num.size() - 1));
		string second = "-";
		num.insert(0, second);
		return num;
	}
	else {
		num.erase(0, min(num.find_first_not_of('0'), num.size() - 1));
		return num;
	}
    
    
    /*
    int startIn;
    int endIn;

    if (num[0] == '-'){
        if (num[1] == '0'){
            startIn = 1;
        }else{
            return num;
        }
    }else{
        if (num[0] == '0'){
            startIn = 0;
        }else{
            return num;
        }
    }

    for (int i = startIn + 1; i < num.length(); i++){
    
        if (num[i] == '0'){
            continue;
        }else{
            endIn = i;
            break;
        }
    }

    if (num[0] == '-'){

        num = "-" + num.substr(startIn, (endIn - startIn));

    }else{

        num = num.substr(startIn, (endIn - startIn));

    }

    return num;

    */
}

string reverse(string str) {
	int n = str.length();

	for (int i = 0; i < n / 2; i++)
		std::swap(str[i], str[n - i - 1]);
	return str;
}

string add(string lhs, string rhs) {
    
    if (lhs.length() > rhs.length())
		std::swap(lhs, rhs);

	string str = "";

	int num1 = lhs.length();
    int num2 = rhs.length();

	lhs = reverse(lhs);
	rhs = reverse(rhs);

	int carryover = 0;
	for (int i = 0; i < num1; i++)
	{
		int sum = ((lhs[i] - '0') + (rhs[i] - '0') + carryover);
		str.push_back(sum % 10 + '0');
		carryover = sum / 10;
	}

	for (int i = num1; i < num2; i++)
	{
		int sum = ((rhs[i] - '0') + carryover);
		str.push_back(sum % 10 + '0');
		carryover = sum / 10;
	}
	if (carryover)
		str.push_back(carryover + '0');


	return reverse(str);
    return "";
}

string multiply(string lhs, string rhs) {

    string a = trim_leading_zeros(lhs);
    string b = trim_leading_zeros(rhs);
    
    bool aNeg = false;
    bool bNeg = false;

    if(a.at(0) == '-'){
        a.erase(0,1);
        aNeg = true;
    }
    if(b.at(0) == '-'){
        b.erase(0,1);
        bNeg = true;
    }

    bool isNeg = false;
    
    if(aNeg == true && bNeg == true){
        isNeg = false;
    }else if(aNeg==true){
        isNeg = true;
    }else if(bNeg==true){
        isNeg = true;
    }else{
        isNeg = false;
    }
    
    int aSize = a.length();
    int bSize = b.length();

    if(a == "0" || b == "0"){ 
      return "0"; 
      
    }else{
        string mult(aSize + bSize, 0); 

        for(int i = aSize - 1; i >= 0; i--){ 
            for(int j = bSize - 1; j >= 0; j--){ 
                int c = digit_to_decimal(a.at(i));
                int d = digit_to_decimal(b.at(j));
                int e = (c*d) + mult[i + j + 1]; 
                mult[i + j + 1] = e % 10; 
                mult[i + j] += e / 10;
            }
        } 

        int size = mult.size();
        string finalAns;
        for(int j = 0; j < size; j++){
            finalAns.push_back(decimal_to_digit(mult.at(j)));
        } 
        if(finalAns.at(0) == '0'){ 
            finalAns = finalAns.substr(1); 
        } 
        if(isNeg){
            finalAns.insert(0,"-");
        }
        return finalAns; 
    }
    return "";
}



string subtract(string lhs, string rhs)
{

    lhs = trim_leading_zeros(lhs);
     rhs = trim_leading_zeros(rhs);

     if (lhs == "0")
          return (rhs.at(0) == '-') ? rhs.substr(1) : "-" + rhs;
     if (rhs == "0")
          return lhs;

     bool is_l_neg = lhs.at(0) == '-', is_r_neg = rhs.at(0) == '-';
     if (is_l_neg && is_r_neg) {
          return add(rhs.substr(1), lhs);
     } else if (is_l_neg && !is_r_neg) {
          return "-" + add(lhs.substr(1), rhs);
     } else if (!is_l_neg && is_r_neg) {
          return add(lhs, rhs.substr(1));
     }

     int n = lhs.size(), m = rhs.size();

     bool swapped = false;

     if (n < m) {
          swap(lhs, rhs);
          swapped = true;
     } else if (n == m) {
          for (int i = 0; i < n; ++i) {
               if (lhs.at(i) < rhs.at(i)) {
                    swap(lhs, rhs);
                    swapped = true;
                    break;
               } else if (lhs.at(i) > rhs.at(i)) {
                    break;
               }
          }
     }

     n = lhs.size();
     m = rhs.size();

     string result = "";

     int carry = 0;
     for (int i = m - 1, j = n - 1; i > -1; --i, --j) {
        
          int sub = lhs.at(j) - rhs.at(i) - carry;
    
          if (sub < 0) {
               sub += 10;
               carry = 1;
          } else
               carry = 0;

        char sub2 = sub + '0';
        string sub3(1, sub2);

        result.insert(0,1,sub3);
     }


     for (int i = n - m - 1; i > -1; --i) {
          int sub = digit_to_decimal(lhs.at(i)) - carry;


          if (sub < 0) {
               sub = sub + 10;
               carry = 1;
          } else
               carry = 0;

          result.insert(0, 1, decimal_to_digit(sub));
     }

     result = trim_leading_zeros(result);
     result = swapped ? "-" + result : result;
 

     return result;

}


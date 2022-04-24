// Paul Kim, pbkim@usc.edu
// Used Sublime to bugfix alot ._.
#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <sstream>

using namespace std;

// Deleting all the comments for functions that pass checks 

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

// All constructors needed (3 given, 3 filled)

BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

BigInt::BigInt(int setbase){
  if(setbase < 2 || setbase > 36){
    throw InvalidBaseException();
  }
  
  base = setbase;
  isPositive = true;
}

// Deconstructor (why is it empty?)... but given don't touch
BigInt::~BigInt(){}

BigInt::BigInt(int input,int setbase){
  if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
  }
  
  base = setbase;
  
  if (input < 0) {
    isPositive = false;
    input = -1*input;
  }
  else {
    isPositive = true;
  }
  if (input == 0) {
    vec.push_back(0);
  }
  
  while (input != 0) {
    vec.push_back (input % setbase);
    input = input/setbase;
  }
}

BigInt::BigInt(const string &s, int setbase){
  if(setbase < 2 || setbase > 36){
      throw InvalidBaseException();
  }
  
  base = setbase;
  int index = 0;
  
  if (s[0] == '-') {
    isPositive = false;
    index++;
  }
  else {
    isPositive = true;
  }
  
  for (int i = s.length()-1; i >= index; i--) {
    if (s[i] >= 48 && s[i] <= 57) {
      vec.push_back(s[i] - 48); // 0-9 digits place
    }
    else {
      vec.push_back(s[i] - 55); // Everything else
    }
  }
}

BigInt::BigInt(const BigInt &b){
  base = b.base;
  isPositive = b.isPositive;
  vec = b.vec;
}

BigInt & BigInt::operator = (const BigInt &b){
  base = b.base;
  isPositive = b.isPositive;
  vec = b.vec;
  return *this;
}

//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

// Converts vector into string form.
string BigInt::to_string(){
  if (!vec.size()) {
    return "0"; // When vector is empty represents 0
  }
  
  string empty = ""; 
  
  if (isPositive == false) {
    empty += "-";
  }
  
  for (int i = vec.size()-1; i >= 0; i--) {
    if (vec[i] >= 0 && vec[i] <= 9) {
      empty += char(vec[i] + 48);
    }
    else {
      empty += char(vec[i] + 55);
    }
  }
  return empty;
}

int BigInt::to_int() const{
  int number = 0;
  for(int i = 0; i < (int)vec.size(); i++){
    number = number + (vec[i]*pow(base,i));
  }
  
  if(isPositive == false){
    number = number * -1;
	}
	if(number > INT_MIN && number < INT_MAX){
		return number;
	}
	if(isPositive == true){
		return INT_MAX;
	}
	
  return INT_MIN;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

int BigInt::compare(const BigInt &b) const{
  if(base != b.base){
    throw DiffBaseException();
  }
  
  if (isPositive && b.isPositive) { // If both positive
    if (vec.size () > b.vec.size()) {
      return 1;
    }
    else if (vec.size() < b.vec.size()) {
      return -1;
    }
    else {
      for (int i = vec.size()-1; i >= 0; i--) {
        if (vec[i] != b.vec[i]){
          if (vec[i] > b.vec[i]) {
            return 1;
          }
          else {
            return -1;
          }
        }
      }
    }
    return 0; // If equal
  }
  
  if (isPositive == false && b.isPositive == false) { // If both negative
    if (vec.size () > b.vec.size()) {
      return -1;
    }
    else if (vec.size() < b.vec.size()) {
      return 1;
    }
    else {
      for (int i = vec.size()-1; i >= 0; i--) {
        if (vec[i] != b.vec[i]){
          if (vec[i] > b.vec[i]) {
            return -1;
          }
          else {
            return 1;
          }
        }
      }
    }
    return 0; // If equal
  }
  
  if (isPositive && (b.isPositive == false)) {
    return 1;
  }
  
  return -1;
}

bool operator == (const BigInt &a, const BigInt &b){
  return !(a.compare(b));
}

bool operator != (const BigInt &a, const BigInt &b){
  return (a.compare(b));
}

bool operator <= (const BigInt &a, const BigInt &b){
  return a.compare(b) == -1 || a.compare(b) == false;
}

bool operator >= (const BigInt &a, const BigInt &b){
  return a.compare(b) == 1 || a.compare(b) == false;
}

bool operator > (const BigInt &a, const BigInt &b){
  return a.compare(b) == 1;
}

bool operator < (const BigInt &a, const BigInt &b){
  return a.compare(b) == -1;
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

BigInt operator + (const  BigInt &a, const BigInt & b){
  BigInt copy = a;
  copy += b;
  return copy;
}

// Addition Assignment Operator
const BigInt & BigInt::operator += (const BigInt &b){
  if(base != b.base){
    throw DiffBaseException();
  }
  if (isPositive != b.isPositive) {
    if (isPositive == true) {
      BigInt temp = b;
      temp.isPositive = true;
      *this -= temp;
      if (vec[0] == 0 && vec.size() == 1) {
        isPositive = true;
      }
    }
    else {
      isPositive = true;
      *this -= b;
      if (vec[0] == 0 && vec.size() == 1) {
        isPositive = true;
      }
      else {
        isPositive = !isPositive;
      }
    }
    return *this;
  }
  else {
    unsigned int Max = max(vec.size(), b.vec.size());
    int carry = 0;
    
    for (unsigned int i = 0; i < Max; i++) {
      int A = 0;
      int B = 0;
      
      if (i < vec.size()) {
        A = vec[i];
      }
      if (i < b.vec.size()) {
        B = b.vec[i];
      }
      
      int sum = A + B + carry;
      carry = sum/base;
      if (i < vec.size()) {
        vec[i] = sum % base;
      }
      else {
        vec.push_back(sum % base);
      }
    }
    if (carry > 0) {
      vec.push_back(1);
    }
    if (to_int() == 0) {
      isPositive = true;
    }
  }
    
  return *this;
}

BigInt operator - (const  BigInt &a, const BigInt & b){
  BigInt copy = a;
  copy -= b;
  return copy;
}

//Subtraction Assignment Operator
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if (isPositive != b.isPositive) {
      if (isPositive == true) {
        BigInt temp = b;
        temp.isPositive = true;
        *this += temp;
        if (vec[0] == 0 && vec.size() == 1) {
          isPositive = true;
        }
      }
      else {
        isPositive = true;
        *this += b;
        if (vec[0] == 0 && vec.size() == 1) {
          isPositive = true;
        }
        else {
          isPositive = false;
        }
      }
      return *this;
    }
    else {
      BigInt temp = *this;
      unsigned int Max = max(vec.size(), b.vec.size());
      int carry = 0;
    
      for (unsigned int i = 0; i < Max; i++) {
        int num = 0;
        int den = 0;

        if ((*this < b && isPositive) || (*this >= b && isPositive == false)) {
          if (i < vec.size()) {
            den = vec[i];
          }
          if (i < b.vec.size()) {
            num = b.vec[i];
          }
        }
        else {
          if (i < vec.size()) {
            num = vec[i];
          }
          if (i < b.vec.size()) {
            den = b.vec[i];
          }
        }
      
        int difference = num - den + base + carry;
        carry = difference/base - 1;
        if (i < vec.size()) {
          vec[i] = difference % base;
        }
        else {
          vec.push_back(difference % base);
        }
      }
      isPositive = (temp >= b);
    }
    int index = vec.size() - 1;
    while (vec[index] == 0 && index > 0) {
      vec.pop_back();
      index--;
    }
    return *this;
}

BigInt operator * (const  BigInt &a, const BigInt & b){
  BigInt copy = a;
  copy *= b;
  return copy;
}

// Multiplication Assignment Operator
const BigInt & BigInt::operator *= (const BigInt &b){
  if(base != b.base){
    throw DiffBaseException();
  }
  
  BigInt zero(0, base); // Base Case
  if (*this == zero || b == zero) {
    *this = zero;
    return *this;
  }
  
  bool sign;
  if (isPositive != b.isPositive) {
    sign = false;
  }
  else {
    sign = true;
  }
  
  if (b.vec.size() == 1 && b.vec[0] == 1) {
    isPositive = sign;
    return *this;
  }
  else if (vec.size() == 1 && vec[0] == 1) {
    vec = b.vec;
    isPositive = sign;
    return *this;
  }
  
  BigInt Sum (0,base);
  int carry = 0;
  int product = 0;
  
  for (unsigned int i = 0; i < b.vec.size(); i++) {
    string buffer (i, '0');
    BigInt temp(buffer, base);
    for (unsigned int j = 0; j < vec.size(); j++) {
      product = (b.vec[i]*vec[j]) + carry;
      carry = product / base;
      temp.vec.push_back (product % base);
    }
    if (carry > 0) {
      temp.vec.push_back(carry);
    }
    Sum += temp;
    carry = 0;
  }
  *this = Sum;
  isPositive = sign;
  return *this;
}

BigInt operator / (const  BigInt &a, const BigInt & b){
  BigInt copy = a;
  copy /= b;
  return copy;
}

// Division Assignment Operator
const BigInt & BigInt::operator /= (const BigInt &b){
  if(base != b.base){
    throw DiffBaseException();
  }
  if(b.vec.size() == 1 && b.vec[0] == 0){
    throw DivByZeroException();
  }
  
  BigInt quotient(base);
  BigInt remainder(base);
  divisionMain(b, quotient, remainder); // Call to function
  *this = quotient;
  return *this;
}

BigInt operator % (const  BigInt &a, const BigInt & b){
  BigInt copy = a;
  copy %= b;
  return copy;
}

// Modulus Assignment Operator
const BigInt & BigInt::operator %= (const BigInt &b){
  if(base != b.base){
    throw DiffBaseException();
  }
  if(b.vec.size() == 1 && b.vec[0] == 0){
    throw DivByZeroException();//divide by zero
  }
  
  BigInt quotient(base);
  BigInt remainder(base);
  divisionMain (b, remainder, quotient);
  *this = quotient;
  return *this;
}

//  Main function for the Division (/=) and Modulus (%=) operators.
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){
  BigInt div = b;
  div.isPositive = true;
  BigInt r(base);
  int x = 0, n = vec.size();
  for(int i = 0; i < n; i++){
    r.vec.insert(r.vec.begin(),vec[n-i-1]);
    if(i > 0 && r.vec[r.vec.size() - 1] == 0){
      r.vec.pop_back();
    }
    while(r.compare(div) != -1){
        r -= div;
        x++;
    }
    quotient.vec.insert(quotient.vec.begin(),x);
    x = 0;
    }
    remainder = r;

    while((quotient.vec[quotient.vec.size()-1] == 0) && quotient.vec.size() > 1){
      quotient.vec.pop_back();
    }
    if(((!isPositive && b.isPositive) || (isPositive && !b.isPositive)) && quotient.to_int() != 0) {
      quotient.isPositive = false;
    }
    else {
      quotient.isPositive = true;
    }
    if(!isPositive && remainder.to_int() != 0) {
      remainder.isPositive = false;
    }
    else {
      remainder.isPositive = true;
    }
}

BigInt pow(const  BigInt &a, const BigInt & b){
  BigInt temp = a;
  temp.exponentiation(b); // Call function
  return temp;
}

//  Exponentiation assignment function.
const BigInt & BigInt::exponentiation(const BigInt &b){
  if(base != b.base){
    throw DiffBaseException();
  }
  if(!b.isPositive){
    throw ExpByNegativeException();
  }
  	
  if(b.vec[0] == 0 && b.vec.size() == 1){
    BigInt one(1,base);
    *this = one;
  }
  else if(b.vec[0] == 1 && b.vec.size() == 1) {
    return *this;
  }
  else if((b.to_int() % 2 == 0) && b.vec.size() > 0){
    BigInt bCopy = b;
    return *this *= exponentiation(bCopy/BigInt(2,base));
  }
  else if((b.to_int() % 2 != 0) && b.vec.size() > 0){
    BigInt copy = *this;
    BigInt copyB = b;
    copyB -= BigInt(1,base);
    *this *= exponentiation(copyB/ BigInt(2,base));
    *this *= copy;
    return *this;
  }
  return *this;
}

BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){
  BigInt temp = a;
  temp.modulusExp(b, m);
  return temp;
}

//  Modulus Exponentiation assignment function.
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
  if(base != b.base || base != m.base){
    throw DiffBaseException();
  }
  if(!b.isPositive){
    throw ExpByNegativeException();
  }
  
  BigInt ans = BigInt(1,base);
	if (b.vec[0] == 0 && b.vec.size() == 1) {
		ans = *this % b;
  } 
	else if (b.vec[0]==1 && b.vec.size() == 1) {
		ans = *this % b;
  }
	else {
		BigInt temp = b;
		while (temp.compare(BigInt(0, base)) != 0){
			if (temp.vec[0] % 2 == 0){
				temp /= BigInt(2,base);
				*this *= (*this);
				*this %= m;
			}
			else {
				ans = (ans*(*this)) % m;
				temp -= BigInt(1,base);
			}
		}
	}
	*this = ans;
	return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************
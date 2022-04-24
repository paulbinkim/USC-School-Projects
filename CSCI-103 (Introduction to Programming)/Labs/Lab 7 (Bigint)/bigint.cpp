#include <string>
#include <vector>
#include <sstream>
#include "bigint.h"
#include <iostream>
#include <cmath>

using namespace std;

BigInt::BigInt(string s){ // Converts a string into digits (Constructor of object)
  for(unsigned int i=0; i< s.length(); i++) { // Iterates for the length of string
    char temp= s[s.length() - 1 - i];
    digitbank.push_back((int)(temp) - 48);
  }
}

string BigInt::to_string() { // Converts the digits of value, back into a string (Using StringStream). 
  string s;
  for(int i=digitbank.size()-1; i >= 0; i--){
    s += std::to_string(digitbank[i]); // CPP function I found online that helped.
  }
  return s;
}

void BigInt::add(BigInt b) {
  int tempcarry = 0;
  
  if (digitbank.size() > b.digitbank.size()) {
    while (b.digitbank.size() < digitbank.size()) {
      b.digitbank.push_back(0);
    }
  }
  
  if (digitbank.size() < b.digitbank.size()) {
    while (b.digitbank.size() > digitbank.size()) {
      digitbank.push_back(0);
    }
  }
  
  for (unsigned int i=0; i < digitbank.size(); i++) {
    digitbank[i] = digitbank[i] + b.digitbank[i];
    if (tempcarry > 0) {
      digitbank[i] += tempcarry;
      tempcarry--;
    }
    if (digitbank[i] >= 10) {
      digitbank[i] -= 10;  
      tempcarry++;
    }
  }
  
  if (tempcarry == 1) {
    digitbank.insert(digitbank.begin() + digitbank.size(), 1); // If in the scenario, a 1 is carried over after the loop, add 1 to the front.
  }
}
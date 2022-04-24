#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}
  
  try {
    ifstream ifile (argv[1]);
    
    int base;
    string d;
    string n;
    string secretcode;
    
    ifile >> base >> d >> n;
    
    BigInt first (d, base);
    BigInt second (n, base);
    
    string file = "";
    while (!ifile.fail()) {
      ifile >> secretcode;
      BigInt msg (secretcode, base);
      msg.modulusExp(first, second);
      file += (char)msg.to_int();
    }
    file.pop_back();
    cout << file << endl;
  }
  
  catch (const exception& e) {
    cout << e.what() << endl;
    return -1;
  }
  
	return 0;
}

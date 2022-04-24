#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int roll();
void printHistogram (int counts[]);

int roll () {
  int dice = rand() % 6 + 1;
  return dice;
}

void printHistogram (int counts[]) {
  for (int t = 4; t <= 24; t++) {
    cout << t << ":";
    int temp = counts [t-4];
    for (int z = 0; z < temp; z++) {
      cout << "X";
    }
    cout << endl;
  }
}

int main () {
  srand(time(0));
  
  int data[21] = {0};
  int sum = 0;
  int n;
  
  cout << "Enter the number of times to run the experiment" << endl;
  cin >> n;
  
  for (int z = 0; z < n; z++) {
    for (int i = 0; i < 4; i++){
      sum += roll();
    }
    switch (sum) {
      case 4: data[0]++; break;
      case 5: data[1]++; break;
      case 6: data[2]++; break;
      case 7: data[3]++; break;
      case 8: data[4]++; break;
      case 9: data[5]++; break;
      case 10: data[6]++; break;
      case 11: data[7]++; break;
      case 12: data[8]++; break;
      case 13: data[9]++; break;
      case 14: data[10]++; break;
      case 15: data[11]++; break;
      case 16: data[12]++; break;
      case 17: data[13]++; break;
      case 18: data[14]++; break;
      case 19: data[15]++; break;
      case 20: data[16]++; break;
      case 21: data[17]++; break;
      case 22: data[18]++; break;
      case 23: data[19]++; break;
      case 24: data[20]++; break;
    }
    sum = 0;
  }
  
  printHistogram(data);
  
  return 0;
}
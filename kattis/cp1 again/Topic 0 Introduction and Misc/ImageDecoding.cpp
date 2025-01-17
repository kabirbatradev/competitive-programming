// Author: Kabir batra
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  // the newline at the end of each image can be a prefix 
  // (set to \n) after one image
  string prefix = "";

  while (true) {
    // number of lines in this image
    int n; 
    cin >> n;
    if (n == 0) break;
    cin.ignore();

    cout << prefix;

    int firstStringLength = -1;
    bool error = false;

    // read each line
    for (int l = 0; l < n; l++) {
      
      // turn line into string stream so I can parse ints
      // and automatically stop when line ends
      string line;
      getline(std::cin, line);

      istringstream stringStream(line);

      // set "filled" to inital value
      char firstPixel;
      stringStream >> firstPixel;
      bool filled = firstPixel == '#';

      // go through ints and print string
      int totalStringLength = 0;

      int repeatCount;
      while (stringStream >> repeatCount) {
        totalStringLength += repeatCount;
        for (int i = 0; i < repeatCount; i++) {
          cout << (filled ? '#' : '.');
        }
        filled = !filled;
      } // end of reading line

      cout << "\n";

      // check for error in not matching string length
      if (firstStringLength == -1) {
        firstStringLength = totalStringLength;
      }
      else {
        if (firstStringLength != totalStringLength) 
          error = true;
      }

    } // end of reading entire picture

    if (error) {
      cout << "Error decoding image\n";
    }

    // answer is wrong if you print new line on the last image
    // cout << "\n"; 
    prefix = "\n";
  }

}
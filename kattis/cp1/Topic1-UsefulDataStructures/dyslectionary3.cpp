

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

// this time im just going to flip all the strings

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  vector<string> backwardStrings;
  int longest = 0;

  string in;

  // used file to test this
  // ifstream inFile;
  // inFile.open("file.txt");
  // while (getline(inFile, in)) {
  while (getline(cin, in)) {
    if (in == "") {
      sort(backwardStrings.begin(), backwardStrings.end());

      for (string s : backwardStrings) {
        string spaces(longest - s.length(), ' ');
        reverse(s.begin(), s.end());
        cout << spaces << s << "\n";
        
      }
      backwardStrings.clear();
      // backwardStrings.erase(backwardStrings.begin(), backwardStrings.end());
      longest = 0;
      cout << "\n";
    }
    else {
      // cout << "putting " << in << " in the dict!" << endl;
      reverse(in.begin(), in.end());
      backwardStrings.push_back(in);
      if (in.length() > longest) {
        longest = in.length();
      }
    }

    
  }
  sort(backwardStrings.begin(), backwardStrings.end());

  for (string s : backwardStrings) {
    string spaces(longest - s.length(), ' ');
    reverse(s.begin(), s.end());
    cout << spaces << s << "\n";
  }
  // inFile.close();


}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
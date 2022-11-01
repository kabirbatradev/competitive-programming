

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

#include <fstream>

using namespace std;

bool compareStringEnd(string s1, string s2) {

  int i = 0;
  while (true) {

    if (i == s1.length()) {
      // cout << "hit!";
      return true;
    }

    if (i == s2.length()) {
      // cout << "hit!";
      return false;
    }

    // if at i, they are the same character, then increase i
    if (s1[s1.length() - 1 - i] == s2[s2.length() - 1 - i]) {
      i++;
    }
    else { // they are not the same character? return the comparison
      return s1[s1.length() - 1 - i] < s2[s2.length() - 1 - i];
    }
    
  }

  // if (s1.back() == s2.back()) {
  //   return s1.back()-1 < s2.back()-1;
  // }
  // return s1.back() < s2.back();
  // return (i1.start < i2.start);
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);


  vector<string> dict;
  int longest = 0;

  string in;

  // used file to test this
  ifstream inFile;
  inFile.open("file.txt");
  while (getline(inFile, in)) {
  // while (getline(cin, in)) {
    if (in == "") {
      // empty line means new group!

      // cout << "begin sort!" << endl;

      sort(dict.begin(), dict.end(), compareStringEnd);
      sort(dict.begin(), dict.end(), compareStringEnd);

      // cout << "print everyting out!" << endl;
      // print it all out
      for (string s : dict) {
        string spaces(longest - s.length(), ' ');
        cout << spaces << s << "\n";
        
      }

      // cout << "clear the vector!" << endl;
      // reset
      // dict.clear();
      dict.erase(dict.begin(), dict.end());
      longest = 0;
      cout << "\n";
    }
    else {
      // cout << "putting " << in << " in the dict!" << endl;
      dict.push_back(in);
      if (in.length() > longest) {
        longest = in.length();
      }
    }

    
  }


  // cout << "print last bit before sorting" << endl;
  // for (int i = 0; i < dict.size(); i++) {
  //   cout << i << dict.at(i) << "\n";
  // }
  
  // cout << "sort!" << endl;
  // print the last one!
  sort(dict.begin(), dict.end(), compareStringEnd);
  // print it all out
  // string prefix = "";

  // cout << "print!" << endl;

  for (string s : dict) {
    string spaces(longest - s.length(), ' ');
    cout << spaces << s << "\n";
    // cout << prefix << spaces << s;
    // prefix = "\n";
    
  }
  inFile.close();


}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
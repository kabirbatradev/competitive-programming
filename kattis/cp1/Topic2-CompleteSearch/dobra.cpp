

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

// #define PI 3.1415926535897932384626433832795

int validity(vector<int> intString, int pos, int size) {
  // int vowelCount = 0;
  // int consCount = 0;
  // for (int i = pos - 2; i < pos + 3 && i < size; i++) {
  //   if (i < 0 || i == pos) continue;

  //   int num = intString.at(i);
  //   if (num == 0) vowelCount++;
  //   else if (num == 1) consCount++;
  //   else {
  //     // its underscore so we ignore.
  //   }
  // }

  // if (vowelCount )

  // ^doesnt work because the vowels and cons have to be in a row lol
  
  // start from pos, and check before and check after
  // just hard code it cuz its only 2 things in each dir
  
  
}

int getNumCombinations(bool hasL, vector<int> intString, int size) {
  
  // 0 is vowel
  // 1 is consonant
  // 2 is underscore

  // count the number of _ (which is 2)
  int numUnderscores = count(intString.begin(), intString.end(), 2);

  // base case:
  if (numUnderscores == 1) {
    
  }


  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  string input;
  cin >> input;


  // represnet string as bolean arraay

  // int intString[input.size()];
  vector<int> intString;
  intString.reserve(input.size());
  bool hasL = false;

  for (int i = 0; i < input.size(); i++) {
    if (input[i] == 'A' ||
        input[i] == 'E' ||
        input[i] == 'I' ||
        input[i] == 'O' ||
        input[i] == 'U') {
      intString.at(i) = 0;
    } else if (input[i] == 'L') {
        hasL = true;
    }
    else if (input[i] == '_') {
      intString.at(i) = 2;
    } else {
      intString.at(i) = 1;
    }
  }

  getNumCombinations(hasL, intString, input.size());



}




// pleasant: 
// no 3 sequential vowels, not 3 sequential consonants
// do contain at least one 'L'
// vowels = A, E, I, O, and U only
// at most 10 underscores in string
// string len 100 max
// return total number of pleasant words

// get the positions of all the _

// for every _, if there is no L, then one of them has to be L
// this is the outer for loop i think...
// if vowel works, then * 5 possibilities?
// if consonant works, then * 21
// if u used consonant, then u mark it? 
// makes me wanna do a recursive solution

// could represent the string as a boolean array
// then have an extra boolean that represents whether there is an L or not
// if there is not, pass that into the recursive function and it will gernerate 
// cases with and without L

// actually integer array


// for the acutal funciton
// how the numeber of _
// if is only one, then return 1 if it must be L
// and return 5 if vowel possible, return 21 if it must be 

// for every time a consonant is possible, 20 cases are not L, and 1 case is L
// if hasL, then all 21 are possible
// if not hasL, then only 20 are possible to continue notHasL
// and the last 1 will start thread with hasL is true



// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
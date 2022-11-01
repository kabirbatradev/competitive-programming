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

int totalCombinations = 0;

void getNumCombinations(bool hasL, vector<int> intString, int combinationsSoFar) {
  
  // 0 is vowel
  // 1 is consonant
  // 2 is underscore

  // ignore this
  // count the number of _ (which is 2)
  // int numUnderscores = count(intString.begin(), intString.end(), 2);
  // base case:
  // if (numUnderscores == 1) {
    
  // }


  // iterate through the string till we reach _
  // then fill it with something that is allowed, and call the function again


  int pos = 0;
  bool found = false;
  for (; pos < intString.size(); pos++) {
    if (intString.at(pos) == 2) {
      found = true;
      break;
    }
  }

  if (!found) {
    // we reached the end
    if (!hasL) {
      return;
    }

    totalCombinations += combinationsSoFar;
    return;
  }

  // int neighborVowels = 0;
  // int neighborCons = 0;
  // for (int i = pos - 2; i <= pos + 2; i++) {
  //   if (i == pos) {
  //     continue;
  //   }
  //   // out of bounds
  //   if (i < 0) continue;
  //   if (i >= intString.size()) continue;

  //   if (intString.at(i) == 0) {
  //     neighborVowels++;
  //   }
  //   else if (intString.at(i) == 0) {
  //     neighborCons++;
  //   }
  //   // count vowels, consonants, if underscore then dont count;
  // }

  bool vowelsAllowed = true;
  bool consAllowed = true;

  // before
  int vowel = 0;
  int cons = 0;
  if (pos - 2 >= 0) {
    if (intString.at(pos - 2) == 0) {
      vowel++;
    }
    else if (intString.at(pos - 2) == 1) {
      cons++;
    }
  }
  if (pos - 1 >= 0) {
    if (intString.at(pos - 1) == 0) {
      vowel++;
    }
    else if (intString.at(pos - 1) == 1) {
      cons++;
    }
  }
  if (vowel == 2) vowelsAllowed = false;
  if (cons == 2) consAllowed = false;

  // surrounding
  vowel = 0;
  cons = 0;
  if (pos + 1 < intString.size()) {
    if (intString.at(pos + 1) == 0) {
      vowel++;
    }
    else if (intString.at(pos + 1) == 1) {
      cons++;
    }
  }
  if (pos - 1 >= 0) {
    if (intString.at(pos - 1) == 0) {
      vowel++;
    }
    else if (intString.at(pos - 1) == 1) {
      cons++;
    }
  }
  if (vowel == 2) vowelsAllowed = false;
  if (cons == 2) consAllowed = false;

  // after
  vowel = 0;
  cons = 0;
  if (pos + 1 < intString.size()) {
    if (intString.at(pos + 1) == 0) {
      vowel++;
    }
    else if (intString.at(pos + 1) == 1) {
      cons++;
    }
  }
  if (pos + 2 < intString.size()) {
    if (intString.at(pos + 2) == 0) {
      vowel++;
    }
    else if (intString.at(pos + 2) == 1) {
      cons++;
    }
  }
  if (vowel == 2) vowelsAllowed = false;
  if (cons == 2) consAllowed = false;

  // cout << vowelsAllowed << " " << consAllowed << endl;


  if (vowelsAllowed) {
    // vowel is allowed

    vector<int> intStringCopy(intString);
    intStringCopy.at(pos) = 0;
    getNumCombinations(hasL, intStringCopy, combinationsSoFar * 5);
  }

  if (consAllowed && hasL) {
    // consonant is allowed and L is already there, so L is also allowed

    vector<int> intStringCopy(intString);
    intStringCopy.at(pos) = 1;
    getNumCombinations(hasL, intStringCopy, combinationsSoFar * 21);

  }

  if (consAllowed && !hasL) {
    // consonant is allowed and L is not already there

    // then we can add L, which is one combination and we set L to true

    // we can also not add L, which is 21 possibilities

    vector<int> intStringCopy(intString);
    intStringCopy.at(pos) = 1;
    getNumCombinations(!hasL, intStringCopy, combinationsSoFar);

  }

  if (consAllowed && !hasL) {
    // consonant is allowed and L is not already there

    // then we can add L, which is one combination and we set L to true

    // we can also not add L, which is 20 possibilities

    vector<int> intStringCopy(intString);
    intStringCopy.at(pos) = 1;
    getNumCombinations(hasL, intStringCopy, combinationsSoFar * 20);

  }

}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  string input;
  cin >> input;


  // vector of ints that represent the string
  // 0 is vowel
  // consonant (including L) is 1
  // _ is 2
  // if L, then hasL is true
  vector<int> intString;
  intString.reserve(input.size());
  bool hasL = false;


  for (int i = 0; i < input.size(); i++) {
    if (input[i] == 'A' ||
        input[i] == 'E' ||
        input[i] == 'I' ||
        input[i] == 'O' ||
        input[i] == 'U') {
      intString.push_back(0);
    } else if (input[i] == 'L') {
      hasL = true;
      intString.push_back(1);
    }
    else if (input[i] == '_') {
      intString.push_back(2);
    } else {
      intString.push_back(1);
    }
  }


  // goal is to get number of combinations recursively

  int numUnderscores = count(intString.begin(), intString.end(), 2);
  if (numUnderscores != 0) {

    int combinationsSoFar = 1;
    getNumCombinations(hasL, intString, combinationsSoFar);

    cout << totalCombinations << endl;

  }
  else {



    bool comboSpotted = false;
    
    int vowelCombo = 0;
    int consCombo = 0;

    for (int i = 0; i < intString.size(); i++) {
      if (intString.at(i) == 0) {
        vowelCombo++;
        consCombo = 0;
      }
      else if (intString.at(i) == 1) {
        vowelCombo = 0;
        consCombo++;
      }


      if (vowelCombo == 3) {
        comboSpotted = true;
        break;
      }
      if (consCombo == 3) {
        comboSpotted = true;
        break;
      }
    }

    if (hasL && !comboSpotted) {
      cout << 1 << endl;
    }
    else {
      cout << 0 << endl;
    }
  }

}




// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
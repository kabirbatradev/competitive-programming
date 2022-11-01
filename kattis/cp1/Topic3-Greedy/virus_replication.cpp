

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

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  string og;
  string virus;
  cin >> og >> virus;

  int i = 0;
  while (true) {
    if (i == og.size() || i == virus.size()) {
      break;
    }

    if (og[i] == virus[i]) {
      i++;
    }
    else {
      break;
    }
  }

  // cout << i << endl;

  int j = 0;
  while (true) {
    if ((og.size() - j == 0) || (virus.size() - j == 0)) {
      break;
    }

    if (og[og.size() - 1 - j] == virus[virus.size() - 1 - j]) {
      j++;
    }
    else {
      break;
    }
  }

  // i could be 3rd
  // j could be 3rd (from the last)
  // cattac
  // cateeetac
  // answer is the difference between viruslength - j and i

  // cateeetac
  // cattac
  // answer is 0 because thats still the difference

  // cout << j << endl;
  // cout << virus.size() << endl;

  cout << (virus.size() - j - i) << endl;


}

// this code does not work for something like
// CATCAT
// CAT

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
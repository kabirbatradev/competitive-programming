

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

struct dude {
  int num;
  int name;
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int t;
  cin >> t;

  vector<struct dude> favNumbers;
  favNumbers.reserve(1e6);

  for (int j = 0; j < t; j++) {
    int num;
    cin >> num;

    struct dude newDude = {num, j};

    favNumbers.push_back(newDude);
  }

  // for each favNumber, we delete the number we land on
  // so lets use for loop, and keep track of index
  // when we delete, then we make index 1 bigger (no because everything will shift over)
  // if index overflow, then we set to 0
  // if there is only 1 dude left, print out and break

  int index = 0;
  while (true) {
    if (favNumbers.size() == 1) {
      cout << favNumbers.at(0).name + 1 << "\n";
      break;
    }

    // cout << "index selected" << index << endl;
    index += favNumbers.at(index).num;

    index--; // compensation
    index = index % favNumbers.size();

    // cout << "erasing: " << favNumbers.at(index) << endl;

    favNumbers.erase(favNumbers.begin() + index);

    // cout << "new fav numbers" << endl;
    for (int i = 0; i < favNumbers.size(); i++) {
      // cout << favNumbers.at(i) << " ";
    }
    // cout << endl;

    if (index == favNumbers.size()) {
      index = 0;
    }

  }

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp


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

struct minion {
  int min;
  int max;
};

bool compareInterval(minion i1, minion i2) {
  return (i1.max < i2.max);
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  vector<struct minion> minions;

  int tc;
  cin >> tc;
  for (int j = 0; j < tc; j++) {
    int mint, maxt;
    cin >> mint >> maxt;
    struct minion m = {mint, maxt};
    minions.push_back(m);
  }

  sort(minions.begin(), minions.end(), compareInterval);

  int roomCount = 0;
  // change to while
  while (true) {

    if (minions.size() == 0) {
      break;
    }
    int roomTemp = minions.at(0).max;
    roomCount++;

    if (minions.at(0).min <= roomTemp) {
      minions.erase(minions.begin());
    }

    // delete all minions that have roomTemp within their range
    while (true) {
      if (minions.size() == 0) {
        break;
      }
      // if (minions.at(j).min <= roomTemp && roomTemp <= minions.at(j).max) {
      if (minions.at(0).min <= roomTemp) {
        minions.erase(minions.begin());
      }
      else {
        break;
      }
    }
  }

  cout << roomCount << endl;



}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
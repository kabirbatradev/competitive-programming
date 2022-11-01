

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

struct city {
  float perBox;
  int totalPeople;
  int boxesAssigned;

  bool operator<(const city &first) const {
    return perBox < first.perBox;
  }
};



int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  int numCities;
  int numBoxes;

  // priority_queue<int> population;

  while (true) {
    priority_queue<city> population;

    cin >> numCities >> numBoxes;
    if (numCities == -1 && numBoxes == -1) {
      break;
    }

    // cout << "read" << numCities << " " << numBoxes << endl;

    for (int i = 0; i < numCities; i++) {
      int ai;
      cin >> ai;
      struct city newCity = {ai, ai, 1};
      population.push(newCity);

      numBoxes--;


      // cout << "read the " << ai << endl;
    }

    // cout << "Exit loop" << endl;

    for (int i = 0 ; i < numBoxes; i++) {

      // cout << i << endl;

      struct city currentCity = population.top();
      population.pop();
      // cout << population.top().perBox << endl;
      // cout << currentCity.boxesAssigned << endl;
      currentCity.boxesAssigned++;
      currentCity.perBox = 1.0 * currentCity.totalPeople / currentCity.boxesAssigned;
      
      population.push(currentCity);
    }

    cout << ceil(population.top().perBox) << endl;


  }

  return 0;

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
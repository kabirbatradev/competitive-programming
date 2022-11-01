

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
using ll = long long;

// ll is kinda op pog use it ALWAYS

// #define PI 3.1415926535897932384626433832795

typedef struct sumAndIndex {
  ll sum;
  int index;
} sum;

bool compareSum(sum &s1, sum &s2) {
  return s1.sum < s2.sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int t;
  cin >> t;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  for (int tc = 0; tc < t; tc++) {
    string blank;
    getline(cin, blank);

    int n;
    cin >> n;

    int nums[n];
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    vector<sumAndIndex> sums;
    // sum temp = {0, -1};
    // sums.push_back(temp); // a sum of 0 to start at

    ll sumSoFar = 0;
    for (int i = 0; i < n; i++) {
      sumSoFar += nums[i];
      sum temp = {sumSoFar, i};
      sums.push_back(temp);
    }

    sort(sums.begin(), sums.end(), compareSum);

    // sum temp = {0, -1};
    // sums.insert(sums.begin(), temp);

    int p1 = 0, p2 = 0;
    int counter = 0;

    // +1 because we added an extra 0 element at the beginning
    // wait what this 0 thing is not needed right?
    // maybe it is.. 

    // instead of the 0 element (sus?), lets just check all the elements
    for (int i = 0; i < n; i++) {
      sum s = sums.at(i);
      if (s.sum == 47) {
        counter++;
      }
    }

    // brute force exceeds time limit
    for (int i = 0; i < sums.size(); i++) {
      for (int j = i + 1; j < sums.size(); j++) {
        if (sums.at(j).sum - sums.at(i).sum == 47) {
          counter++;
        }
      }
    }

    cout << counter << "\n";



  }

}

// lets create a 1d prefix sum
// sort it but also store its original position
// then do the pointers approach, but only increment the counter
// if the second pointer's original pos > first og pos

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
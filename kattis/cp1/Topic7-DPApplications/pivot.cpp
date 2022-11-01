

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


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  

  int n;
  cin >> n;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  int nums[n];

  for (int tc = 0; tc < n; tc++) {
    int num;
    cin >> num;
    nums[tc] = num;
  }

  int maxes[n];
  int maxSoFar = nums[0];
  for (int i = 0; i < n; i++) {
    if (nums[i] > maxSoFar) {
      maxSoFar = nums[i];
    }
    maxes[i] = maxSoFar;
  }

  int mins[n];
  int minSoFar = nums[n-1];
  for (int i = n-1; i >= 0; i--) {
    if (nums[i] < minSoFar) {
      minSoFar = nums[i];
    }
    mins[i] = minSoFar;
  }

  int counter = 0;
  for (int i = 0; i < n; i++) {
    if (nums[i] == maxes[i] && nums[i] == mins[i]) {
      counter++;
    }
  }

  cout << counter << endl;
  


}

// a number is a pivot if it is the biggest so far (from left)
// and the smallest so far (from right)

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
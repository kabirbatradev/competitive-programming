

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

    int p1 = 0, p2 = 0;
    int counter = 0;
    while (p1 < n && p2 < n) {
      // mistake: the while loop ends early when we have 
      // second pointer reach the end early?
      int sum = 0;
      sum = accumulate(nums + p1, nums + p2 + 1, 0);
      if (sum == 47) {
        counter++;
        p2++;
        p1 = p2;
      }
      else if (sum > 47) {
        p1++;
      }
      else if (sum < 47) {
        p2++;
      }

      if (p1 > p2) {
        p2 = p1;
      }
    }

    cout << counter << "\n";

  }
  


}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
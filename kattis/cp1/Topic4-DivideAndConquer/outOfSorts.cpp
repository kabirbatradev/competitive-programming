

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

// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  // int N = (int)1e5;
  

  ll n, m, a, c, x0;
  cin >> n >> m >> a >> c >> x0;

  vector<ll> nums;
  nums.reserve(n);

  ll previousX = x0;
  ll xi;

  for (int i = 1; i <= n; i++) {
    xi = (a*previousX + c) % m;
    previousX = xi;

    nums.push_back(xi);
  }

  // for (ll searchingFor : nums) {
  //   cout << searchingFor << " ";
  // }
  // cout << endl;

  // sort(nums.begin(), nums.end());

  int numFound = 0;
  // ll searchingFor = 1;
  for (ll searchingFor : nums) {
    // cout << i << " ";

  bool found = false;
  int mid, low, high;
  low = 0; high = n - 1;
  while (true) {
    // cout << low << " " << high << endl;
    if (low >= high) {
      found = nums.at(low) == searchingFor;
      break;
    }
    mid = (low + high) / 2;
    if (nums.at(mid) == searchingFor) {
      found = true;
      break;
    }
    if (nums.at(mid) > searchingFor) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  }

  // cout << found << endl;
  if (found) numFound++;

  }
  cout << numFound << endl;

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
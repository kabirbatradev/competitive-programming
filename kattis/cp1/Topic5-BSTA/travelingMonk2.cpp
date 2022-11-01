

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

struct interval {
  int height;
  int time;
  
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cout.precision(7);

  int a, d;
  cin >> a >> d;

  // int N = (int)1e5;
  vector<struct interval> ascending;
  vector<struct interval> descending;
  // nums.reserve(N);

  ll totalHeight = 0;

  ll totalTime1 = 0;
  ll totalTime2 = 0;

  for (int i = 0; i < a; i++) {
    int h, t; // height change, and time for that change
    cin >> h >> t;
    // h = 0 when rest and no extra height gained
    struct interval temp = {h, t};
    ascending.push_back(temp);

    totalHeight += h;
    totalTime1 += t;
  }
  
  for (int i = 0; i < d; i++) {
    int h, t; // height change, and time for that change
    cin >> h >> t;

    struct interval temp = {h, t};
    descending.push_back(temp);

    totalTime2 += t;
  }





}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
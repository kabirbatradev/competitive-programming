#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {
    string s; cin >> s;

    // count
    int lower = 0;
    int upper = 0;
    for (char c : s) {
      if ('a' <= c && c <= 'z') {
        lower++;
      }
      else {
        upper++;
      }
    }

    // print lower or upper depending on which count is higher
    if (lower >= upper) {
      for (char c : s) {
        cout << (char)tolower(c);
      }
    }
    else {
      for (char c : s) {
        cout << (char)toupper(c);
      }
    }
    cout << '\n';

  }
};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  int t; cin >> t;
  for (int i = 0; i < t; i++) 
    Solution s;
}
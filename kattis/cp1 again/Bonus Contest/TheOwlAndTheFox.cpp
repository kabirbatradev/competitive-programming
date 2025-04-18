#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {
    int n; cin >> n;

    string s = to_string(n);

    // iterate through chars from right
    // stop when we find a char that is not 0 
    // then decrement it
    // then print it
    int i;
    for (i = s.size()-1; i >= 0; i--) {
      if (s[i] != '0') {
        break;
      }
    }
    // found i such that char is not 0
    s[i]--;

    cout << stoi(s) << '\n';

  }
};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  int t; cin >> t;
  for (int i = 0; i < t; i++) 
    Solution s;
}

/*
given a number
n

find a number that is smaller (but close to n)
and its digits num to one less than n

ideas:
  get the sum of the digits

for any number with 1 through 9 as the last digit:
  just do the OG number - 1
  its very close, and sum of digits is one less!

but if the last digit is 0...
then just subtract the second last digit

simple!

*/
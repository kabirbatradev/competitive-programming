#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  int n, k;
  Solution() {
    cin >> n >> k;

    // BSTA
    int low = 0;
    int high = n;
    int minV = n;
    while (low <= high) {
      int mid = low + (high - low)/2;

      // if possible, try smaller
      if (canFunction(mid)) {
        minV = min(minV, mid);
        high = mid-1;
      }
      // not possible, try higher v
      else {
        low = mid+1;
      }
    }

    cout << minV << '\n';
  }

  // can he write n lines given some v?
  bool canFunction(int v) {
    int linesWritten = 0;

    double linesPerIteration = v;
    while (true) {
      // floor the double
      int linesFloored = linesPerIteration;

      // if its 0, he doesnt write more code
      if (linesFloored == 0) break;

      // add the lines written
      linesWritten += linesFloored;

      // update lines per iteration (double) for next iteration
      linesPerIteration /= k;
    }

    // true if we wrote enough lines
    return linesWritten >= n; 
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
n = number of lines of code we need to write
k is a coefficient

goal: find min v such that:

he writes v lines, then v/k lines, then v/k/k lines ...
until v/k/k/... = 0

BSTA: find the value of v 
  can function tells you: can he write n lines given some v?
  how to compute: just simulate summing v + v/k + ... until its 0
binary search for v
  possible because function is boolean monotonic

bounds for v:
0 means he writes 0 lines of code
n itself means he wrotes all n lines of code immediately
*/
#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {
    int n, q; cin >> n >> q;

    vector<vector<int>> xy(n, vector<int>(n, n)), 
    xz = xy, yz = xy;

    int counter = 0;
    for (int i = 0; i < q; i++) {
      int x, y, z; cin >> x >> y >> z;

      if (--xy[x][y] == 0) {
        counter++;
      }
      if (--xz[x][z] == 0) {
        counter++;
      }
      if (--yz[y][z] == 0) {
        counter++;
      }

      cout << counter << '\n';
    }
  }
};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  // int t; cin >> t;
  // for (int i = 0; i < t; i++) 
    Solution s;
}

/*
N by N by N cheese cube
repeatedly remove cells at x y z position

goal: at some state where some blocks are removed:
  how many N long lines of empty are there?

can represent entire cheese cube with N by N by N grid
true means has cheese
false means it was removed

efficient way of detecting if new line of empty cheese exists:
fix 2 variables, such as x and y
  for every z, position (x, y, z) has to be empty

if we are removing at pos x, y, z:
  xy[x][y]--; means that at the current x y, we removed a cell
    should be initialized to N
    then once its 0, that whole thing is empty and we increment count
  do for all combinations:
  xz[x][z]--;
  yz[y][z]--;
how do we initialize these?
  create xy, xz, and yz
  all 2d arrays from 0 to N
  all initial value N

note: no need to actually represent the cheese grid
*/
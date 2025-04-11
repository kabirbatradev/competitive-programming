#include <bits/stdc++.h>
#define int long long
#define INT_MAX LLONG_MAX
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {
    int n; cin >> n;

    vector<int> cans(n);
    for (int i = 0; i < n; i++) {
      cin >> cans[i];
    }

    sort(cans.begin(), cans.end(), greater<int>());

    int sum = 0;
    for (int x = 0; x < n; x++) {
      sum += (1 + cans[x] * x);
    }

    cout << sum << '\n';
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
shots needed to knock down can
 = 1 + difficulty * number of cans alr shot down
is greedy possible? can we sort cans by difficulty? 
  if we do high difficulty first, then they are multiplied less
  if we do low difficulty first, then high difficulty are multipled more
    which intuitively sounds bad
  is it always better to do high difficulty first?
  i tried a bunch of examples and couldnt find any counter examples
  PROOF BY SUBMISSION
  one case where it is better
    lets say x = 3
    and we have high difficulty of 10 up next
    if we swapped this with lower difficulty first (lets say 4)
    then we would add 3 * 4 now
    and maybe later down the line when x = 20, we would do 10 * 20
    this makes it 12 + 200
    compared to original 3*10 + 4*20 = 30 + 80
  another case 
    lets say x = 3
    and we have high difficulty of 10 up next
    if we swapped this with lower difficulty first (lets say 4)
    then we would add 3 * 4 now
    later, x = 4, we would do 10 * 4
    this makes it 12 + 40 = 52
    compared to original 3*10 + 4*4 = 30 + 16 = 46
  another case:
    lets say x = 100
    high difficulty = 10
    low difficulty = 4

    current case: 100 * 10 + 101 * 4 = 1404
    swap: 100 * 4 + 101 * 10 = 1410
    high difficulty first is still better
  another case:
    lets say x = 100
    high difficulty = 10
    much later: x = 200
    low difficulty = 4

    current case: 100 * 10 + 200 * 4 = 1800
    swap: 100 * 4 + 200 * 10 = 2400
    high difficulty first is still better
  another case:
    lets say x = 100
    high difficulty = 10
    much later: x = 200
    low difficulty = 9

    current case: 100 * 10 + 200 * 9 = 2800
    swap: 100 * 9 + 200 * 10 = 2900
    high difficulty first is still better

wait so i couldve done greedy all along??
maybe i should do a more mathematical proof

*/
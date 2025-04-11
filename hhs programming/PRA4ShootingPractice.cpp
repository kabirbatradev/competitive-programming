#include <bits/stdc++.h>
#define int long long
#define INT_MAX LLONG_MAX
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {
    int n; cin >> n;

    map<int, int> cans; // counts # of cans if duplicates
    for (int i = 0; i < n; i++) {
      int ai; cin >> ai;
      cans[ai]++;
    }

    cout << dfs(0, cans) << '\n';
  }

  map<map<int, int>, int> cache;

  int dfs(int x, map<int, int>& cansLeft) {

    // if no cans left, then return 0
    if (cansLeft.size() == 0) return 0;

    // if this map is in cache, just use that value
    auto it = cache.find(cansLeft);
    if (it != cache.end()) {
      return it->second; // return value stored in cache
    }

    // try every can next, and use the best answer
    int minShots = INT_MAX;

    // move keys into a vector so we dont modify the cansLeft map as we iterate through it
    vector<int> canVals; canVals.reserve(cansLeft.size());
    for (auto [canVal, count] : cansLeft) {
      canVals.push_back(canVal);
    }
    
    // use the vector for iteration
    for (int canVal : canVals) {
      int count = cansLeft[canVal];
      // if we ran out, then remove the key altogether
      if (count == 1) {
        cansLeft.erase(canVal);
      }
      else {
        // remove this can 
        cansLeft[canVal]--;
      }

      int shots = dfs(x+1, cansLeft) + (1 + canVal * x);
      minShots = min(minShots, shots);

      cansLeft[canVal]++; // bring back this can for next iteration
    }

    // update cache with answer before returning
    cache[cansLeft] = minShots;

    return minShots;
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
its still worse?
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
i should do a more mathematical proof

lets try brute force, and then add in DP if possible
brute force is try every order:
  all permutations
  dfs(x = knocked over, can durabilities left, current sum)
  try every can of can durabilities left

note the overlapping subproblems:
  certain permuations can have substrings that are the same 
  certain permutations can have the same "can durabilities left"
  so they would have the same optimal output
  we could cache: key = set of remaining cans
note: cannot use set, because we can have duplicate cans
*/
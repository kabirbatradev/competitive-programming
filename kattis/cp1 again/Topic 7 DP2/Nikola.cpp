// Author: Kabir batra
// It is okay to share my code for educational purposes
// Note: no gen AI was used for this problem

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  // cannot use map because cannot have pair of ints as key
  // instead using ordered map
  map<pair<int, int>, int> cache;

  int n; 
  vector<int> costs;

  Solution() {
    cin >> n; // num squares

    costs = vector<int>(n);
    for (int i = 0; i < n; i++) {
      cin >> costs[i];
    }

    // at position 1 (0 indexed) with jump 1, cost is cost at 1
    cache[make_pair(1, 1)] = costs[1];

    int runningMin = INT_MAX;
    for (int jumpSize = 0; jumpSize <= n; jumpSize++) {
      int result = topDown(n-1, jumpSize);
      runningMin = min(runningMin, result);
    }
    
    cout << runningMin << '\n';
  }


  // input: p = position, s = last jump size
  // output = total cost best case
  int topDown(int p, int s) {
    
    // base cases: out of bounds, or last jump size is invalid (0)
    if (p < 0 || p >= n || s <= 0) {
      return INT_MAX;
    }

    auto it = cache.find(make_pair(p, s));
    if (it != cache.end()) {
      return it->second; // return the cost of that map item
    }


    // try coming from forward jump, and coming from backward jump, and keep best one
    int fromBackward = topDown(p+s, s);
    int fromForward = topDown(p-s, s-1);

    int best = min(fromBackward, fromForward);
    if (best != INT_MAX) best += costs[p];
    cache[make_pair(p, s)] = best; // store in cache

    return best;

  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  Solution s;
}

/*
initial states: 
start at square 1
jump to square 2 (and add entry fee of square 2)
latest jump was size 1

now he has 2 options:
  jump back to square 1 (latest jump stays size 1)
  jump forward (latest jump was size 1, so we must jump size 2 and update latest jump size)

define a state:
  latest jump size
  current position
  current entry fee

dp table question: at a certain position, what is the minimum entry fee possible
dp input: 
  (latest jump size, current position)
dp output: 
  optimal entry fee to get to that state 

dp recursive relation conceptually:
  let s = latest jump size
  let p = position
  either we could have come from backward jump or forward jump
    backward jump: ask for future dp: dp[s][p + s]
    forward jump: ask for past dp: dp[s-1][p-s]
  then take the minimum cost and store it here

dp table initialization:
  can use cache (map), where if entry is not in cache, then it is not yet computed
  put first entry: at p = 1 (0 indexed) and s = 1, cost = costs[1]
  return int max if requesting for impossible case

can use top down appraoch (recursion) because its hard to keep prerequisite that certain states are already computed
can use bases cases like out of bounds (back or front)
*/

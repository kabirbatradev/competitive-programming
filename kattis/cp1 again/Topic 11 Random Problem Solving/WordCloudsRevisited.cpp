// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
#define int long long // replace all "int" with "long long"
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  int n, c; 
  vector<pair<int, int>> blocks;

  Solution() {
    cin >> n >> c;
    // n: number of entries
    // c: max width
    blocks.resize(n);

    for (int i = 0; i < n; i++) {
      int w, h; cin >> w >> h;
      blocks[i] = {w, h};
    }

    int result = completeSearch(0, 0, 0);
    cout << result << '\n';
  }

  map<tuple<int,int,int>, int> cache;

  // return minimized total height of rows
  // actually lets just return the minimized row height of current row and future rows
  int completeSearch(int currentBlockIndex, int currentRowHeight, int currentRowWidth) {
    if (currentBlockIndex == n) {
      return currentRowHeight;
    }

    // if in cache, then return result immediately
    auto it = cache.find({currentBlockIndex, currentRowHeight, currentRowWidth});
    if (it != cache.end()) {
      return it->second;
    }

    int bestCase = INF;

    // can either place this block on the right or place on a new row
    auto [currentWidth, currentHeight] = blocks[currentBlockIndex];

    // if it fits on this row, consider putting on this row
    bool noBrainerSameRow = false;
    if (currentRowWidth + currentWidth <= c) {
      if (currentRowHeight >= currentHeight) noBrainerSameRow = true;
      int result = completeSearch(currentBlockIndex+1, max(currentRowHeight, currentHeight), 
        currentRowWidth + currentWidth
      );
      bestCase = min(bestCase, result);
    }

    // if its not a no brainer to put on the same row, the consider putting on next row
    // no brainer if width fits and row height doesnt change
    if (!noBrainerSameRow) {
      // new row is just this block
      // old total of prev rows should include the "current row"
      int result = completeSearch(currentBlockIndex+1, currentHeight, 
        currentWidth
      );
      result += currentRowHeight; // factor in the cost of what was the current row
      bestCase = min(bestCase, result);
    }

    // add to cache before returning
    cache[{currentBlockIndex, currentRowHeight, currentRowWidth}] = bestCase;

    return bestCase;

  }
};

// using "signed" works around "int" being replaced with long long
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  Solution s;
}

/*
understanding the problem statement:
  for every block
    you can place it to the right on the current row
    or you can place it on the next row
  note blocks must be processed in order
  goal: minimize the total of all the max heights of each row

if you place it on the right, 
  you actually cannot if it doesnt fit in the max width
  it might increase that row's max height
  its a no brainer to put it on the same row if it doesnt increase the max height (and it fits)
if you place it on new row
  u dont affect the previous row max height

simple solution:
  basically DFS/complete search, where each state has 2 options forward
  basic pruning:
    have to start new row if max width full
    should always go on same row if doesnt make max height worse

state information:
  total row height sum so far
  height of current row
  current block index (being processed)
output:
  optimal minimum total height if we make optimal decisions from there onward


do we need caching?
  there could be overlapping subproblems
    if total row height so far is same
    and height of current row is same
    and current block index is same
cache would be a map from 3 int tuple to one int

It TLEs even with the cache
that means DP doesnt work? we have to do greedy?

better cache: only cache:
  currentBlockIndex
  currentRowHeight
  currentRowWidth
no need to cache with "total row height so far" because all future decisions made are the same so its not a defining state variable
  now my solution detects more overlapping subproblems
it passes yay!
*/
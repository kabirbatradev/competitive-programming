// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  
  int n, h; cin >> n >> h; // length and height

  bool fromBottom = true;
  // from bottom, want to consider shortest ones first (min heap)
  priority_queue<int, vector<int>, greater<int>> pqBottom; 
  priority_queue<int> pqTop; // largest sizes first
  for (int i = 0; i < n; i++) {
    int size; cin >> size;
    if (fromBottom) {
      pqBottom.push(size);
    }
    else {
      pqTop.push(size);
    }
    fromBottom = !fromBottom;
  }
  
  int minObstacles = pqBottom.size() + pqTop.size(); // impossible case: all walls were hit
  int numSolutions = 0;
  
  int obstacles = pqBottom.size(); // assume we hit all bottom obstacles at height = 1 (lowest)
  // 1 through h inclusive
  for (int height = 1; height <= h; height++) {
    // if height is higher than some obstacle size, then its no longer an obstacle
    while (!pqBottom.empty() && height > pqBottom.top()) {
      obstacles--;
      pqBottom.pop();
    }
    // h - size = the point right under "from top" obstacle
    // if height > that point right under, then we no collide with obstacle
    while (!pqTop.empty() && height > (h-pqTop.top())) {
      obstacles++;
      pqTop.pop();
    }

    // new best!
    if (obstacles < minObstacles) {
      minObstacles = obstacles;
      numSolutions = 1;
    }
    // same as prev best
    else if (obstacles == minObstacles) {
      numSolutions++;
    }
    // dont care if this case is worse (do not change the running best)

    // example print statement for debugging:
    // printf("at height = %d, # obstacles = %d\n", height, obstacles);
  }

  cout << minObstacles << " " << numSolutions << '\n';
}

/*
what if we tried every single height (iterate through height being considered)
at the bottom height, 
  we go through all "from floor" 
  and none "from ceiling"
from the next height:
  we not go through some of the ones "from floor". here, we can greedily only consider the shortest ones from floor first
  and we might now go through some "from ceiling". greedily consider the longest new ones
how to efficiently greedily consider from floor and ceiling:
  sort them 
  or use a priority queue (same runtime)
make sure to invert the height for the "from ceiling"
*/
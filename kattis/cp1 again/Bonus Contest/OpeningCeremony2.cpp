#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {


  vector<int> heights;

  int n; 
  Solution() {
    cin >> n;

    heights.resize(n);
    for (int i = 0; i < n; i++) {
      // int h; cin >> h;
      cin >> heights[i];
    }
  
    // max first!
    sort(heights.begin(), heights.end(), greater<int>());

    int best = n;
    // try destroying every possible # heights from tallest first
    // i is number of buildings destroyed
    for (int i = 0; i < n; i++) {
      int buildingsDestroyed = i;
      // if i = 0, then 0 buildings destroyed, so we need to destroy height[0] layers first building
      // if i = n-1, almost all buildings destroyed
      int layersToDestroy = heights[i];
      best = min(best, buildingsDestroyed + layersToDestroy);
    }

    // extra case: no building is alive
    // default best = n


    cout << best << '\n';
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
list of building heights 
goal: remove all blocks with minimum charges

charge:
  destroy entire building
  destroy 1 level in all buildings
    just destroy the bottom level
    it decreases the height of all buildings 

is this greedy?

complete search:
  try destroying all buildings one by one
  try destroying every layer one by one
  or some combination of the 2

interesting idea:
  there might be one building super tall, so u destroy that one building
  then 100 buildings that are very short, so u destory them all layer by layer

greedy says:
  go for bang for buck every time
  if theres a super tall building, and it allows u to destroy more than u could by destroying any one layer, then destroy that one tall building

what does dp say:
  at some state, we have a certain list of buildings left

  max height tells us max slices we could do (upper bound)
  # buildings tells us max buildings we need to destory one by one
  how do we do some combination of this?

  we could sort the list of remaining buildings
  then go both directions complete search style (destroy tallest building greedily)
  and cache based on the list of remaining building heights


instead of using vector to store heights

use sorted deque
or sorted array and 2 pointers saying how far we have gotten in each dir

pop from right side to kill tallest building
  or just store # tall buildings destroyed
  aka a pointer from the right
store a value "levels destroyed" and pop from left side if enough levels are destroyed
  or a pointer from the left



TLE means we have to cache better or do greedy

is 2 pointer possible?
left pointer = left building small building
right pointer = tall building

push left if its better to destroy a layer
better to destroy a layer if 

idk


what if we cached less stuff
dont cache left pointer? just have levels destroyed?
but then we have to find it

what if we only have left pointer!
then we can assume levels
always jump to the next level too!

still TLE sadge

greedy means we know which pointer to push every time
push left if destroying that many layers leads to destroying more buildings than # layers destroyed 

can we BSTA for # layers to destroy
if we destroy x layers
then that destroys x buildings
so we have n - x buildings left, and thats how many destroy buildings we need to do

destroy more layers
means n-x gets smaller

try every # of destroy layers


*/
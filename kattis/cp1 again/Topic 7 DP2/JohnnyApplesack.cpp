// Author: Kabir Batra
// It is okay to share my code for educational purposes
// Note: no gen AI was used for this problem

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  int n, k;

  Solution() {
    cin >> n >> k;
    // n apples, k size bag

    // binary search for farthest distance we can travel
    // where # apples needed is less than how many we have

    int farthestDistance = 0;
    int low = 0; // min distance walked is 0 
    int high = n; // max disatnce walked is <= apples for sure
    while (low <= high) {
      int mid = low + (high - low) / 2;

      // how many apples are needed to reach position mid with 0 apples in hand?
      int applesNeeded = howManyApplesNeeded(mid, 0);
      if (applesNeeded == n) {
        farthestDistance = mid;
        break;
      }
      // need too many apples, try shorter distance
      else if (applesNeeded > n) {
        high = mid-1;
      }
      // didnt use all apples, successfully reached distance
      else {
        farthestDistance = mid;
        low = mid+1;
      }
    }

    // off by one because farthestDistance = # tolls we can cross
    // but problem wants the position of the first toll
    // that he cannot cross
    cout << (farthestDistance+1) << '\n';


    // for (int i = 0; i <= 8; i++) {
    //   cout << i << ": " << howManyApplesNeeded(i, 0) << endl;
    // }
    // cout << "\n\n";
    // for (int i = 0; i <= 8; i++) {
    //   cout << i << ": " << howManyApplesNeeded(i, 1) << endl;
    // }
    // cout << "\n\n";
    // for (int i = 0; i <= 8; i++) {
    //   cout << i << ": " << howManyApplesNeeded(i, 2) << endl;
    // }
    // cout << "\n\n";

    // cout << "0 4 case" << ": " << howManyApplesNeeded(0, 4) << endl;
    // cout << "1 3 case" << ": " << howManyApplesNeeded(1, 3) << endl;

    // at i = 2, want 2 apples, should cost 4

  }

  map<pair<int, int>, int> cache;

  // position is # tolls passed
  // count is # apples that we want at this position
  int howManyApplesNeeded(int pos, int count) {
    // we can basically have unlimited apples at position 0
    // because no paying for tolls
    if (pos == 0) {
      return count;
    }
    // count = 0 means count = 1 for prev position
    // this probably would have been accommodated for anyway
    if (count == 0) {
      return howManyApplesNeeded(pos-1, 1);
    }

    // check cache
    auto it = cache.find(make_pair(pos, count));
    if (it != cache.end()) {
      return it->second; // second is value of (key,value)
    }

    // running min:
    int leastApplesUsed = INT_MAX;
    // try having up to k apples in previous position to bring forward
    // f means # apples brought forward
    for (int f = 1; f < k; f++) {
      if (count - f < 0) break; // dont consider negative counts
      
      int applesUsed = 0;

      // in this case, we dont want to waste apples on bringing 0 apples to pos
      // so we just dont add that
      if (count - f == 0) {
        applesUsed = howManyApplesNeeded(pos-1, f+1);
      }
      else {
        applesUsed += howManyApplesNeeded(pos, count - f);
        // at previous position, we need 1 + f apples 
          // then we pay 1 apple
          // and end up bringing f apples forward
        applesUsed += howManyApplesNeeded(pos-1, f+1);
      }

      // update running min
      leastApplesUsed = min(leastApplesUsed, applesUsed);
    }

    // update cache
    cache[make_pair(pos, count)] = leastApplesUsed;

    return leastApplesUsed;
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
how far can the apple man travel?
he has n apples
and a sack that can hold k at a time
but at every km, he has to pay an apple if he is walking forward
  doesnt have to pay if walking backward
he can drop apples at places to pick them up later and use them to travel farther
his goal is to use his apples to go as far as he can, paying on the way

greedy: 
fill up the sack as much as possible, and go as far as you can
then come back, get the remaining apples, and again, go as far as you can
issue: you will never go farther than how much u can hold in a sack
  you can never take advantage of the fact that you can place apples down if you always use them all up


any ideal strategies? (something that is always right to do)
  maybe: fill up the sack as much as possible
    pros: results in going farther, or having more apples to drop off somewhere
    cons: what if we go back to get more apples, but now we can't come back to where we dropped off our last bit of apples
      because we didnt have enough left at home?
      we would have had to carefully drop off our last bit of apples just in range of where we could go for the next trip i guess?
what would a human do?
  lets think backwards: what would the optimal state of placed apples look like at the end right before the final trip from home?
  walk forward with k apples until you run out 
  there is a pile of k apples on the ground right there
  repeat
  eventually, there are no more piles of apples that you set up for yourself
  something like that maybe?
But: for every set of k apples on the ground, you need to do the entire process to put those k apples there
  to get 4 apples at pos = 0, do nothing
  to get 4 apples at pos = 4, its not obvious
  to get 4 apples at pos = 8, first get 4 apples at pos=4, and then...
    repeatedly do this until you have enough apples to do the process of bringing 4 apples to 4
    and then start from position 4 with that many apples in hand, and use the procedure to place 4 apples at 8
  this might be suboptimal though...

brute force/complete search?
  from the start point, try picking up every combination of apples
  and try dropping every combination of apples on the way forward
  then try walking back to every position that has apples
  and consider moving them forward or using them
  maybe just go all the way back? or back to the latest apples that still exist on the route?
this seems super complicated... how can we simplify this?

what if we created a function:
  input:
    want to get to a certain position
    want to have certain number of apples on the ground
      after that position (if pos = 1, the apples are between 1 and 2)
  output: how many apples you need to do this
and this function computes this recursively
then we just call the function on some far distance, with 0 apples
  binary search for the farthest position that we can do 

how does this function work though?
  can be similar to complete search, but saves work (cache)
  base case: 
    to get to position 0 with 0 apples in hand, we need 0 apples
      position 0 means anywhere between 0 and 1; no toll was crossed
  more base cases:
    to get to pos=0 with x <= k apples, we need x apples
      again, no toll, and we can carry that many apples in the sack


reevaluating from dp lens:
  state: 
    (position = # tolls crossed, count = # apples on the ground)
  dp at state: 
    # apples needed to achieve this state (optimally used)
  recursive relation concept:
    how could we have gotten to this state?
    1) we used to have less apples at this position, and we
      brought the remaining needed somehow...
      maybe we had a bunch of apples in the position right before,
      and we were also just there, and we picked them up, and
      we paid one apple but had a bunch now in hand to bring 
      to the new position
      issue: our current state representation cannot
        describe the idea of having more apples at another position...
      potential solution: instead of using state to say that apples exist
        at a certain earlier position, we can call the function to ask
        what it would take to have that many apples at some position, and 
        then work with that directly
    ... thats pretty much it
  lets be more specific:
    goal is position and count
    one case:
      make 2 requests:
        function(position, count-1)
        function(position-1, 2)
      first request:
        gives as count-1 apples at position
      second request: 
        gives us 2 apples at the prev position
        then we walk to next position, paying 1 apple
        now we have an extra apple
      with both requests, we have achieved desired position and count
    another case:
      make 2 requests, but slightly different
        function(position, count-2)
        function(position-1, 3)
      first request: (note, skip this if count is just 1)
        same as previous case really
      second request: 
        at prev position, want to have 3 apples, so we can bring 2 forward
      alternative second request:
        function(position-2, 4)
        at 2 positions ago, have 4 apples, and then pay 2 tolls to bring 2 forward
      is the alternative second request equivalent?
        if we did second request instead, and that called its own 
        request to have apples back 1 from there, would it result in the same total apples used?
        that would be like:
          function(position-2, 4)
          to get us 3 apples at position-1
        so they are equivalent! it is equivalent to request
          more from further back vs request less from closer
        no need to make requests from positions further back than 1
    note that we can ask for larger amounts of apples from previous position
    what is the max we can request from prev position?
      it is k: function(position-1, k)
      then we walk forward one, and have k-1 apples
      note that if we requested k+1, we would not be able to carry all of them
so what is the exact recurrence relation:
  dp[position, count] = 
    consider every c from count-1 to count-k+1
    count-1 means: 
      get dp[position, count-1]
      get dp[position-1, 2] // bc need 2 apples to add final apple
    count-k+1 means:
      get dp[position, count-k+1]
      get dp[position-1, k] // bc u end up bringing k-1 apples
  in dp current, store the combo that used least number of apples!
  make sure to do bound checks
    as we iterate through counts, if count-x is negative, then stop

  seems to be edge case:
    if count = 0, then 
      we really just want dp[position-1, 1]
      we just want 1 apple at previous position to take that one step forward
  

woohoo! i think thats at least the essense of it


*/
// Author: Kabir Batra
// It is okay to share my code for educational purposes
// Note: no gen AI was used for this problem

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  
  int n, k; cin >> n >> k;


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
  

*/
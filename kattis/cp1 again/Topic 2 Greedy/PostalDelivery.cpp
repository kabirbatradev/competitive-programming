// Author: Kabir batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Solution {
  Solution() {
    int n;
    cin >> n;
    int capacity;
    cin >> capacity;

    // split into places with negative vs positive x (position).
    // we can run the same algorithm on them separately
    vector<pair<int, int>> negatives;
    vector<pair<int, int>> positives;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      int letters;
      cin >> letters;
      if (x < 0) {
        negatives.push_back(make_pair(-x, letters));
      } else {
        positives.push_back(make_pair(x, letters));
      }
    }

    // reverse to get them into sorted order (positives are already sorted)
    reverse(negatives.begin(), negatives.end());
    ll total = simulate(negatives, capacity) + simulate(positives, capacity);
    cout << total << '\n';
  }

  ll simulate(vector<pair<int, int>>& distAndLetters, int capacity) {
    ll total = 0;
    while (!distAndLetters.empty()) {
      // go to the last one, and deliver as much as possible
      int inTruck = capacity;

      auto p = distAndLetters.back();
      int x = p.first;
      // we are traveling to the farthest location and back
      total += 2 * x;

      while (inTruck > 0 && !distAndLetters.empty()) {
        auto& p = distAndLetters.back();
        int& letters = p.second;

        // if cant fully satisfy the farthest one
        if (letters > inTruck) {
          letters -=
              inTruck;  // note we are editing letters directly (in the array)
          inTruck = 0;
        } else {
          // can delete the last element = delete the last location
          distAndLetters.pop_back();
          inTruck -= letters;

          // now inTruck might still be > 0
          // so in the next iteration, we will grab the next farthest
          // location and give letters to them
        }
      }

      // now inTruck is 0 or we ran out of locations
      // in the next iteration, we will have a new farthest place and
      // total will be increased
    }
    return total;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  Solution s;
}

/*
always deliver to the farthest one first
if have remaining space, then deliver to closer one "while going on the way"
if a closer one becomes 0 while on the way, then dont need to go back (remove
from list)
*/

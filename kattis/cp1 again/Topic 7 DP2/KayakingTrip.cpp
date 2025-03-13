// Author: Kabir batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  vector<int> speedFactors;
  int b, n, e; 
  int sb, sn, se; 

  vector<pair<int, pair<int, int>>> strengthCombinations; // strength --> (strength type index, strength type index)
  
  Solution() {
    cin >> b >> n >> e;
    // # beginners, normal, experienced
    cin >> sb >> sn >> se;
    // strengths of each participant

    // what if we stored every combination of speeds in sorted order
    strengthCombinations.push_back({sb + sb, {0, 0}});
    strengthCombinations.push_back({sb + sn, {0, 1}});
    strengthCombinations.push_back({sn + sn, {1, 1}});
    strengthCombinations.push_back({sn + se, {1, 2}});
    strengthCombinations.push_back({se + se, {2, 2}});
    sort(strengthCombinations.begin(), strengthCombinations.end());

    int m = (b + n + e) / 2; // # kayaks

    speedFactors = vector<int>(m);

    for (int i = 0; i < m; i++) {
      cin >> speedFactors[i];
    }

    sort(speedFactors.begin(), speedFactors.end());

    // binary search using can function:
    int low = 0;
    int high = 100'000 * 2 * 1000; // max c, max s
    int best = low;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      bool success = canFunction(mid);
      // if we can succeed with this speed lower bound, then try 
      // a higher minimum
      cout << "success = " << success << '\n';

      if (success) {
        best = max(best, mid);
        low = mid+1;
      }
      else {
        high = mid-1;
      }
    }

    cout << best << '\n';
  }

  // assign worst kayak with strongest people
  bool canFunction(int speedLowBound) {
    printf("trying low bound = %d\n", speedLowBound);
    vector<int> counts = {b, n, e};
    vector<int> strengths = {sb, sn, se};
    for (int c : speedFactors) {
      // v = c * (s1 + s2)

      // go through combinations of strength in sorted order
      bool foundSolution = false;
      for (int i = 0; i < strengthCombinations.size() && !foundSolution; i++) {
        auto [sum, indeces] = strengthCombinations[i];

        // we might have found a potential solution (if there enough people of those strengths left)
        if (c * sum >= speedLowBound) {
          auto [i, j] = indeces;
          counts[i]--;
          counts[j]--;
          if (counts[i] >= 0 && counts[j] >= 0) {
            foundSolution = true;
            continue; // breaks out of the loop
          }

          // otherwise, revert counts and try different in next iteration
          counts[i]++;
          counts[j]++;
        }
      }
      // if we tried all strengths but we dont have ppl its not strong enough, we fail
      if (!foundSolution) {
        return false;
      }
    }

    // if we got through all kayaks without failing, yay
    return true;
  }
};

int main() {
  // std::ios::sync_with_stdio(false);
  // cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  Solution s;
}

/*
# kayaks = 1/2 * sum of # beginners, normal, experienced
3 corresponding different possible strengths of people
2 ppl per kayak
every kayak has a speed factor 'c'
goal: optimize max speed of slowest kayak
  speed = c * (strength of first person, strength of second person)

brute force: 
  try assigning every combination of 2 people on every kayak

how would a human do it?
greedy:
  put the strongest people on the worst kayaks
  but then if you use the 2 strongest people on the worst kayak,
    the second kayak is cooked if its the same speed
    so u would rather want to split up the strongest people among the worst kayaks

another greedy approach:
  split up the strongest people among the worst kayaks as evenly as possible? 
  not sure how to make this optimal...

BSTA:
  can function: given a minimum speed that we have to do better than
    can we greedily find an assignment of people to kayaks?
  assign the worst kayaks with the weakest 2 people that are just strong enough to meet the worst case speed
    dont need to binary search for them and worry about removing from a list
    there are only 3 strengths! so 3 counts
  exchange arg: then we always have better stronger people for other kayaks (anything else is worse)
  Q: how do we decide between using worst and best vs 2 middles?
    pick the option that is closer to the worst speed, because save better people/better combination for future trains

how would a human do brute force with caching (aka dp)? 
  i still lean towards BSTA still because im trying to find the maximum min
  are there any overlapping subproblems?
    # remaining people to consider working with?, or maybe the specific list of people
      but actually its just 3 numbers, the counts of each strength type remaining
    # kayaks that are unassigned?, or maybe the specific list of kayaks?
    this seems too complex, and makes BSTA look simpler
  need something more brute force-like i guess...
    states in the complete search are the same though



  
*/
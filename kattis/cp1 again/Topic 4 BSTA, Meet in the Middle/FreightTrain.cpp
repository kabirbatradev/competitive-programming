#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  Solution() {
    int T; cin >> T;

    for (int i = 0; i < T; i++) {
      int n, w, l; cin >> n >> w >> l;
      // n: number of total wagons
      // w: number of wagons that need to be delivered
      // l: number of trains

      // important wagons given in ascending order (no need to sort)
      vector<int> wagonNumbers(w);
      for (int j = 0; j < w; j++) {
        cin >> wagonNumbers[j];
      }

      // BSTA
      // minimize longest len train needed
      // bounds: 0 to n
      int low = 1; 
      int high = n;
      int best = high;
      while (low <= high) {
        int mid = low + (high - low)/2;
        // if its possible, try smaller
        if (canFunctionV2(mid, wagonNumbers, n, l)) {
          best = min(mid, best);
          high = mid-1;
        }
        // otherwise try longer
        else {
          low = mid+1;
        }
      }

      cout << best << '\n';
    }
  }
  
  // is it possible to send trains such that the longest one for delivery <= longestLenTrain
  bool canFunctionV2(int longestLenTrain, vector<int>& wagonNumbers, int n, int l) {
    // greedy approach:
    // keep making trains of longest length
    // can go past longest length if the next important wagon is very far
    int numTrainsUsed = 1;
    ll trainStart = 1; // 1 indexed numbering
    bool hasImportantWagon = false;
    for (int i = 0; i < wagonNumbers.size(); i++) {
      ll trainEnd = trainStart + longestLenTrain-1; // inclusive
      if (wagonNumbers[i] <= trainEnd) {
        // this wagon is covered by current train
        hasImportantWagon = true;
        continue; 
      }
      // otherwise:
      // have to make a new train for this wagon
      // check if previous train had an important wagon
      // if not, then that train can be very long and cover the whole gap
      if (!hasImportantWagon) {
        trainStart = wagonNumbers[i];
        numTrainsUsed++;
        hasImportantWagon = true;
        continue;
      }
      // otherwise start a new train right after the previous one, and do i--
      trainStart = trainEnd+1;
      numTrainsUsed++;
      hasImportantWagon = false;
      i--;
    }

    // acount for last few wagons if they exist:
    ll trainEnd = trainStart + longestLenTrain-1; // inclusive
    if (trainEnd >= n || !hasImportantWagon) {
      // included all the last wagons
    }
    else {
      numTrainsUsed++;
    }

    // true if we used # trains less than what we have
    return numTrainsUsed <= l;

  }

};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(10);
  Solution s;
}
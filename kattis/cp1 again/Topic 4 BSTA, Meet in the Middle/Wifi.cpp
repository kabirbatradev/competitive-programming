#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  Solution() {
    int tc; cin >> tc;

    // for each test case
    for (int i = 0; i < tc; i++) {
      // number of wifi, number of houses
      int n, m; cin >> n >> m;
      
      // get house numbers
      vector<int> houseNums(m);
      for (int j = 0; j < m; j++) {
        cin >> houseNums[j];
      }
      // might not already be sorted
      sort(houseNums.begin(), houseNums.end());

      // binary search for optimal max distance
      double low = 0; // place wifi on top of house
      double high = 1e6; // max house at 1 million
      for (int j = 0; j < 40; j++) { // 40 iterations should be good enough
        double mid = low + (high - low) / 2.;
        // if possible, try smaller
        if (canFunction(mid, n, houseNums)) {
          high = mid;
        }
        // not possible, try bigger
        else {
          low = mid;
        }
      }

      // low and high should have converged to a best max distance 
      cout << low << '\n';
    }
  }

  bool canFunction(double maxDistance, int numWifiPoints, vector<int> houseNums) {
    int accessPointsUsed = 0;
    double prevWifiPos = INT_MIN;
    for (int housePos : houseNums) {
      // if distance between house and prev wifi is too big, need new wifi
      if (housePos - prevWifiPos > maxDistance) {
        accessPointsUsed++;
        prevWifiPos = housePos + maxDistance; // this position barely includes housePos in range
      }
      // otherwise this house is already covered by wifi
    }

    // true if we used not too many wifi points
    return accessPointsUsed <= numWifiPoints;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  cout.precision(1); // # decimal places
  cout << fixed; // force precision decimal places
  Solution s;
}

/*
n = number of wifi points
m = number of houses, each is num from 1 to 100,000
output: max distance between house and access point

BSTA:
binary search for max distance
test a fixed max distance with can function:
greedy approach:
place first access point as far as possible from first house
if next house is covered, skip
if next house is not covered, repeat: place next access point

*/
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
  int t; cin >> t;
  for (int i = 0; i < t; i++) {

    int n, x; cin >> n >> x; 
    // seems the sample input got n and x mixed up
    // i will assume sample input is correct maybe
      // n farms
      // x disciples

    vector<int> prefixSum(n+1, 0); // extra one at the start for 0 sum
    for (int j = 0; j < n; j++) {
      int carrots; cin >> carrots;

      prefixSum[j+1] = prefixSum[j] + carrots;
    }

    // for every pair (start, end) inclusive, get contiguous sum
    int counter = 0;
    for (int j = 0; j < n+1; j++) {
      for (int k = j+1; k < n+1; k++) {
        int contiguousSum = prefixSum[k] - prefixSum[j];
        if (contiguousSum % x == 0) counter++;
      }
    }
    cout << counter << '\n';
  }
}

/*
idea:
  a contiguous sum of carrots can be quickly obtained by subtracting 2 prefix sums
solution:
  create prefix sum of every length
  can mod by # disciples along the way (to prevent overflow, although using long longs should do the trick)
  then take every pair of prefix sums and subtract to get contiguous sum
    check if divisible by # disciples
*/
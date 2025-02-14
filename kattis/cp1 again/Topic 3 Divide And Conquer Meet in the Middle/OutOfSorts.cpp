// Author: Kabir batra
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  ll n, m, a, c, x0; cin >> n >> m >> a >> c >> x0;
  
  // what if we just stored the entire sequence in a vector?
  vector<ll> sequence;
  sequence.reserve(n);

  int xi = x0; // note that initial xi is not pushed into the sequence list
  for (int i = 0; i < n; i++) {
    // generate next xi using formula and previous xi
    xi = (a * xi + c) % m;
    sequence.push_back(xi);
  }

  // binary search each num in sequence and count # successes
  int count = 0;
  for (int target : sequence) {

    bool found = false;
    
    int low = 0, high = n-1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      // target was found, break loop 
      if (sequence[mid] == target) {
        found = true;
        break;
      }
      // target is small, go left
      else if (target < sequence[mid]) {
        high = mid - 1;
      }
      // target is big, go right
      else {
        low = mid + 1;
      }
    }

    if (found) count++;

  }
  
  cout << count << '\n';
}

/*
generate sequence of numbers and populate array
a number can be found with binary search if... 
  we binary search and we find it ofc
*/
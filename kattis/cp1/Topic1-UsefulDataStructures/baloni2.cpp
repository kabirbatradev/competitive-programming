

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};

// ll is kinda op pog use it ALWAYS

// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int n;
  cin >> n;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  unordered_map<int, int> um;

  int arrows = 0;

  for (int tc = 0; tc < n; tc++) {
    int h; cin >> h;
    if (um.find(h) != um.end()) {
      // reduce count of arrows at that level
      if (um[h] == 1) {
        um.erase(h);
      }
      else {
        um[h]--;
      }
    }
    else {
      // create new arrow
      arrows++;
    }
    // move arrow lower
    if (h == 1) {
      continue;
    }
    if (um.find(h-1) != um.end()) {
      um[h-1]++;
    }
    else {
      um[h-1] = 1;
    }
  }

  cout << arrows << "\n";

}
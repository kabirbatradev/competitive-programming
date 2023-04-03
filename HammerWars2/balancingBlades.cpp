
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(10);

  int n;
  cin >> n;
  
  int arr[n];

  for (int i = 0; i < n; i++) {
    int p; cin >> p;
    arr[i] = p;
  }

  sort(arr, arr + n);
  ll ugliness = 0;
  for (int i = 0; i < n-1; i++) {
    // ugliness = (pi - pi+1)^2
    ugliness += pow(arr[i] - arr[i+1], 2);
  }

  cout << ugliness << "\n";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << "\n";

  // sorting the power levels does not work to minimize
  // we need to minimize the difference squared between every neighboring number
  
  // maybe i could have brute forced try every combination?
  // maybe i could have greedy? is that not the same as sorting though?

  // i just needed to use long long lol
  
}
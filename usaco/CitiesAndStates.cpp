#include<bits/stdc++.h>
using namespace std;

int main() {
  // read and write to file!
  freopen("citystate.in", "r", stdin);
  freopen("citystate.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  
  // state + city --> count
  map<string, int> stateCityCounts;

  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    string city, state;
    cin >> city >> state;
    city = city.substr(0, 2);

    // skip when they are the same because it would allow same state
    if (city == state) continue;

    stateCityCounts[state+city]++;
  }
  int total = 0;
  for (auto [stateCity, count] : stateCityCounts) {
    string cityState = stateCity.substr(2,2) + stateCity.substr(0,2);
    total += count * stateCityCounts[cityState];
  }

  cout << total / 2 << endl;
}
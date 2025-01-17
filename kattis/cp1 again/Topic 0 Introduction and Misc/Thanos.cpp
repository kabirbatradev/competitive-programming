#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int T; cin >> T;
  for (int t = 0; t < T; t++) {
    ll Population, Rate, Food; // using longs so we dont get overflow
    cin >> Population >> Rate >> Food;

    // simulate the # years needed
    int years = 0;
    while (Population <= Food) {
      Population *= Rate;
      years++;
    }
    cout << years << "\n";

  }

}
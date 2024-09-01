
#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;

  for (int tc = 0; tc < t; tc++) {
    int a, b;
    cin >> a >> b;

    if (b & 1 == 1) {
      if (a < 2) {
        cout << "no\n";
        continue;
      }
      a -= 2;
    }

    if (a & 1 == 1) {
      cout << "no\n"; continue;
    }
    cout << "yes\n";

  }
  
}
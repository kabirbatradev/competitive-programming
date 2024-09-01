#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int t; cin >> t;
  for (int tc = 0; tc < t; tc++) {
    int n; cin >> n;
    string s; cin >> s;
    double result = sqrt(n);
    int root = (int)result;
    if (root != result) {
      // not a square
      cout << "No\n";
      continue;
    }

    bool bad = false;
    for (int i=0; i < root && !bad; i++) {
      for (int j = 0; j < root && !bad; j++) {
        // first row or last, then 1
        if (i == 0 || i == root-1) {
          if (s[i*root + j] != '1') {
            bad = true;
          }
        }
        else {
          // if first or last, then 1
          if (j == 0 || j == root - 1) {
            if (s[i*root + j] != '1') {
              bad = true;
            }
          }
          // if in the middle, then 0
          else {
            if (s[i*root + j] != '0') {
              bad = true;
            }
          }
        }
      }
    }

    if (bad) {
      cout << "No\n";
    }
    else {
      cout << "Yes\n";
    }

  }
}
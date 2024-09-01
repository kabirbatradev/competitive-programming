#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int t; cin >> t;
  for (int tc = 0; tc < t; tc++) {
    int l, r; cin >> l >> r;
    int gap = r - l;

    // how many numbers can we fit in a gap
    // optimal: distance between numbers increases by 1 each time
    // 0, 1, 3, 6, 10, 15, 21
    // for 1 num, you need 0 gap; for 2 nums, you need 1 gap, for 3 nums, you need 3 gap; for 4 nums, you need 6 gap
    // gapn = 1 + 2 + 3 + 4 .. + n = (1 + n)(n/2)
    // solve for n
    // 0 = n^2 + n - 2*gapn
    // n = -1 + root(1 - 4*-2*gapn) / 2
    // n = -1 + root(1 + 8*gapn) / 2

    // if root is decimal, we can truncate, right?
    double n = (-1 + sqrt(1 + 8.0*gap)) / 2;
    // cout << n << "\n";
    cout << (int)n+1 << "\n"; // i couldnt exactly figure out why everything is off by 1 but it works
  }
}
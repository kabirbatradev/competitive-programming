#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int n, m; cin >> n >> m;

  // store and sort all sizes offered so we can binary search
  vector<int> sizesOffered(n);
  for (int i = 0; i < n; i++) {
    cin >> sizesOffered[i];
  }
  sort(sizesOffered.begin(), sizesOffered.end());

  // for each paint size need, find the closest valid/larger size. add the difference to total paint wasted
  ll paintWasted = 0;
  for (int i = 0; i < m; i++) {
    int paintNeeded;
    cin >> paintNeeded;

    // binary search for best size offered
    int l = 0, r = n-1;
    int bestValidSize = sizesOffered[r];
    while (l <= r) {
      int mid = l + (r - l)/2;
      int size = sizesOffered[mid];
      if (size == paintNeeded) {
        bestValidSize = size;
        break; // can break early because we have the perfect size
      }
      else if (size > paintNeeded) {
        bestValidSize = size;
        r = mid-1;
      }
      else {
        l = mid+1;
      }
    }

    paintWasted += bestValidSize - paintNeeded;
  }

  cout << paintWasted << '\n';
}
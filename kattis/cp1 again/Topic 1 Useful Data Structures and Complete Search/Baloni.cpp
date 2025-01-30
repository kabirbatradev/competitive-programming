// Author: Kabir batra
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int arrowsShot = 0;

  // counting map for counting the current arrows still flying
  unordered_map<int, int> heights;

  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    int h; cin >> h;

    // arrow already exists, hit balloon, so move arrow down one
    if (heights[h] > 0) {
      heights[h]--;
      heights[h-1]++;
    }
    // need to shoot new arrow at that balloon and then the arrow drops
    else {
      heights[h-1]++;
      arrowsShot++;
    }
  }

  // note: the arrows shot for past balloons 
  // can be used immediately for future balloons

  cout << arrowsShot << '\n';
}
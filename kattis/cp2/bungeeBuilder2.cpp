
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int n;
  cin >> n;

  int heights[n];

  int tallestOnLeft[n];
  int tallestOnRight[n];

  for (int i = 0; i < n; i++) {
    int h;
    cin >> h;
    heights[i] = h;



    if (i == 0) {
      tallestOnLeft[i] = 0;
      continue;
    }
    if (heights[i-1] > tallestOnLeft[i-1]) {
      tallestOnLeft[i] = heights[i-1];
    }
    else {
      tallestOnLeft[i] = tallestOnLeft[i-1];
    }
  }


  for (int i = n-1; i >= 0; i--) {
    // heights[i];
    if (i == n-1) {
      tallestOnRight[i] = 0;
      continue;
    }
    tallestOnRight[i] = max(heights[i+1], tallestOnRight[i+1]);
    // if (heights[i+1] > tallestOnRight[i+1]) {
    //   tallestOnRight[i] = heights[i+1];
    // }
    // else {
    //   tallestOnRight[i] = tallestOnRight[i+1];
    // }
  }

  int bestJump = 0;

  for (int i = 0; i < n; i++) {
    // cout << "height: " << heights[i] << " tallestOnLeft: " << tallestOnLeft[i] << " tallestOnRight " << tallestOnRight[i] << endl;
    int resulting_jump = min(tallestOnLeft[i], tallestOnRight[i]) - heights[i];
    // cout << "resulting jump " << resulting_jump << endl;

    if (resulting_jump > bestJump) {
      bestJump = resulting_jump;
    }
  }

  cout << bestJump << endl;


}


// this time I will use a different strategy
// have an array of all heights
// have array of tallest to the left
// have array of tallest to the right
#include<bits/stdc++.h>
using namespace std;

#define GRID_MAX 501

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  
  while (true) {

    int n; // number of rectangles
    cin >> n;
    if (n == 0) break;

    bool grid[GRID_MAX][GRID_MAX] = {0};


    // read in "n" rectangle
    for (int i = 0; i < n; i++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      // fill in part of the grid covered
      for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
          grid[x][y] = true; 
        }
      }

    }

    int total = 0;
    for (int x = 0; x < GRID_MAX; x++) {
      for (int y = 0; y < GRID_MAX; y++) {
        if (grid[x][y])
          total++;
      }
    }

    cout << total << "\n";

  }

  
}
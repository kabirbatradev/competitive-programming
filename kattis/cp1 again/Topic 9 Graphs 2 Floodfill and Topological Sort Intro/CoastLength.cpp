// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  Solution() {
    int n, m; cin >> n >> m;

    // create layer around everything as 0 
    vector<vector<int>> grid(n+2, vector<int>(m+2, 0));

    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < m; j++) {
        // offset by 1 to maintain first layer of 0s
        grid[i+1][j+1] = s[j] - '0';
        
      }
    }

    // run bfs on every single outside node
    // count number of times we hit land
    // keep track of visited
    int count = 0;

    vector<vector<bool>> visited(n+2, vector<bool>(m+2, false));

    queue<pair<int, int>> q;

    // push first last row, first last col into queue
    for (int i = 0; i < n+2; i++) {
      q.push({i, 0});
      q.push({i, m+2-1});
    }
    for (int j = 0; j < m+2; j++) {
      q.push({0, j});
      q.push({n+2-1, j});
    }

    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    while (!q.empty()) {
      auto [row, col] = q.front(); q.pop();

      // if visited, then skip
      if (visited[row][col]) continue;

      // if this is land, then add to counter and stop
      if (grid[row][col] == 1) {
        count++;
        continue;
      }

      // if this is water, continue searching, mark as visited
      visited[row][col] = true;

      for (int k = 0; k < 4; k++) {
        int newRow = row + dx[k];
        int newCol = col + dy[k];
        if (newRow < 0 || newRow >= n+2 || newCol < 0 || newCol >= m+2) {
          continue; // skip if out of bounds
        }
        q.push({newRow, newCol});
      }
      
    }

    cout << count << '\n';

  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  Solution s;
}
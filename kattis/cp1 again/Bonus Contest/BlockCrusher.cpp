// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
#define int long long // replace all "int" with "long long"
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  int h, w;
  Solution(int h, int w) : h(h), w(w) {

    // cout << h << " " << w << endl;

    // read in grid
    vector<vector<int>> grid(h, vector<int>(w));

    // im reading input in wrong!
    // for (int i = 0; i < h; i++) {
    //   for (int j = 0; j < w; j++) {
    //     cin >> grid[i][j];
    //   }
    // }
    for (int i = 0; i < h; i++) {
      string in; cin >> in; // need to actually parse a string
      for (int j = 0; j < w; j++) {
        grid[i][j] = in[j] - '0';
      }
    }

    // for (int i = 0; i < h; i++) {
    //   for (int j = 0; j < w; j++) {
    //     cout << grid[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    // cout << endl;

    // run shorest path from top to bottom
    // each pq thing should have
      // weight
      // cell ij
      // cell that it came from ij
    using omg = tuple<int, int, int, int, int>;
    priority_queue<tuple<int, int, int, int, int>, vector<omg>, greater<omg>> pq;

    vector<vector<bool>> visited(h, vector<bool>(w, false));

    // all cells come from -1 -1 default
    vector<vector<pair<int,int>>> whereComeFrom(h, vector<pair<int,int>>(w, {-1, -1}));

    // put first values in pq:
    // the entire top row
    for (int c = 0; c < w; c++) {
      pq.push({grid[0][c], 0, c, -1, -1});
      // putting every row=0
      // and -1 is where it comes from
    }

    pair<int, int> lastCell = {-1, -1};
    while (!pq.empty()) {
      auto [weight, i, j, prevI, prevJ] = pq.top(); pq.pop();

      if (visited[i][j]) continue;
      visited[i][j] = true;

      // mark where this cell comes from 
      whereComeFrom[i][j] = {prevI, prevJ};

      // base case: we reached a cell that is in the bottom row
        // if this is the first cell to do that, we found the shortest path
      // i means row means height
      if (i == h-1) {
        lastCell = {i, j};
        break;
      }

      // consider going in all directions
      for (int k = 0; k < 8; k++) {
        int iNew = i + dx[k];
        int jNew = j + dy[k];

        // do not consider if out of bounds
        // or if visited
        if (iNew < 0 || jNew < 0 || iNew >= h || jNew >= w
          || visited[iNew][jNew]
        ) continue;

        int newWeight = weight + grid[iNew][jNew];
        pq.push({newWeight, iNew, jNew, i, j});
      }

    }

    // now fill the grid with spaces and print the grid
    // fill the grid with -1 along the fracture line
    // then print the grid
    while (lastCell != make_pair(-1ll, -1ll)) {

      auto [i, j] = lastCell;

      grid[i][j] = -1; // mark with -1

      lastCell = whereComeFrom[lastCell.first][lastCell.second];
    }

    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (grid[i][j] == -1) {
          cout << ' ';
        }
        else {
          cout << grid[i][j];
        }
      }
      cout << endl;
    }
    cout << endl;
    
  }
};

// using "signed" works around "int" being replaced with long long
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cin.exceptions(cin.failbit); // idk what this does but it prevents me from doing while (cin >> n)
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places

  while (true) {
    int h, w;
    cin >> h >> w;
    if (h == 0 && w == 0) break;

    Solution s(h, w);
  }
}


/*
can start from any cell at the top
goal: find the shortest path to reach a bottom cell

then report back that shortest path and edit the cell values 
and then print that result

idea:
  run shortest path from every top cell

idea: 
  create one dummy node at the top above all cells
  and one more at the bottom below all bottom cells
  run shortest path between those 2 dummy nodes

shorest path is dijkstras
  add all top cells to pq with their value as weight
  note we want min heap (not max heap which is default)
then we stop when we reach a cell at the bottom

how to get the actual path:
  for every node added to pq: provide additional info: the cell that it came from
  when a node becomes visited, then write down the cell that it came from

side note:
  always do diagonals or straight down, i think...
  actually nvm just go all directions



*/
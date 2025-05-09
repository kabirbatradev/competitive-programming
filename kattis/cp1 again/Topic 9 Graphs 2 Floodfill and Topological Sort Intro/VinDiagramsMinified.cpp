#include <bits/stdc++.h>
using namespace std;
struct Solution {
  int R, C;
  Solution() {
    cin >> R >> C;
    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
      cin >> grid[i];
    }
    pair<int, int> posA, posB;
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (grid[i][j] == 'A') {
          posA = {i, j};
        }
        else if (grid[i][j] == 'B') {
          posB = {i, j};
        }
      }
    }
    vector<vector<bool>> gridA(R, vector<bool>(C, false));
    dfs(posA.first, posA.second, -1, -1, grid, gridA);
    vector<vector<bool>> gridB(R, vector<bool>(C, false));
    dfs(posB.first, posB.second, -1, -1, grid, gridB);
    vector<vector<int>> floodfillGrid(R, vector<int>(C, false));
    pair<int, int> startFloodFillA = {-1, -1};
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C-1; j++) {
        if (gridA[i][j] && !gridA[i][j+1]) {
          startFloodFillA = {i, j+1};
          i = R;
          break;
        }
        else if (gridA[i][j] && gridA[i][j+1]) {
          break;
        }
      }
    }
    int counterA = 0;
    floodFillA(startFloodFillA.first, startFloodFillA.second, gridA, floodfillGrid, counterA, grid);
    pair<int, int> startFloodFillB = {-1, -1};
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C-1; j++) {
        if (gridB[i][j] && !gridB[i][j+1]) {
          startFloodFillB = {i, j+1};
          i = R;
          break;
        }
        else if (gridB[i][j] && gridB[i][j+1]) {
          break;
        }
      }
    }
    int counterB = 0;
    int counterIntersection = 0;
    floodFillB(startFloodFillB.first, startFloodFillB.second, gridB, floodfillGrid, counterB, counterIntersection, grid);
    cout << counterA-counterIntersection << " " << counterB-counterIntersection << " " << counterIntersection << '\n';
  }
  int dx[4] = {0, 0, -1, 1};
  int dy[4] = {-1, 1, 0, 0};
  void floodFillB(int r, int c, vector<vector<bool>>& gridA, vector<vector<int>>& floodfillGrid, int& counter,
    int& counterIntersection,
    vector<string>& grid
  ) {
    if (floodfillGrid[r][c] >= 2) return;
    if (floodfillGrid[r][c] == 1) {
      counterIntersection++;
    }
    floodfillGrid[r][c] += 2;
    if (grid[r][c] == '.')
      counter++;
    for (int k = 0; k < 4; k++) {
      int newR = r + dx[k];
      int newC = c + dy[k];
      if (
        newR >= 0 && newR < R
        && newC >= 0 && newC < C
        && !gridA[newR][newC]
      ) {
        floodFillB(newR, newC, gridA, floodfillGrid, counter, counterIntersection, grid);
      }
    }
  }
  void floodFillA(int r, int c, vector<vector<bool>>& gridA, vector<vector<int>>& floodfillGrid, int& counter,
    vector<string>& grid
  ) {
    if (floodfillGrid[r][c] == 1) return;
    floodfillGrid[r][c] = 1;
    if (grid[r][c] == '.')
      counter++;
    for (int k = 0; k < 4; k++) {
      int newR = r + dx[k];
      int newC = c + dy[k];
      if (
        newR >= 0 && newR < R
        && newC >= 0 && newC < C
        && !gridA[newR][newC]
      ) {
        floodFillA(newR, newC, gridA, floodfillGrid, counter, grid);
      }
    }
  }
  void dfs(int r, int c, int prevPosR, int prevPosC, vector<string>& grid, vector<vector<bool>>& gridA) {
    if (gridA[r][c] == true) return;
    gridA[r][c] = true;
    int dr = r - prevPosR;
    int dc = c - prevPosC;
    int newR = r + dr;
    int newC = c + dc;
    if (
      prevPosR != -1
      && newR >= 0 && newR < R
      && newC >= 0 && newC < C
      && grid[newR][newC] == 'X'
    ) {
      dfs(newR, newC, r, c, grid, gridA);
      return;
    }
    for (int k = 0; k < 4; k++) {
      int newR = r + dx[k];
      int newC = c + dy[k];
      if (
        newR >= 0 && newR < R
        && newC >= 0 && newC < C
        && grid[newR][newC] == 'X'
      ) {
        dfs(newR, newC, r, c, grid, gridA);
      }
    }
  }
};
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  Solution s;
}

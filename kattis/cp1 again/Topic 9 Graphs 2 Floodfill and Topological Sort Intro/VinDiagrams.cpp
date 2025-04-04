// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using ll = long long;
// ll is kinda op pog use it ALWAYS
using namespace std;

struct Solution {
  int R, C;
  Solution() {
    cin >> R >> C;

    vector<string> grid(R);

    for (int i = 0; i < R; i++) {
      // string row;
      // cin >> row;
      cin >> grid[i];
    }

    // print the input that was read
    // for (int i = 0; i < R; i++) {
    //   for (int j = 0; j < C; j++) {
    //     cout << grid[i][j];
    //   }
    //   cout << '\n';
    // }
    // cout << endl;

    // find A and B:
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


    // use dfs to mark the entire A loop
    vector<vector<bool>> gridA(R, vector<bool>(C, false));
    dfs(posA.first, posA.second, -1, -1, grid, gridA); // prev pos -1 means we have 2 directions to go in
    

    // print A loop only
    // for (int i = 0; i < R; i++) {
    //   for (int j = 0; j < C; j++) {
    //     cout << ((gridA[i][j]) ? '#' : '.');
    //   }
    //   cout << '\n';
    // }
    // cout << endl;


    vector<vector<bool>> gridB(R, vector<bool>(C, false));
    dfs(posB.first, posB.second, -1, -1, grid, gridB); // prev pos -1 means we have 2 directions to go in
    

    // print B loop only
    // for (int i = 0; i < R; i++) {
    //   for (int j = 0; j < C; j++) {
    //     cout << ((gridB[i][j]) ? '#' : '.');
    //   }
    //   cout << '\n';
    // }
    // cout << endl;

    vector<vector<int>> floodfillGrid(R, vector<int>(C, false));

    // floodfill A:
    // mark grid with 1's
    // counter to keep track of area
    pair<int, int> startFloodFillA = {-1, -1};
    // find the first X in gridA that has a '.' after it
    // find the first true that has a false after it
    // but also if there were multiple Xs in a row, then thats the top bar, so skip it
    for (int i = 0; i < R; i++) { // note reduced range
      for (int j = 0; j < C-1; j++) {
        // if this is true and next is not true 
        if (gridA[i][j] && !gridA[i][j+1]) {
          startFloodFillA = {i, j+1}; // mark the spot with the period
          i = R; // break out of the double whole loop
          break;
        }
        else if (gridA[i][j] && gridA[i][j+1]) {
          break; // skip the rest of this row
        }
      }
    }

    int counterA = 0;
    floodFillA(startFloodFillA.first, startFloodFillA.second, gridA, floodfillGrid, counterA, grid);

    // for (int i = 0; i < R; i++) {
    //   for (int j = 0; j < C; j++) {
    //     cout << floodfillGrid[i][j];
    //   }
    //   cout << '\n';
    // }
    // cout << endl;


    pair<int, int> startFloodFillB = {-1, -1};
    // find similar start for floodfill for B
    for (int i = 0; i < R; i++) { // note reduced range
      for (int j = 0; j < C-1; j++) {
        // if this is true and next is not true 
        if (gridB[i][j] && !gridB[i][j+1]) {
          startFloodFillB = {i, j+1}; // mark the spot with the period
          i = R; // break out of the double whole loop
          break;
        }
        else if (gridB[i][j] && gridB[i][j+1]) {
          break; // skip the rest of this row
        }
      }
    }

    int counterB = 0;
    int counterIntersection = 0;
    floodFillB(startFloodFillB.first, startFloodFillB.second, gridB, floodfillGrid, counterB, counterIntersection, grid);

    // for (int i = 0; i < R; i++) {
    //   for (int j = 0; j < C; j++) {
    //     cout << floodfillGrid[i][j];
    //   }
    //   cout << '\n';
    // }
    // cout << endl;

    
    cout << counterA-counterIntersection << " " << counterB-counterIntersection << " " << counterIntersection << '\n';

  }

  int dx[4] = {0, 0, -1, 1};
  int dy[4] = {-1, 1, 0, 0};


  // now we mark things with a 2 instead
  void floodFillB(int r, int c, vector<vector<bool>>& gridA, vector<vector<int>>& floodfillGrid, int& counter, 
    int& counterIntersection,
    vector<string>& grid
  ) {
    // if visited, then skip
    if (floodfillGrid[r][c] >= 2) return; // 2 or more, because we are marking intersections with '3'

    // case of intersection
    if (floodfillGrid[r][c] == 1) {
      counterIntersection++;
    }
    floodfillGrid[r][c] += 2; // mark as visited (intersection is '3')

    if (grid[r][c] == '.')
      counter++;

    // go in all 4 directions
    for (int k = 0; k < 4; k++) {
      int newR = r + dx[k];
      int newC = c + dy[k];

      // check for in bounds, stop if cell is 
      if (
        newR >= 0 && newR < R
        && newC >= 0 && newC < C
        && !gridA[newR][newC] // not true in grid A means this is not a "wall"
      ) {
        floodFillB(newR, newC, gridA, floodfillGrid, counter, counterIntersection, grid);
      }
    }
  }


  void floodFillA(int r, int c, vector<vector<bool>>& gridA, vector<vector<int>>& floodfillGrid, int& counter,
    vector<string>& grid
  ) {
    // if visited, then skip
    if (floodfillGrid[r][c] == 1) return;

    floodfillGrid[r][c] = 1; // mark as visited

    if (grid[r][c] == '.')
      counter++;

    // go in all 4 directions
    for (int k = 0; k < 4; k++) {
      int newR = r + dx[k];
      int newC = c + dy[k];

      // check for in bounds, stop if cell is 
      if (
        newR >= 0 && newR < R
        && newC >= 0 && newC < C
        && !gridA[newR][newC] // not true in grid A means this is not a "wall"
      ) {
        floodFillA(newR, newC, gridA, floodfillGrid, counter, grid);
      }
    }
  }
  
  // prev pos is the position of where we came from in the dfs 
  // (so that we keep going in that direction if we reach a 4 way intersection)
  void dfs(int r, int c, int prevPosR, int prevPosC, vector<string>& grid, vector<vector<bool>>& gridA) {

    // if visited, then skip
    if (gridA[r][c] == true) return;

    gridA[r][c] = true; // mark as visited

    // go in the direction of "forward" if possible
      // if it is possible, then this is either a normal case or an intersection, where we are supposed to go forward
    // if not possible, then this is not an intersection, so try all 4 directions, and one will be correct
    int dr = r - prevPosR;
    int dc = c - prevPosC;

    int newR = r + dr;
    int newC = c + dc;

    // if prev are not -1, and its in bounds, and its an X in the grid then this is the way to go 
    if (
      prevPosR != -1
      && newR >= 0 && newR < R
      && newC >= 0 && newC < C
      && grid[newR][newC] == 'X'
    ) {
      dfs(newR, newC, r, c, grid, gridA);
      return; // return early! 
    }

    // go in all 4 directions
    for (int k = 0; k < 4; k++) {
      int newR = r + dx[k];
      int newC = c + dy[k];

      // same check for in bounds, but no check for if prev is -1 ()
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
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  Solution s;
}

/*
find the two loops of X's 
  loop for A
  loop for B

put these loops into new 2d arrays, one for A, and one for B
  everything is true or false (part of loop or not)

create third 2d grid for flood fill
  everything is ints (init to 0)

for the A loop:
  flood fill the area inside (fill the floodfill grid)
  set it all to 1s (to mark as visited)

for the B loop:
  flood fill the area inside (fill the floodfill grid)
  set it all to 2s (to mark as visitied)
  if we see a 1, then we can explore over it, but we should increment the "intersection counter"

how to start floodfilling:
  if there is every a '.' after an X, then just start floodfill from there 
*/
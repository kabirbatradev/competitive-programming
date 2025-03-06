// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  vector<set<int>> adjList;
  
  Solution() {
    // int n; // made it global
    cin >> n;                  // num colors in painting
    vector<string> colors(n);  // in sorted order, best color first
    map<string, int> colorToIndex;
    for (int i = 0; i < n; i++) {
      cin >> colors[i];
      colorToIndex[colors[i]] = i;
    }

    int m;
    cin >> m;  // num pairs of bad colors
    // want to represent with adj list
    // vector<vector<int>> adjList(n);  // one adj list for every color
    // adjList = vector<vector<int>>(n);
    adjList = vector<set<int>>(n); // use vector of sets for O(1) look up 
    for (int i = 0; i < m; i++) {
      string c1, c2;
      cin >> c1 >> c2;
      int c1Num = colorToIndex[c1];
      int c2Num = colorToIndex[c2];
      // adjList[c1Num].push_back(c2Num);
      // adjList[c2Num].push_back(c1Num);
      adjList[c1Num].insert(c2Num);
      adjList[c2Num].insert(c1Num);
    }

    // example of how to print adj list code when debugging: 
    // for (int i = 0; i < n; i++) {
    //   cout << "adj list for " << i << endl;
    //   for (int num : adjList[i]) {
    //     cout << num << " ";
    //   }
    //   cout << endl;
    // }

    // perform complete search, always picking best color first, but
    // backtracking if fail keep track of # solutions the first solution
    // identified will also be the prefered painting

    // complete search state: 
      // how many painting lines completed
      // which nums already used (aka visited), pass by ref
      // what was the previous line color (-1 means nothing)
      // also the current painting state itself, pass by ref
    vector<bool> visited(n, false); // for each color, visited is false by default
    vector<int> paintingState; // empty means no colors in the painting right now
    completeSearch(0, visited, -1, paintingState);
    // idea: stop updating painting state once first painting is found

    cout << numValidPaintings << '\n';
    string prefix = "";
    for (int stringIndex : paintingState) {
      cout << prefix << colors[stringIndex];
      prefix = " ";
    }
    cout << '\n';
  }

  int n; 
  bool bestPaintingFound = false;
  int numValidPaintings = 0;
  // i also made adjList global up top

  void completeSearch(int linesCompleted, vector<bool>& visited, int prevColor, vector<int>& paintingState) {
    // if completed painting
    if (linesCompleted == n) {
      bestPaintingFound = true;
      numValidPaintings++;
      return;
    }

    // try all colors (from 0 to n-1), use the first one that is not visited and not adj to prev color
    // if no such color exists, then we failed and return
    for (int color = 0; color < n; color++) {
      if (visited[color]) continue;
      // if this color does not look good with prev color 
      if (adjList[color].find(prevColor) != adjList[color].end()) continue;
      
      // otherwise, we can use this color:
      visited[color] = true;
      if (!bestPaintingFound) paintingState.push_back(color);

      completeSearch(linesCompleted + 1, visited, color, paintingState);

      // reset values after for other cases
      visited[color] = false;
      if (!bestPaintingFound) paintingState.pop_back();

    }

    return;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places

  // create unique instances of Solution for each test case
  int T;
  cin >> T;

  for (int tc = 0; tc < T; tc++) {
    Solution s;
  }
}
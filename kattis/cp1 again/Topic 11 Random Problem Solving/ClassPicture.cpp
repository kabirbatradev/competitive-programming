// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
#define int long long // replace all "int" with "long long"
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {

  int n;
  vector<set<int>> adjList; // global adj list

  Solution() {
    while (cin >> n) {

      vector<string> names(n);

      for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        names[i] = name;
      }

      // sort names so final result is lexicographically sorted
      sort(names.begin(), names.end());

      // map from name to integer for easy conversion
      map<string, int> getInt;
      for (int i = 0; i < n; i++) {
        getInt[names[i]] = i;
      }

      // populate adj list
      int m; cin >> m;
      adjList.assign(n, set<int>()); // reset adj list to empty sets
      for (int i = 0; i < m; i++) {
        string a, b;
        cin >> a >> b;

        // convert to int before populating adj list
        int ai = getInt[a];
        int bi = getInt[b];
        adjList[ai].insert(bi);
        adjList[bi].insert(ai);
      }

      // initialize visited
      visited.assign(n, false);

      // reset currentList
      currentList.clear();

      if (completeSearch()) {
        // currentList has the solution
        string prefix = "";
        for (int i : currentList) {
          cout << prefix << names[i];
          prefix = " ";
        }
        cout << '\n';
      }
      else {
        cout << "You all need therapy.\n";
      }

    }

  }

  // current solution being built is stored in vector/stored set
  vector<int> currentList;
  vector<bool> visited;

  // return true if solution was possible
  bool completeSearch() {
    // base case:
    if (currentList.size() == n) return true;

    // try putting every person next 
    for (int i = 0; i < n; i++) {
      // skip if visited
      if (visited[i]) continue;
      // skip if adjacent to the latest student
      if (currentList.size() > 0 && adjList[currentList.back()].contains(i)) continue;

      // update current state
      currentList.push_back(i);
      visited[i] = true;

      // continue searching
      if (completeSearch()) {
        return true;
      }

      // revert current state for other possibilities
      currentList.pop_back();
      visited[i] = false;
    }

    // if we got here and didnt return true, this route is impossible
    return false;
  }
};

// using "signed" works around "int" being replaced with long long
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  Solution s;
}

/*
given list of names of students
given list of pairs of students that wont sit next to each other

just do dfs/complete search and return the first solution

what does a state look like?
  the current order of people in the picture
    represented as a vector of ints
  the set of remaining people who have not been placed
    stored as a visited array of booleans

at each iteration of dfs:
  consider adding each person in the unvisited set
  only add them if adjList doesnt include the "back" of the vector
*/
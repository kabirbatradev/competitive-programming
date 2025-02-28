#include<bits/stdc++.h>
using namespace std;
using ll = long long;


// len, weight=target sum
int l, w; // globals

vector<char> currentLetters;
vector<vector<bool>> visited;
// bool visited[40][1000] = {0}; // all set to false

void printLetters() {
  for (char c : currentLetters) {
    cout << c;
  }
  cout << '\n';
}

bool dfs(int numCoinsUsed, int currentSum) {
  // base case
  if (numCoinsUsed == l) {
    if (currentSum == w) {
      printLetters();
      return true;
      // should quit when true
    }
    return false;
    visited[numCoinsUsed][currentSum] = true;
  }

  // if sum is too large already, quit early
  if (currentSum >= w) {
    visited[numCoinsUsed][currentSum] = true;
    return false;
  }

  // skip if we already went down this path (with these states)
  if (visited[numCoinsUsed][currentSum]) return false;

  // consider using every character
  for (char c = 'a'; c <= 'z'; c++) {
    currentLetters.push_back(c);
    int value = (int)(c-'a' + 1);
    if (dfs(numCoinsUsed + 1, currentSum + value)) {
      return true; // return early if we already got an answer
    }
    currentLetters.pop_back();
  }
  visited[numCoinsUsed][currentSum] = true;
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  
  // global l and w
  cin >> l >> w;
  if (w < l or w > l*26) {
    cout << "impossible" << '\n';
    return 0;
  }

  // init globals:
  currentLetters.reserve(l);
  visited = vector<vector<bool>>(l, vector<bool>(w, false));

  dfs(0, 0);

  return 0;
}

/*
26 letters
each has a weight (1 through 26), like a coin value
q: can we reach a target value w?
constraint: we have to use exactly l coins

bound checks for "impossible":
  if w < l
  if w > l*26

brute force: (complete search)
  state = 
    # coins used already
    current sum value
  base case: 
    # coins used = l. then return if current sum value matches w
  
  try using every coin, and call recursive function with new state:
    # coins used++
    current sum value += letter

overlapping subproblems:
  state=(coins used, current sum value) could be reached in multiple ways
  do not want to recompute state if already been here
  can put this state in "visited" table, mark as "true" if visited

oops i forgot to actually set the visited array
*/
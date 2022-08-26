
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

vector<int> bestString;
bool bestStringBuilt = false;

int findCombinations(vector<int> remainingNums, vector<vector<bool> > &adjMatrix, int lastNum) {
  
  if (remainingNums.size() == 0) {
    bestStringBuilt = true;
    return 1;
  }

  int combinations = 0;
  // bool addedSomething = false;
  for (int i = 0; i < remainingNums.size(); i++) {
    int num = remainingNums.at(i);
    // int lastNum = currentString.at(currentString.size()-1);
    
    if (lastNum != -1 && adjMatrix.at(num).at(lastNum) == true) {
      
      continue;
    }
    //otherwise add new num 
    vector<int> remainingNumsCopy = remainingNums;
    remainingNumsCopy.erase(remainingNumsCopy.begin() + i);
    if (!bestStringBuilt) {
      bestString.push_back(num);
      // addedSomething = true;
    }
    combinations += findCombinations(remainingNumsCopy, adjMatrix, num);
  }
  if (!bestStringBuilt && combinations == 0) {
    bestString.erase(bestString.end() - 1);
    // bestString.clear();
  }
  return combinations;

}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int t;
  cin >> t;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  for (int tc = 0; tc < t; tc++) {
    bestString.clear();
    bestStringBuilt = false;

    int n; cin >> n;
    string colors[n];
    unordered_map<string, int> reverseLookup;
    for (int i = 0; i < n; i++) {
      cin >> colors[i];
      reverseLookup[colors[i]] = i;
    }

    // bool adjMatrix[n][n] = {0};
    vector<vector<bool> > adjMatrix;
    for (int i = 0; i < n; i++) {
      vector<bool> temp;
      adjMatrix.push_back(temp);
      for (int j = 0; j < n; j++) {
        adjMatrix.at(i).push_back(false);
      }
    }
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
      string color1, color2;
      cin >> color1 >> color2;
      int x = reverseLookup[color1];
      int y = reverseLookup[color2];
      adjMatrix.at(x).at(y) = true;
      adjMatrix.at(y).at(x) = true;
    }

    // recursive function
    vector<int> remainingNums;
    for (int i = 0; i < n; i++) {
      remainingNums.push_back(i);
    }
    int arrangements = findCombinations(remainingNums, adjMatrix, -1);
    cout << arrangements << "\n";
    string prefix = "";
    for (int x : bestString) {
      cout << prefix << colors[x];
      prefix = " ";
    }
    cout << "\n";

  }

  
}
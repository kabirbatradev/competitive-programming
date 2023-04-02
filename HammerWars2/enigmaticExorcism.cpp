
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

vector< vector<int> > adjList;

int bestStrength = 0;
int strengths[3];

void bfs(int currentNode, vector<int> visitedArray, int totalStrength) {

  // cout << "entered function" << endl;

  // is 0
  // cout << "size: " << adjList.size() << endl;

  // for every neighbor of currentNode
  for (int i = 0; i < adjList.at(currentNode).size(); i++) {

    int neighborNode = adjList.at(currentNode).at(i);
    // cout << "got neighbor" << endl;

    // if neighbor is already visited, skip it
    if (visitedArray.at(neighborNode) != -1) {
      continue;
    }


    int oldTotalStrength = totalStrength;
    
    // for the current not visited neighbor, try drop or no drop
    for (int j = 0; j <= 1; j++) {
      // set visited array to j (strength or no strength)
      visitedArray.at(neighborNode) = j;

      totalStrength = oldTotalStrength;
      
      // update total strength by adding all visited connections
      // iterate through neighbors of this neighbor
      for (int k = 0; k < adjList.at(neighborNode).size(); k++) {
        int neighborNeighborNode = adjList.at(neighborNode).at(k);
        // if neighbor neighbor is visited, add strength
        if (visitedArray.at(neighborNeighborNode) != -1) {
          int strength0or1 = visitedArray.at(neighborNeighborNode);
          
          int dropsTotal = j + strength0or1;
          // can be either 0, 1, or 2
          int strengthToAdd = strengths[dropsTotal];

          totalStrength += strengthToAdd;
          // cout << "adding strength: " << strengthToAdd << endl;
          // cout << "total strength here " << totalStrength << endl;
        }
      }
      // cal bfs for j = 0, separate time for j = 1
      bfs(neighborNode, visitedArray, totalStrength);
      
    }
  }

  bool allVisited = true;
  // if all neighbors are visited, compare total strength to best strength so far
  for (int i = 0; i < visitedArray.size(); i++) {
    if (visitedArray.at(i) == -1) {
      allVisited = false;
      break;
    }
  }
  
  if (allVisited) {
    // if all neighbors are visited
    // compare total strength to best strength so far
    // cout << "total strength " << totalStrength << endl;
    if (totalStrength > bestStrength) {
      bestStrength = totalStrength;
    }

    // print the visited array
    // for (int i = 0; i < visitedArray.size(); i++) {
    //   cout << visitedArray.at(i) << " ";
    // }
    // cout << endl;
    
  }
}



int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(10);

  // n total number of nodes
  int n;
  cin >> n;

  ll s0, s1, s2;
  cin >> strengths[0] >> strengths[1] >> strengths[2];
  // vector< vector<int> > adjList(n); // accidently recreated the list
  for (int i = 0; i < n; i++) {
    adjList.push_back(vector<int>());
  }
  // cin >> s0 >> s1 >> s2;
  for (int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    // describes link between u and v
    adjList.at(u).push_back(v); 
    adjList.at(v).push_back(u);
  }

  // cout << "size earluer: " << adjList.size() << endl;

  // brute force: iterate through every node and set strength to 0, 1, 2
  // then go to all neighboring nodes and try all three strengths again

  // we can pass in list of nodes already inserted and corresponding strengths (visited array)
  // current node to try adding strength to 
  // also a total strength so far var

  // visited = -1 means not visited
  // visited = 0 means visited but no strength drop
  // visited = 1 means visited and added strength drop

  vector<int> visitedArray;
  for (int i = 0; i < n; i++) {
    visitedArray.push_back(-1);
  }
  visitedArray.at(0) = 0;
  bfs(0, visitedArray, 0);
  visitedArray.at(0) = 1;
  bfs(0, visitedArray, 0);

  // print adjacency matrix
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < adjList.at(i).size(); j++) {
  //     cout << adjList.at(i).at(j) << " ";
  //   }
  //   cout << "\n";
  // }

  cout << bestStrength << "\n";
}

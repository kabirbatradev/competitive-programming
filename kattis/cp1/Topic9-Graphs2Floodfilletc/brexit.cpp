

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;
using ll = long long;

const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};

// ll is kinda op pog use it ALWAYS

// #define PI 3.1415926535897932384626433832795


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int C, P, X, L; cin >> C >> P >> X >> L;
  
  // first one is the original count
  pair<int, int> countryConnectionCount[C];
  vector<int> countryConnections[C];

  for (int tc = 0; tc < P; tc++) {
    pair<int, int> connection;
    cin >> connection.first >> connection.second;
    connection.first--;
    connection.second--;

    countryConnectionCount[connection.first].first++;
    countryConnectionCount[connection.first].second++;
    
    countryConnections[connection.first].push_back(connection.second);

    countryConnectionCount[connection.second].first++;
    countryConnectionCount[connection.second].second++;
    countryConnections[connection.second].push_back(connection.first);

  }

  if (L == X) {
    cout << "leave\n";
    return 0;
  }

  list<int> queue;
  queue.push_back(L-1);

  bool found = false;
  
  while (!queue.empty()) {

    // grab the country and 
    // set connection count to 0 to say its dead
    // and go to all the countries its connected to and 
    // subtract one and if it dies then add them to the queue

    int country = queue.front();
    queue.pop_front();

    if (countryConnectionCount[country].first == 0) {
      // country alr dead so 
      continue;
    }

    countryConnectionCount[country].first = 0; // mark as dead

    // cout << endl;
    // for (int i : countryConnections[country]) {
    //   cout << i << " ";
    // }
    // cout << endl;

    for (int i : countryConnections[country]) {
      countryConnectionCount[i].second--;
      if (countryConnectionCount[i].second <= countryConnectionCount[i].first / 2) {
        if (i == X-1) {
          found = true;
          break;
        }
        queue.push_back(i);
        
      }
    }

    


  }
  cout << (found ? "leave\n" : "stay\n");

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
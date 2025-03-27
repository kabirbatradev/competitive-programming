// Author: Kabir Batra, Tony Xu
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  
  int n, m, d; cin >> n >> m >> d;
  // n: number of people
  // m is number of connection
  // d: # days elapsed

  // key: name
  // value: integer 
  unordered_map<string, int> personToInt;

  // int --> # whispers needed
  vector<int> numWhispersNeeded(n);

  int numPeople = 0;

  for (int i = 0; i < n; i++) {
    string s; // name
    int t; // # of whispers needed
    cin >> s >> t;

    numWhispersNeeded[numPeople] = t;

    personToInt[s] = numPeople++;

  }

  vector<vector<int>> adjList(n);

  for (int i = 0; i < m; i++) {
    string u, v; cin >> u >> v;

    int uInt = personToInt[u];
    int vInt = personToInt[v];

    // populate adj list
    adjList[uInt].push_back(vInt);
    adjList[vInt].push_back(uInt);
  }

  // BFS starts with person r
  string r;
  cin >> r;
  int rInt = personToInt[r];


  vector<bool> heardWhisper(n, false);

  // run BFS:
  // pair: person aka node, day
  queue<pair<int, int>> q;

  // add the first person to the queue
  q.push({rInt, 1});
  heardWhisper[rInt] = true;

  int numPeopleHeardRumor = 0;

  while (!q.empty()) {
    auto [person, day] = q.front();
    q.pop();

    // if the day of this node has crossed 'd' then break
    // if day == d, then we can still process that person
    if (day > d) break;

    // visit all neighbors
    for (int neighbor : adjList[person]) {

      // set the flag to true if this person is hearing the rumor for the first time
      if (!heardWhisper[neighbor]) {
        heardWhisper[neighbor] = true;
        numPeopleHeardRumor++;
      }

      numWhispersNeeded[neighbor]--; // whisper to that person
      if (numWhispersNeeded[neighbor] == 0) {
        // add to the queue with day+1, this person is ready to whisper for the first time
        q.push({neighbor, day+1});
      }
      // dont add the person if they are not ready to whisper
      // or if they have already whispered before
    }
  }

  cout << numPeopleHeardRumor << '\n';

}

/*
modified BFS:
  only add to queue if:
    person has been whispered to enough times (decrement that counter, and once it reaches 0, add the queue)
  queue nodes need to have:
    the person that is now ready to whisper (node)
    the day it is (we stop processing the queue once the day number is too big)

global values:
  adj list (undirected)
  # times this person needs to be whispered to (remaining)
*/

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int numberOfTeams, numberOfEvents;
  cin >> numberOfTeams >> numberOfEvents;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  // maps team number to pair<# problems solved, total penalty>
  map<int, pair<int, int> > teamData;

  for (int i = 0; i < numberOfEvents; i++) {
    int teamNumber, penalty;
    cin >> teamNumber >> penalty;

    // this is the first time this team has submitted a problem
    if (teamData.find(teamNumber) == teamData.end()) {
      // add 1 problem and penalty score
      teamData[teamNumber] = pair<int, int>(1, penalty); 
    }
    else {
      // if team already exists, just add 1 problem and add penalty
      teamData[teamNumber].first += 1;
      teamData[teamNumber].second += penalty;
    }

    cout << "printing teams: \n";
    for (pair<int, pair<int, int> > team : teamData) {
      cout << "team number " << team.first << " problems solved " << team.second.first << " penalty " << team.second.second << endl;
    }

  }




  
}
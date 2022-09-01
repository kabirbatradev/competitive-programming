
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

// bool compare(pair<int, pair<int, int> >& a, pair<int, pair<int, int> >& b) {
//   // solving more problems is better
//   if (a.second.first > b.second.first) {
//     return true;
//   }
//   if (a.second.first < b.second.first) {
//     return false;
//   }
//   // same # problems means less penalty is better
//   return a.second.second < b.second.second;
// }

// bool compare(pair<int, int>& a, pair<int, int>& b) {
//   // solving more problems is better
//   if (a.first > b.first) {
//     return true;
//   }
//   if (a.first < b.first) {
//     return false;
//   }
//   // same # problems means less penalty is better
//   return a.second < b.second;
// }

struct SortStruct {
  bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
    if (a.first > b.first) {
      return true;
    }
    if (a.first < b.first) {
      return false;
    }
    // same # problems means less penalty is better
    return a.second < b.second;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  // cout.precision(10);

  int numberOfTeams, numberOfEvents;
  cin >> numberOfTeams >> numberOfEvents;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  // maps team number to pair<# problems solved, total penalty>
  // map<int, pair<int, int> > teamData;
  unordered_map<int, pair<int, int> > teamData;

  for (int i = 0; i < numberOfEvents; i++) {
    int teamNumber, penalty;
    cin >> teamNumber >> penalty;

    // this is the first time this team has submitted a problem
    if (teamData.find(teamNumber) == teamData.end()) {
      // add 1 problem and penalty score
      teamData[teamNumber] = pair<int, int>(1, penalty);
    } else {
      // if team already exists, just add 1 problem and add penalty
      teamData[teamNumber].first += 1;
      teamData[teamNumber].second += penalty;
    }

    // cout << "printing teams: \n";
    // for (pair<int, pair<int, int> > team : teamData) {
    //   cout << "team number " << team.first << " problems solved " <<
    //   team.second.first << " penalty " << team.second.second << endl;
    // }

    pair<int, int> team1Data = teamData[1];

    // vector<pair<int, pair<int, int> > > teamDataVector;
    // vector<pair<int, int> > teamDataVector;
    multiset<pair<int, int>, SortStruct> teamDataSet;
    for (auto& it : teamData) {
      teamDataSet.insert(it.second);
    }

    // sort(teamDataVector.begin(), teamDataVector.end(), compare);

    // cout << "printing teams from vector: \n";
    // for (pair<int, pair<int, int> > team : teamDataVector) {
    //   cout << "team number " << team.first << " problems solved " <<
    //   team.second.first << " penalty " << team.second.second << endl;
    // }

    // int rank = 1;
    // for (auto& it : teamDataVector) {
    //   // if this team has the same score as team 1, then break
    //   if (it.first == team1Data.first && it.second == team1Data.second) {
    //     break;
    //   }
    //   rank++;
    //   // otherwise we must be looking at a team that is better than team 1 so
    //   add 1 rank

    // }

    int rank = 1 + distance(teamDataSet.begin(), teamDataSet.find(team1Data));

    cout << rank << '\n';
  }
}
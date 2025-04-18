#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {
    int n; cin >> n;

    // adj list
    vector<vector<int>> adjList(n); // init to empty vectors
    // in degree counter
    vector<int> inDegree(n, 0); // init to 0 

    vector<int> meetingTimes(n);

    for (int i = 0; i < n; i++) {

      int minutes, numPre; cin >> minutes >> numPre;

      meetingTimes[i] = minutes;

      for (int j = 0; j < numPre; j++) {
        int prereq; cin >> prereq;
        prereq--; // of by one

        // i --> prereq NO
        // prereq --> i
        // adjList[i].push_back(prereq);
        adjList[prereq].push_back(i);

        // inDegree[prereq]++;
        inDegree[i]++;

      }

    }

    // cout << "indegrees" << endl;
    // for (int i = 0; i < n; i++) {
    //   cout << (i+1) << ": " << inDegree[i] << endl;
    // }



    // now run topo sort but with pq
    // insert if indegree is 0 
    // weight = length of meeting
    // data: meeting int

    // these are max by default? greater<> makes it min oop
    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    priority_queue<pair<int, int>> pq;

    // add nodes with in degree of 0 

    for (int i = 0; i < n; i++) {
      if (inDegree[i] == 0)
        pq.push({meetingTimes[i], i});
    }

    int worstMeetingTime = 0;
    int meetingsDone = 0;
    while (!pq.empty()) {
      auto [meetingTime, meetingNum] = pq.top(); pq.pop();

      // total meeting time: meetingTime + meetingsDone
      worstMeetingTime = max(worstMeetingTime, meetingTime + meetingsDone);

      // cout << (meetingNum+1) << endl;
      // cout << meetingTime << " " << meetingsDone << endl;

      meetingsDone++; // incremenet after


      // go through adj List and check if new in degree is 0 (decrement first)
      for (int neighbor : adjList[meetingNum]) {
        inDegree[neighbor]--;
        if (inDegree[neighbor] == 0) {
          // get meeting time of neighbor and put into pq
          pq.push({meetingTimes[neighbor], neighbor});
        }
      }
    }

    cout << worstMeetingTime << '\n';


  }
};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  // int t; cin >> t;
  // for (int i = 0; i < t; i++) 
    Solution s;
}



/*

topological sort:
every negotiation thing has prerequisites

but: we want to minimize the max meeting length

length of meeting is given
  but additional length added = # of meetings already completed

we should always do the longer meetings first (makes sense)
because if we did the later, it would always be worse
so in the top sort, we can use pq (max heap) to pick longer meetings first (this might be wrong)

i think greedy works... NOPE

wrong answer 4th test case
is there a case where pq is giving us the wrong thing
pq should give longest meeting (with in degree 0) first

but what if we wanted to process longer meetings first
and we should "complete search" the possibilities instead of greedily picking

might be better to take shorter meeting first to enable taking longer meeting earlier

*/
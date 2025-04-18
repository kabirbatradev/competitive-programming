#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  int n; 
  vector<int> priority;

  vector<vector<int>> adjList;

  vector<int> meetingTimes;


  Solution() {
    cin >> n;

    // adj list
    // vector<vector<int>> adjList(n); // init to empty vectors
    adjList.resize(n);
    // in degree counter
    vector<int> inDegree(n, 0); // init to 0 

    // vector<int> meetingTimes(n);
    meetingTimes.resize(n);

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

    // vector<int> priority(n, -1);
    priority.assign(n, -1); // -1 is dummy value, used to know if its alr computed
    for (int i = 0; i < n; i++) {
      getPriority(i); // sets the array value
    }





    // now run topo sort but with pq
    // insert if indegree is 0 
    // weight = length of meeting
    // data: meeting int

    // these are max by default? greater<> makes it min oop
    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // weight = priority
    // second weight = meeting time
    priority_queue<tuple<int, int, int>> pq;

    // add nodes with in degree of 0 

    for (int i = 0; i < n; i++) {
      if (inDegree[i] == 0)
        pq.push({priority[i], meetingTimes[i], i});
    }

    int worstMeetingTime = 0;
    int meetingsDone = 0;
    while (!pq.empty()) {
      auto [priorityWeight, meetingTime, meetingNum] = pq.top(); pq.pop();

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
          pq.push({priority[neighbor], meetingTimes[neighbor], neighbor});
        }
      }
    }

    cout << worstMeetingTime << '\n';


  }

  int getPriority(int i) {
    // do not get prio if it was alr computed!
    if (priority[i] != -1) return priority[i];


    // get the prio of i using adj list
    priority[i] = meetingTimes[i]; // default is this meeting time

    for (int neighbor : adjList[i]) {
      int prio = getPriority(neighbor); // use max prio of neighbor
      priority[i] = max(priority[i], prio); // if other guy prio is worse, then update this one
    }

    return priority[i];
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

what if we try to enable longer meetings first
so the priority = the longest meeting that it waits for

priority != meeting time
priority = meeting time of any meeting down the line....

make a list called priority (instead of meeting time)
note: if 2 nodes have same meeting time, then it doesnt matter? because the long meeting later is worse anyway
but we can give pq more info, the second val can be its actual meeting time

priority = max priority of the adjList (nodes that this is a pre req of)



now i TLE half way through..
what if i optimize get prioirty funtion
that helsp!
YES IT WORKS


*/
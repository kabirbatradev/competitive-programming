
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

  int n;
  cin >> n;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  // for every test case
  for (int tc = 0; tc < n; tc++) {
    int numberOfButtons, desiredTime;
    cin >> numberOfButtons >> desiredTime;

    // store seconds added per button in an array
    int secondsPerButton[numberOfButtons];
    for (int i = 0; i < numberOfButtons; i++) {
      int seconds;
      cin >> seconds;
      secondsPerButton[i] = seconds;
    }

    int minButtonPresses = 0;
    int minExtraTime = 0;

    // create map to use to check if we have already hit a specific time (so we dont loop infinitely)
      // map.find(key) == map.end() : key is not in map
      // map[time] = button presses
    // time, button presses
    // map<int, int> visitedTimes;

    // instead of a map, lets use an array from 0 to 3600 (1 hr)
    // set to -1 implies this time has not been visited (-1 button presses to reach this time)
    int visitedTimes[3601];
    for (int i = 0; i < 3601; i++) {
      visitedTimes[i] = -1;
    }

    // if we find the solution, print "buttonPresses 0"
    // if we do not find the solution and bfs ends
      // bfs ends when we go to 0 seconds or 1 hr (cannot go past)
      // and any new bfs paths lead to an already visited time
    // then go to the index in the array of the desiredTime, and go up until
    // we reach the "smallest achievable cooking time above the target", and print the
    // button presses and the difference in time (the extra time)

    // current button presses, current seconds sum
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0)); // push initial pair

    int closestTimeSoFar = 3600;

    while (!q.empty()) {
      pair<int, int> current = q.front();
      q.pop();
      int currentTime = current.second;
      int currentButtonPresses = current.first;

      // if current time is out of bounds, set to 0 or 1 hr
      if (currentTime < 0) currentTime = 0;
      if (currentTime > 3600) currentTime = 3600;

      // if this current time has already been visited, skip
      if (visitedTimes[currentTime] != -1) {
        continue;
      }

      // otherwise add it to visited times
      visitedTimes[currentTime] = currentButtonPresses;

      // if current seconds sum = desiredTime, that is the solution
      // we know it is the minimum button presses because bfs gives shortest path
      if (currentTime == desiredTime) {
        closestTimeSoFar = desiredTime;
        break;
      }

      // if it has not been visited but was not the solution, we should try every button (and add it to the queue)
      for (int i = 0; i < numberOfButtons; i++) {
        q.push(make_pair(currentButtonPresses + 1, currentTime + secondsPerButton[i]));
      }

      // update closestTimeSoFar just in case this current time is the best solution
      if (currentTime > desiredTime && currentTime < closestTimeSoFar) {
        closestTimeSoFar = currentTime;
      }

    }

    // if we made it here, that means either
    // we ran out of bfs without every hitting the solution
    // or we hit the solution

    minButtonPresses = visitedTimes[closestTimeSoFar];
    minExtraTime = closestTimeSoFar - desiredTime;

    cout << minButtonPresses << " " << minExtraTime << '\n';
  }
  
}
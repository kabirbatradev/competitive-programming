
// Time Limit Exceeded

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  // cout.precision(10);

  int width, height;
  cin >> width >> height;

  // initialize board
  string board[height];
  for (int i = 0; i < height; i++) {
    cin >> board[i];
  }

  // find player
  int playerRow, playerCol;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (board[i][j] == 'P') {
        playerRow = i;
        playerCol = j;
        i = height;
        j = width;  // break
      }
    }
  }

  pair<int, int> playerPos;
  playerPos.first = playerRow;
  playerPos.second = playerCol;

  // bfs until all paths are tried
  int totalGoldCollected = 0;
  queue<pair<int, int> > q;
  q.push(playerPos);

  while (!q.empty()) {
    pair<int, int> pos = q.front();
    q.pop();

    // MISSING LINK: check if this position has already been read but was put in the queue multiple times
    if (board[pos.first][pos.second] == '#') {
      continue;
    }

    // check if pos is gold
    if (board[pos.first][pos.second] == 'G') {
      totalGoldCollected++;
    }

    // set pos in board to # (wall) so we dont repeat
    board[pos.first][pos.second] = '#';

    // check if any nearby traps, (if not, then add nearby squares to queue if
    // they are not walls)
    bool nearbyTraps = false;
    // vector<pair<int, int> > newPositions;
    pair<int, int> newPositions[4];
    int newPosCount = 0;
    for (int i = 0; i < 4; i++) {
      pair<int, int> newPos;
      newPos.first = pos.first + dy[i];
      newPos.second = pos.second + dx[i];

      if (newPos.first < 0 || newPos.second < 0 || newPos.first >= height ||
          newPos.second >= width) {
        continue;
      }

      if (board[newPos.first][newPos.second] == 'T') {
        nearbyTraps = true;
        break;
      }

      // if the new position is a wall, do not add to queue
      if (board[newPos.first][newPos.second] == '#') continue;

      // newPositions.push_back(newPos);
      newPositions[newPosCount] = newPos;
      newPosCount++;
    }

    // do not put anything in the queue if there is a nearby trap
    if (nearbyTraps) {
      continue;
    }
    // add all the (non wall) new positions into the queue
    for (pair<int, int> pos : newPositions) {
      q.push(pos);
    }
  }

  cout << totalGoldCollected << endl;
}
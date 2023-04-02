
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;

  string start; cin >> start;
  string end; cin >> end;

  int moves = 0;
  for (int i = 0; i < n; i++) {
    int startdigit = start.at(i) - '0';
    int enddigit = end.at(i) - '0';

    int absDifference = abs(startdigit - enddigit);
    
    moves += min(absDifference, 10 - absDifference);
  }
  cout << moves << "\n";
  
}

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

  // string aabb = "aabb";
  string out;
  while (out.length() < n) {
    out += "aabb";
  }

  out = out.substr(0, n);

  cout << out << "\n";

}
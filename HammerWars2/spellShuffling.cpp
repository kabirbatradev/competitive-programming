
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(10);

  string s; cin >> s;

  // read string
  // convert to vector and sort
  vector<char> v(s.begin(), s.end());
  sort(v.begin(), v.end());

  // count and remove 0s
  int numZeros = 0;
  for (int i = 0; i < v.size(); i++) {
    if (v.at(i) == '0') {
      numZeros++;
      v.erase(v.begin() + i);
      i--;
    }
  }
  // convert vector to string
  string s2(v.begin(), v.end());

  // insert 0s back in after the first number
  s2.insert(1, numZeros, '0');

  cout << s2 << "\n";
  
}
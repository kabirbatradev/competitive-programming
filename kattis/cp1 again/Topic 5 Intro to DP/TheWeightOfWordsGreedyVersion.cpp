#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  // account for impossible cases early:
  int l, w; cin >> l >> w;
  if (w < l or w > l*26) {
    cout << "impossible" << '\n';
    return 0;
  }

  // set everything to weight = 1 aka 'a'
  vector<int> weights(l, 1);
  int sum = l; // keep track of current sum weight
  for (int i = 0; i < l; i++) {
    if (w - sum > 25) {
      weights[i] = 26;
      sum += 26 - 1; // note that we lost the 'a'=1 value in the running sum
    }
    else {
      weights[i] = w - sum+1; // add remaining sum needed
      break;
    }
  }
  for (int i : weights) {
    cout << (char)(i-1 + 'a');
  }
  cout << '\n';
}

/*
greedy: canonical coin change, always try largest weight firstr
set everything to 1 = 'a'
set things to z until need less than 26
that last letter can be the remaining needed
cast integers to chars: 
  1 --> 'a'
  1-1 + 'a'
*/
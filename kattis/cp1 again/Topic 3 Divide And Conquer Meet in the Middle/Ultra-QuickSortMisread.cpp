#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int n; cin >> n;

  vector<int> unsorted(n);

  for (int i = 0; i < n; i++) {
    int ai; cin >> ai;
    unsorted[i] = ai;
  }

  vector<int> sorted(unsorted);
  sort(sorted.begin(), sorted.end());

  for (int i = 0; i < n; i++) {
    cout << unsorted[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < n; i++) {
    cout << sorted[i] << " ";
  }
  cout << endl;


  // digit --> index in sorted
  unordered_map<int, int> m;
  for (int i = 0; i < n; i++) {
    int x = sorted[i];
    m[x] = i;
  }

  int swaps = 0;

  for (int i = 0; i < n; i++) {

    int x = unsorted[i];

    cout << i << " " << x << " " << m[x] << endl;


    // no swap needed if already correct position
    if (m[x] == i) continue; 

    // otherwise swap this element with where it is supposed to go
    // supposed to go to m[x]
    cout << "swapping " << m[x] << " " << i << endl;
    swap(unsorted[m[x]], unsorted[i]);
    swaps++;
    // note, the element here now is probably still wrong, so decrement i to process it again
    i--;

  }

  for (int i = 0; i < n; i++) {
    cout << unsorted[i] << " ";
  }
  cout << endl;


  cout << swaps << '\n';
}

/*
idea: 
sort the array
create a map: element --> index (integers are distinct)

for each element in unsorted array, swap it with the index where it should be (if its not already there)
  get that position using the map
after the swap, there is potential for that element to end up where it is supposed to be, so u wouldnt need that swap

idk if this is optimal # of swaps but gut feeling says it is
*/
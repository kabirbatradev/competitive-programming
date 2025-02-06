#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int getWeight(int population, int boxesAssigned) {
  return ceil((double)population / boxesAssigned);
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  while (true) {
    int n, b; cin >> n >> b;
    if (n == -1) break;

    /*
    for every city: 
      population
      boxes assigned currently
    
    pq: 
      weight = ppl per box = population / boxes assigned, but rounded up
        = ceil((double)population / boxes assigned)
      attached value: city index
    
    pop from pq:
      increment boxes assigned to city
      push back into pq weight = population / boxes assigned
    */

    // pair of population, boxes assigned
    vector<pair<int,int>> cityData(n);

    // pair of weight, city index
    priority_queue<pair<int,int>> pq;

    for (int i = 0; i < n; i++) {
      int pop; cin >> pop;
      cityData[i].first = pop;
      cityData[i].second = 1; // give a box
      b--; // used a box

      pq.push(make_pair(getWeight(pop, cityData[i].second), i));
    }

    // while we still have boxes left, give boxes to the worst case cities
    while (b > 0) {
      // remove worst city
      auto [weight, index] = pq.top(); pq.pop();
      auto& city = cityData[index];

      city.second++; // give another box to this city
      b--;

      int newWeight = getWeight(city.first, city.second);

      // insert city back 
      pq.push(make_pair(newWeight, index));
    }

    // print the next worst city's weight = ratio of ppl / boxes (rounded up)
    cout << pq.top().first << '\n';

    cin.ignore(2); // ignore \n after int, and another \n
  }
}
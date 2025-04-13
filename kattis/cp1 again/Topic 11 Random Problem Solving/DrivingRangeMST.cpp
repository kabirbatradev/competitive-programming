// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
#define int long long // replace all "int" with "long long"
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

// modified from https://github.com/stevenhalim/cpbook-code/blob/master/ch2/ourown/unionfind_ds.cpp
typedef vector<int> vi;

class UnionFind {                                // OOP style
private:
  vi p; // p means parents
  // vi rank;
  vi setSize;                           
  int numSets;
public:
  UnionFind(int N) {
    // p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i; // initialze parents to self
    p.resize(N);
    iota(p.begin(), p.end(), 0);
    // rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    numSets = N;                                 // optional feature
  }

  // recursive find()
  int findSet(int i) {
    return (p[i] == i) ? i : (p[i] = findSet(p[i]));
  }

  bool isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
  }

  int numDisjointSets() { return numSets; }      // optional
  int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

  // union by rank, update size and # sets
  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items

    // y should be the parent

    // if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    // p[x] = y;                                    // set x under y
    // if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    
    // can also consider union by size instead of rank:
    if (setSize[x] > setSize[y]) swap(x, y);
    p[x] = y;

    setSize[y] += setSize[x];                    // combine set sizes at y
    --numSets;                                   // a union reduces numSets
  }
};

struct Solution {
  Solution() {
    int n, m; cin >> n >> m;

    // weight, a, b
    vector<tuple<int,int,int>> edges(m);
    for (int i = 0; i < m; i++) {
      int a, b, len;
      cin >> a >> b >> len;
      edges[i] = {len, a, b};
    }

    // run kruskals:
    // sort min weight first
    sort(edges.begin(), edges.end());

    UnionFind UF(n);
    int lastWeightUsed = 0;
    for (auto [weight, a, b] : edges) {
      if (UF.isSameSet(a, b)) continue;

      UF.unionSet(a, b);
      lastWeightUsed = weight;
      
      // short circuit return early
      if (UF.numDisjointSets() == 1) {
        cout << lastWeightUsed << '\n';
        return;
      }
    }

    // guaranteed we failed if we got here
    cout << "IMPOSSIBLE" << '\n';
  }
};

// using "signed" works around "int" being replaced with long long
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cin.exceptions(cin.failbit); // idk what this does but it prevents me from doing while (cin >> n)
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places

  // int t; cin >> t;
  // for (int i = 0; i < t; i++) 
    Solution s;
}

/*
goal: connect all the cities such that the distance between any 2 pair of cities is minimized 
given set of edges

output minimum max distance between 2 cities
impossible if not all cities are connected

idea 1: BSTA: given a max edge weight, can we connect all the cities? can function is simply DFS
  runtime: log(10^9) * (V+E)

idea 2: MST: will use the smallest edges until all cities are connected
  use Kruskals algo to go through edges in sorted order
  the weight of the last edge used is the answer! 
  runtime: E log E 

about the same runtime?
*/
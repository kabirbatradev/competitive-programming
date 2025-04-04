// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;



// union find data structure:
// https://github.com/stevenhalim/cpbook-code/blob/master/ch2/ourown/unionfind_ds.cpp

// modification: 
  // create dummy nodes too
typedef vector<int> vi;

class UnionFind {                                // OOP style
private:
  vi p;
  // vi rank;
  vi setSize;                           // vi p is the key part
public:
  int N;
  vector<ll> sumOfSet; // need longs here!
  vector<int> numElements;
  int numSets;
public:
  UnionFind(int N) : N(N) {

    p.assign(2*N, 0); // double the size

    // make normal node parent be the dummy node
    for (int i = 0; i < N; ++i) {
      p[i] = N + i;
    }

    // initialize dummy notes (parent is itself)
    for (int i = N; i < 2*N; ++i) {
      p[i] = i;
    }

    // // initialize all nodes as normal
    // for (int i = 0; i < 2*N; ++i) {
    //   p[i] = i;
    // }


    // rank.assign(2*N, 0);                           // optional speedup
    setSize.assign(2*N, 1);                        // optional feature

    // there are only N sets, because all of the normal nodes are already connected to parent nodes
    numSets = N;                                 // optional feature

    sumOfSet.assign(2*N, 0);
    numElements.assign(2*N, 0); // size, but it doesnt include dummy nodes

    // initialze sum of every sum
    // dummy nodes have sum of 0
    // actual nodes have actual sum

    // // normal nodes:
    // for (int i = 0; i < N; ++i) {
    //   sumOfSet[i] = i;
    // }

    // // dummy nodes have no sum
    // for (int i = N+1; i < 2*N; ++i) {
    //   sumOfSet[i] = 0;
    // }

    // for every normal node, the parent sum should be the value of that node
    for (int i = 0; i < N; ++i) {
      sumOfSet[N+i] = i+1; // node value is off by one
      numElements[N+i] = 1;
    }

    // // union all of the normal nodes with their respective dummy parent nodes
    // for (int i = 0; i < N; ++i) {
    //   unionSet(i, i+N); // union the node with its dummy parent
    // }

  }

  int findSet(int i) { 
    // cout << "find set: i = " << i << endl;
    return (p[i] == i) ? i : (p[i] = findSet(p[i])); 
  }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int numDisjointSets() { return numSets; }      // optional
  // int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional
  int sizeOfSet(int i) { return numElements[findSet(i)]; } // modified to use our own array
  ll sumOfSetFunction(int i) { return sumOfSet[findSet(i)]; } // modified to use our own array

  // modify: also union the sum
  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (setSize[x] > setSize[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    // if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    setSize[y] += setSize[x];                    // combine set sizes at y
    --numSets;                                   // a union reduces numSets

    // y is the parent
    sumOfSet[y] += sumOfSet[x];
    numElements[y] += numElements[x];
  }



  // x --> y (root of y is the parent)
  void move(int x, int y) {
    // get roots
    int rootY = findSet(y);
    int rootX = findSet(x);
    // cout << rootX << " " << rootY << endl;

    if (rootY == rootX) return; // doesnt make a difference

    // move element, parent of x should now be y 
    p[x] = rootY;

    // fix sizes:
    setSize[rootY] += 1;
    setSize[rootX] -= 1;

    // fix num elements (counter that does not include dummy nodes)
    numElements[rootY] += 1;
    numElements[rootX] -= 1;

    sumOfSet[rootY] += x + 1; // same off by one error here
    sumOfSet[rootX] -= x + 1;

  }

  void printParents() {
    for (int i = 0; i < 2*N; i++) {
      cout << "parent of " << i << " is " << p[i] << endl;
    }
  }
};


struct Solution {
  Solution(int n, int m) {

    // n nodes
    // initialize union find data structure:
    UnionFind UF(n);

    // m commands:
    for (int i = 0; i < m; i++) {
      int command;
      cin >> command;

      // cout << command << endl;

      // UF.printParents();

      // union
      if (command == 1) {

        int p, q;
        cin >> p >> q;
        p--;
        q--;

        
        // int rootY = UF.findSet(p);
        // int rootX = UF.findSet(q);
        // cout << rootX << " " << rootY << endl;

        UF.unionSet(p, q);
        // cout << "command 1" << endl;
      }

      // move
      else if (command == 2) {
        int p, q;
        cin >> p >> q;
        p--;
        q--;

        // int rootY = UF.findSet(p);
        // int rootX = UF.findSet(q);
        // cout << rootX << " " << rootY << endl;

        // p --> q
        UF.move(p, q);
        // cout << "command 2" << endl;

      }

      // return # elements and sum of elements
      else {
        int x; cin >> x;
        x--;

        cout << UF.sizeOfSet(x) << ' ' << UF.sumOfSetFunction(x) << '\n';
        // cout << "command 3" << endl;
      }
    }

  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places

  int n, m;
  while (cin >> n >> m) {

    // cout << n << " " << m << endl;
    Solution s(n, m);

  }
  
}





/*
union find, but we should be able to move an element
keep track of # elements, and sum of elements

operations we need to do 
  union
  find
  move one element

classic union find
  union
  find
  information stored with root node
  also need to keep track of sum of elements

modify the original union find:
  create dummy node for every original node
  all normal nodes will always be a leaf node
  then move is easy

how to do dummy nodes:
  total # nodes = 2*n
  nodes from n+1 to 2n are dummy nodes:
    for node i, the parent dummy node is n+i


how to implement move:
  assumption: all nodes are leaves
  move x --> y
  change the parent of node: 
    root of y = find(y)
    parent[x] = root of y;
  
  adjust the sizes, and the sum
    size of rootY += 1
    size of rootX -= 1
    same with # elements (more important)

    sum of rootY += x
    sum of rootX -= x

  
*/
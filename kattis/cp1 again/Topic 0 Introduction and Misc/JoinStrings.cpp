// Author: Kabir batra
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;

// linked list node
struct Node {
  Node* next = nullptr;
  Node* last = nullptr;
  string val;
  // Node(string val) : val(val) {}
  Node() {
    last = this;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int N; cin >> N;

  // keep track of all strings as linked list nodes
  Node strings[N];

  for (int i = 0; i < N; i++) {
    cin >> strings[i].val;
  }

  int finalStringIndex = 0;
  for (int i = 0; i < N-1; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--; // shift to 0 indexed

    // put b after a:
    strings[a].last->next = &strings[b]; // add to end of chain
    strings[a].last = strings[b].last; // make the last of this into the last of the chain
    finalStringIndex = a;
  }

  // go through linked list and print strings in order
  Node *current = &strings[finalStringIndex];
  while (current != nullptr) {
    cout << current->val;
    current = current->next;
  }

}
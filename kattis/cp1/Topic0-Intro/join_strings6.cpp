

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

// graph --> linkedlist solution
struct node
{
    string data;
    node *next;
    node *end;
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int numStrings; 
    cin >> numStrings;

    // string strings[numStrings]; // all the strings; this array never changes
    // I want an array of nodes where the index corresponds to the position of the string
    node *strings[numStrings];
    
    for (int t = 0; t < numStrings; t++) {
        node *tmp = new node;
        cin >> tmp->data;
        tmp->next = NULL;
        tmp->end = tmp;
        strings[t] = tmp;
    }

    // for (int i = 0; i < numStrings; i++) {
    //   cout << strings[i]->data << " ";
    // }
    // cout << endl;

    node *lastANode = NULL;
    for (int t = 0; t < numStrings - 1; t++) {
        int a, b;
        cin >> a;
        cin >> b;
        a--; b--; // already subtracted 1

        node *aNode = strings[a];
        node *bNode = strings[b];
        // cout << aNode->data << ", " << bNode->data << "\n";

        // store the last one so that we can print everything out after
        if (t == numStrings - 2) {
          lastANode = aNode;
        }
        
        node *endOfAChain = aNode->end;
        
        // while (aNode->next != NULL) {
        //   aNode = aNode->next;
        // }

        endOfAChain->next = bNode;
        aNode->end = bNode->end;

    }

    if (lastANode == NULL) {
      lastANode = strings[0];
    }
    // print at the end
    while (true) {
      cout << lastANode->data;
      if (lastANode->next == NULL) {
        break;
      }
      lastANode = lastANode->next;
    }
    cout << endl;


}

// use graphs where
// strings represent nodes
// a, b represents a connection between nodes
// by the end, we end up with a long linked list and we print the list out

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
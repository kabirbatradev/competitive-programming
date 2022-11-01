

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

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int numStrings; 
    cin >> numStrings;

    
    string strings[numStrings]; // all the strings; this array never changes
    vector<int> aliases; // integers that point to the strings; this list shifts around to represent the order of the strings
    int director[numStrings]; // integers that convert "a"-1 to the index in aliases

    int N = (int)1e5;
  
    aliases.reserve(N);

    int counters[numStrings]; // keeps track of how many strings come after

    for (int t = 0; t < numStrings; t++) {
        cin >> strings[t];

        aliases.push_back(t);
        director[t] = t;

        counters[t] = 0;
    }

    // cout << "initial position: " << endl;
    // for (int i = 0; i < aliases.size(); i++) {
    //     cout << strings[aliases[i]];
    // }
    // cout << endl;

    // cannot be faster than n time
    for (int t = 0; t < numStrings - 1; t++) {
        int a, b;
        cin >> a;
        cin >> b;
        a--; b--; // already subtracted 1

        int bIndex;
        // int index = 0;

        // want to optimise this while loop because it is slow
        // while (true) {
        //     if (aliases[index] == b) {
        //         bIndex = index;
        //         break;
        //     }

        //     int skips = counters[aliases[index]];
        //     for (int i = 0; i < skips; i++) {
        //         index++;
        //     }
        //     index++;
        // }

        // director[b] is position of b alias in aliases
        bIndex = director[b];


        // cout << "\nfound b at index: " << bIndex << endl;

        vector<int> bChain;
        int bChainLen = bChain.size();
        int bChainLen = counters[b] + 1; // everything in the chain including itself

        // can this be optimized?
        for (int i = 0; i < bChainLen; i++) {
            bChain.push_back(aliases[bIndex]);
            aliases.erase(aliases.begin() + bIndex); // delete the entire b chain
        }

        // if the entire b chain is deleted, we need to tell director how everything was shifted over.
        // everything after b chain is moved over
        // director is 0, 1, 2, 3, 4, 5...
        // we delete 2, 3
        // director should be 0, 1, [-1, -1,] 2-2, 3-2

        // THIS WONT WORK!!!!
        // you cant really just iterate through director because the bChain is not the order of director
        for (int i = 0; i < bChainLen; i++) {
          director[i + b] = -1;
        }
        for (int i = bIndex + bChainLen; i < numStrings; i++) {
          director[i] = director[i] - bChainLen;
        }

        // cout << "bchain: ";
        // for (int x : bChain)
        //     cout << strings[x] << " ";
        // cout << endl;

        // cout << "aliases vector: " << endl;
        // for (int x : aliases)
        //     cout << strings[x] << " ";
        // cout << endl;

        int aIndex;
        // index = 0;

        // this while loop is also slow
        // while (true) {        
        //     // cout << aliases[index] << " at index: " << index << endl;
        //     if (aliases[index] == a) {
        //         aIndex = index;
        //         break;
        //     }

        //     int skips = counters[aliases[index]]; // out of bounds?
        //     for (int i = 0; i < skips; i++) {
        //         index++;
        //     }
        //     index++;
        // }

        aIndex = director[a];


        // cout << "\nfound a at index: " << aIndex << endl;

        aliases.insert(aliases.begin() + aIndex + counters[a] + 1, bChain.begin(), bChain.end()); // out of bounds?

        // we need to tell director how everything after a chain was shifted over
        // director is 0, 1, 2, 3, 4, 5...
        // we delete 2, 3
        // director should be 0, 1, ?, ?, 2, 3
        // we add 2, 3 back at the end
        // director should be 0, 1, [4, 5,] 2, 3
        // if instead, we add 2, 3 after 0
        // aliases is 0, 2, 3, 1, 4, 5
        // director should be 0, 1+2, [1, 2,] 2+2, 3+2

        // the bChain...
        // for (int i = 0; i < bChainLen; i++) {
        //   director[i + aIndex + counters[a]] = -1;
        // }
        // for (int i = bIndex + bChainLen; i < numStrings; i++) {
        //   director[i] = director[i] - bChainLen;
        // }
        // WONT WORK

        counters[a] += 1 + counters[b];


        // for (int x : aliases)
        //     cout << strings[x] << " ";
        // cout << endl;

        // for (int x : counters)
        //   cout << x << " ";
        // cout << endl;

    }

    // cout << "end" << endl;
    for (int x : aliases)
      cout << strings[x];
    cout << endl;

    

}


// the while loops that look for the node that represents index a and b is very slow
// i could have another array that stores the position of these nodes
// checking position a in this nodePositions array would give you the position in of a in 
// the actual aliases vector

// if this does not work, use graphs where
// strings represent nodes
// a, b represents a connection between nodes
// by the end, we end up with a long linked list and we print the list out


// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp


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

// #define PI 3.1415926535897932384626433832795

// runtime error might mean trying to index out of bounds

int main() {
    // std::ios::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
    // cout.precision(10);

    int numStrings; 
    cin >> numStrings;

    
    string strings[numStrings]; 
    vector<int> aliases;

    int N = (int)1e5;
  
    // Reserve space
    aliases.reserve(N);

    int counters[numStrings]; // keeps track of how many strings come after

    for (int t = 0; t < numStrings; t++) {
        cin >> strings[t];
        aliases.push_back(t);
        counters[t] = 0;
    }

    // cout << "initial position: " << endl;
    // for (int i = 0; i < aliases.size(); i++) {
    //     cout << strings[aliases[i]];
    // }
    // cout << endl;

    for (int t = 0; t < numStrings - 1; t++) {
        int a, b;
        cin >> a;
        cin >> b;
        a--; b--;

        int bIndex;
        int index = 0;
        while (true) {
            if (aliases[index] == b) {
                bIndex = index;
                break;
            }

            int skips = counters[aliases[index]];
            for (int i = 0; i < skips; i++) {
                index++;
            }
            index++;
        }
        // cout << "\nfound b at index: " << bIndex << endl;

        vector<int> bChain;
        int bChainLen = counters[b] + 1;
        for (int i = 0; i < bChainLen; i++) {
            bChain.push_back(aliases[bIndex]);
            aliases.erase(aliases.begin() + bIndex);
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
        index = 0;
        while (true) {        
            // cout << aliases[index] << " at index: " << index << endl;
            if (aliases[index] == a) {
                aIndex = index;
                break;
            }

            int skips = counters[aliases[index]]; // out of bounds?
            for (int i = 0; i < skips; i++) {
                index++;
            }
            index++;
        }
        // cout << "\nfound a at index: " << aIndex << endl;

        aliases.insert(aliases.begin() + aIndex + counters[a] + 1, bChain.begin(), bChain.end()); // out of bounds?

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

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
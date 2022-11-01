

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

int main() {
    // std::ios::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
    // cout.precision(10);

    while (true) {
        int r;
        cin >> r;

        string line;
        getline(cin, line); // get rid of "\n"


        if (r == 0) {
            break;
        }

        for (int l = 0; l < r; l++) {
            getline(cin, line);
            bool filled = false;
            for (char c : line) {
                if (c == "#") {
                    filled = true;
                }
                // if () // i want to use java spit
                cout << "'" << c << "'" << endl;
            }
            cout << "\n";

        }


    }

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
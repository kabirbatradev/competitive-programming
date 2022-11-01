

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
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // cout.precision(10);

    while (true) {
        int num_rects;
        cin >> num_rects;
        if (num_rects == 0) {
            break;
        }

        bool grid[501][501];

        for (int i = 0; i < 501; i++) {
        for (int j = 0; j < 501; j++) {
            grid[i][j] = false;
        }
        }

        for (int rect = 0; rect < num_rects; rect++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            
            // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

            for (int i = x1; i < x2; i++) {
                for (int j = y1; j < y2; j++) {
                    // cout << i << ", " << j << endl;
                    grid[i][j] = true;
                }
            }
        }

        int sum = 0;

        for (int i = 0; i < 501; i++) {
        for (int j = 0; j < 501; j++) {
            if(grid[i][j]) sum++;
            }
        }
        
        cout << sum << "\n";


       
    }

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
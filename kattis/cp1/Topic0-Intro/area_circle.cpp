
// i kinda dont know what im supposed to add cuz 
// ive never used cpp before so dont judge me too 
// harshly XD
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

#define PI 3.1415926535897932384626433832795

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cout.precision(10);
    
    double r, m, k;
    cin >> r;
    cin >> m;
    cin >> k;
    // cout << r << m << k << "\n";
    while (true) {
        if (r == 0 && m == 0 && k == 0) {
            break;
        }
        // area of the circle
        // area of the square times proportion of points inside
        cout << PI * r * r << " " << (4 * r * r) * (1.0 * k / m) << "\n";

        cin >> r;
        cin >> m;
        cin >> k;

    }
    
}
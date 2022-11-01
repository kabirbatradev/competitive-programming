
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

int main()
{


    vector<int> aliases;
    for (int i = 0; i < 10; i++) {
        aliases.push_back(i);
    }

    vector<int> bChain;
    int bChainLen = 2;
    for (int i = 0; i < bChainLen; i++) {
        bChain.push_back(aliases[2]);
        aliases.erase(aliases.begin() + 2);
    }

    aliases.insert(aliases.begin() + 5, bChain.begin(), bChain.end());

    for (int x : aliases)
        cout << x << " ";
    cout << endl;
    for (int x : bChain)
        cout << x << " ";
    cout << endl;

    return 0;
}

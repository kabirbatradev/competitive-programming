

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

    string space = "";

    while (true) {
        int r;
        cin >> r;

        if (r == 0) {
            break;
        }

        cout << space;
        int pile1 = 0;
        int pile2 = 0;

        // 0 is drop, 1 is take
        vector<bool> commands;
        vector<int> counts;

        int takeTotal = 0;
        int movedAlready = 0;

        for (int i = 0; i < r; i++) {
          

          int count;
          string command;
          cin >> command >> count;
          commands.push_back(command == "DROP" ? 0 : 1);
          counts.push_back(count);

        }

        for (int i = 0; i < r; i++) {
          bool command = commands.at(i);
          int count = counts.at(i);

          if (command == 0) {
            pile2 += count;
            cout << "DROP 2 " << count << "\n";
          } else { // TAKE

            // if there are enough
            if (pile1 >= count) {
              pile1 -= count;
              cout << "TAKE 1 " << count << "\n";
            } 
            // there are not enough
            else {
              if (pile1 != 0) {
                cout << "TAKE 1 " << pile1 << "\n";
              }
              pile1 = 0;


              // dont just move them all over; first check if movedAlready + count > takeTotal
              // if it is greater, then only move over takeTotal - movedAlready
              // leave the rest on pile2

              if (movedAlready + count > takeTotal) {
                pile1 += takeTotal - movedAlready;
                pile2 -= takeTotal - movedAlready;
              }

              // WAIT this doesnt work because if we only move over some, then we arent taking the newest plates



              // pile1 = pile2;
              // pile2 = 0;
              // cout << "MOVE 2->1 " << pile1 << "\n";

              // pile1 -= count;
              // cout << "TAKE 1 " << count << "\n";

            }

          }
        }

        space = "\n";
        



    }

}

// drop plates on table 2
// once take command comes, put all the plates on table 1 so they flip
// then take from table 1
// if there are any more drops, drop them on table 2
// then when a take comes around, take it from table 1 until its empty
// after table 1 is empty, then get everything on table 2 and flip it and take from table 1

// other option is to see the take in advance and move all the plates currently on table 1 back
// to table 2, then taking, and then moving all of that back to table 1
// this seems to add an extra move though, which is bad

// there must be a balance between extra moves, and too many "waiting till table 1 is empty"?


// the problem seems to be that you could be dropped 10000 plates, and then asked to take only 2
// I would still move all 10000 plates over, which is extra work!
// I need to look ahead at all the takes to see what the total takes are so i dont move over more than i need to

// but if i dont move everything over, then i will leave behind the newest plate!
// instead, i need to take only the number of plates i need; then I put the rest of the plates on the other pile
// then, I flip the plates that i calcuated i needed and then return them before being done


// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
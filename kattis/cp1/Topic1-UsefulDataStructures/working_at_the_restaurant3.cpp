

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
        int totalDropped = 0;

        for (int i = 0; i < r; i++) {

          int count;
          string command;
          cin >> command >> count;

          if (command == "TAKE") {
            takeTotal += count;
          }

          commands.push_back(command == "DROP" ? 0 : 1);
          counts.push_back(count);

        }

        for (int i = 0; i < r; i++) {
          bool command = commands.at(i);
          int count = counts.at(i);

          if (command == 0) { // DROP (giving you plates)

// when we reach plates we need, we flip everything over
// if we are given more plates than we actually need, then put some in the stack and all the extra on the other side
// if there are already flipped plates onthe other side, then we unflip them before putting extra plates
// then we only flip them back over if a take command is issued

            // if (totalDropped + count <= takeTotal) {
              // put the plates on pile 2
              pile2 += count;
              totalDropped += count;
              cout << "DROP 2 " << count << "\n";
            // }

            // next count given will exceed the take total
            // else {

            // }



            
          } else { // TAKE

            // if there are enough
            if (pile1 >= count) {
              pile1 -= count;
              cout << "TAKE 1 " << count << "\n";
            } 
            // there are not enough
            else {

              int remaining = count;

              if (pile1 != 0) {
                cout << "TAKE 1 " << pile1 << "\n";
                remaining -= pile1;
              }
              pile1 = 0;

              // now we have to flip plates from pile 2 
              pile1 = pile2;
              pile2 = 0;
              cout << "MOVE 2->1 " << pile1 << "\n";

              pile1 -= remaining;
              cout << "TAKE 1 " << remaining << "\n";


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


// imagine final state:
// we have plates unflipped in pile1
// we have plates flipped in pile2
// we have 10000 drops, which exceeds how many takes we actually need to do
// lets move the flipped plates back to pile1
// keep track of how many that is (x)
// -- insert problem
// now, pile1 has all of the old unflipped plates (older stack of x on top of the rest)
// then lets dump all the plates we calculate we will never flip onto pile2
// and drop all the plates we do want to flip onto pile1

// then flip them all from 1 to pile2 and save that count as (y)
// now flip back the x plates from 1 to 2

// ^these two can just be combined in one step
// take those x plates
// then flip all the other plates on pile 2 to pile 1 (because they are older) count them as z
// then take those z plates as well as the y plate from pile 1
// the rest of the trash plates will be sitting there unflipped on pile1 



// possible problem is we move too many flipped plates back to pile1
// we just had way too many flipped plates
// we need to know in advance before flipping plates whether we should flip all of them before
// reaching the step which requires us to not flip all of them. 
// lets ignore this problem for now (ima be mad but i will know what to do lmao)


// in the end, what we are doing is
// putting all the plates on the side
// when we reach plates we need, we flip everything over
// if we are given more plates than we actually need, then put some in the stack and all the extra on the other side
// if there are already flipped plates onthe other side, then we unflip them before putting extra plates
// then we only flip them back over if a take command is issued

// I NEVER NEEDED TO DO ANY OF THISABISJDFOABIHSDIFHOUIBSADFOHUISBD


// 4
// DROP 100
// TAKE 50
// DROP 50
// TAKE 100


// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();

        queue<int> q; // queue of all recently fallen dominoes
        for (int i = 0; i < n; i++) {
            char c = dominoes[i];
            if (c != '.') {
                q.push({i});
            }
        }

        
        // while new stuff still just fell
        while (!q.empty()) {


            // process all of the falling dominoes of this second
            unordered_map<int, pair<bool, bool>> fallingNeighbors;
            while (!q.empty()) {
                int index = q.front(); q.pop();
                char dir = dominoes[index];

                // mark the neighbor as now falling (if not already fallen)
                if (dir == 'L') {
                    int neighbor = index-1;
                    // check in range and is standing (not already fallen)
                    if (0 <= neighbor && dominoes[neighbor] == '.') {
                        // mark as falling left
                        fallingNeighbors[neighbor].first = true; 
                    }
                }
                else {
                    int neighbor = index+1;
                    // check in range and is standing (not already fallen)
                    if (neighbor < n && dominoes[neighbor] == '.') {
                        // mark as falling right
                        fallingNeighbors[neighbor].second = true; 
                    }
                }
            }

            // now go through all falling neighbors, and skip the ones
            // that are falling in both directions
            for (auto [index, dirPair] : fallingNeighbors) {
                auto [left, right] = dirPair;
                if (left && right) {
                    continue;
                }

                // update the state, and add to the queue
                dominoes[index] = left ? 'L' : 'R';
                q.push(index);
            }


        }

        // dominoes stoppped falling
        // state should be up to date
        return dominoes;
        
    }
};

/*
simulate the dominos:
some are pushed left, some are pushed right
its just an array of dominos

it takes one second for a domino to push the next domino
so we should process everything per second

we could put all dominos on a queue
once a second has passed:
we have to note the dominos that were pushed twice (left and right)
    and remove these dominos

how should we represent this?
one queue for the "current second"
maybe a map that maps from a position to a pair of 2 bools (left or right)

then once everything of this current second is processed
we go through the map
and for every item, if both are true, then skip it, but otherwise we should simulate that domino
so if its going left, 
    first, update the state itself
    then put the left domino in the queue for the next second (if its not already knocked over)
*/
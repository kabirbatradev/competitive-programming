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
            // second queue is for future things
            // but also we want to skip stuff that is already marked?
            // i guess the second queue can just be indices
            // and we skip if already marked:
            // we use the value in the dominoes thing
                // can set it to . + 1 for left
                // . + 2 for right
                // if its . + 3, then it was both so we are cooked (skip)

            queue<int> secondQueue;
            
            while (!q.empty()) {
                int index = q.front(); q.pop();
                char dir = dominoes[index];

                // mark the neighbor as now falling (if not already fallen)
                if (dir == 'L') {
                    int neighbor = index-1;
                    // check in range and is standing (not already fallen)
                    if (0 <= neighbor && dominoes[neighbor] != 'R' && dominoes[neighbor] != 'L') {
                        // mark as falling left
                        // fallingNeighbors[neighbor].first = true; 
                        dominoes[neighbor]++;
                        secondQueue.push(neighbor);
                    }
                }
                else {
                    int neighbor = index+1;
                    // check in range and is standing (not already fallen)
                    if (neighbor < n && dominoes[neighbor] != 'R' && dominoes[neighbor] != 'L') {
                        // mark as falling right
                        // fallingNeighbors[neighbor].second = true; 
                        dominoes[neighbor] += 2;
                        secondQueue.push(neighbor);
                    }
                }
                
            }

            // now go through all falling neighbors, and skip the ones
            // that are falling in both directions
            while (!secondQueue.empty()) {
                int index = secondQueue.front(); secondQueue.pop();
                // get the direction falling from dominoes
                if (dominoes[index] == '.' + 3) {
                    // both directions case 
                    dominoes[index] = '.'; // reset it though
                    continue;
                }
                else if (dominoes[index] == '.' + 1) {
                    // left case
                    dominoes[index] = 'L';
                    q.push(index);
                }
                else if (dominoes[index] == '.' + 2) {
                    // right case
                    dominoes[index] = 'R';
                    q.push(index);
                }
                // other case is its already set, so do nothing
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
class Solution {
public:
    vector<vector<string>> configurations;
    int N;
    vector<vector<string>> solveNQueens(int n) {
        N = n;
        traverse(n, make_pair(0, 0), vector<pair<int, int>>());
        return configurations;
    }
    
    // can have occupied diagonals i + j or i - j
    // can have occupied rows and columns
    void traverse(int numRemainingQueens, pair<int, int> currentPos, vector<pair<int, int>> placedPositions) {

        // if no more queens, push back this configuration
        if (numRemainingQueens == 0) {
            string s(N, '.');
            vector<string> config;
            for (int i = 0; i < N; i++) 
                config.push_back(s); // strings are cloned so they can be edited separately
            // config[0][0] = 'Q';
            for (pair<int, int> pos : placedPositions) {
                config[pos.first][pos.second] = 'Q';
            }
            configurations.push_back(config);
            return;
        }

        // if no more positions bc off the board, return
        if (currentPos.first >= N || currentPos.second >= N) {
            // technically dont need to check second?
            return;
        }

        // set next position
        pair<int, int> nextPos;
        if (currentPos.second == N-1) {
            // if in last column
            nextPos.second = 0;
            nextPos.first = currentPos.first+1;
        }
        else {
            nextPos.second = currentPos.second+1;
            nextPos.first = currentPos.first;
        }
        
        // consider not placing queen
        traverse(numRemainingQueens, nextPos, placedPositions);
        
        // also consider placing queen in next position, if possible
        for (pair<int, int> pos : placedPositions) {
            // no need to check row because we already guarantee that we do not place in the same row
            // i
            // if (pos.first == currentPos.first) {
            //     return;
            // }
            // j
            if (pos.second == currentPos.second) {
                return;
            }
            // i+j
            if (pos.first + pos.second == currentPos.first + currentPos.second) {
                return;
            }
            // i-j
            if (pos.first - pos.second == currentPos.first - currentPos.second) {
                return;
            }
        }

        // if we have not returned, then we can place the queen
        numRemainingQueens--;
        placedPositions.push_back(currentPos);

        // time save: next position should skip this row if we place queen on this row
        nextPos.first = currentPos.first+1; // next row
        nextPos.second = 0; // first col

        traverse(numRemainingQueens, nextPos, placedPositions);

        return;
    }
};
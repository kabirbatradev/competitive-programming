class Solution {
public:
    vector<vector<string>> configurations;
    int N;
    vector<vector<string>> solveNQueens(int n) {
        N = n;
        traverse(0, vector<pair<int, int>>());
        return configurations;
    }
    
    // can have occupied diagonals i + j or i - j
    // can have occupied rows and columns
    void traverse(int currentRow, vector<pair<int, int>> placedPositions) {

        // if all queens are placed (if we have gone past the last row), then push solution
        if (currentRow == N) {
            // create blank board
            string s(N, '.');
            vector<string> config;
            for (int i = 0; i < N; i++) 
                config.push_back(s); // strings are cloned so they can be edited separately
            
            // add queens
            for (pair<int, int> pos : placedPositions) {
                config[pos.first][pos.second] = 'Q';
            }

            configurations.push_back(config);
            return;
        }

        // consider placing a queen in every column of this row:
        for (int i = 0; i < N; i++) {
            pair<int, int> currentPos(currentRow, i);

            bool canPlaceQueen = true;

            // make sure we can place a queen there
            for (pair<int, int> pos : placedPositions) {
                // no need to check row because we already guarantee that we do not place in the same row
                // i
                // if (pos.first == currentPos.first) {
                //     return;
                // }
                // j
                if (pos.second == currentPos.second) {
                    canPlaceQueen = false;
                }
                // i+j (diagonal)
                if (pos.first + pos.second == currentPos.first + currentPos.second) {
                    canPlaceQueen = false;
                }
                // i-j (diagonal)
                if (pos.first - pos.second == currentPos.first - currentPos.second) {
                    canPlaceQueen = false;
                }
            }

            if (canPlaceQueen) {
                vector<pair<int, int>> placedPositionsCopy(placedPositions);
                placedPositionsCopy.push_back(currentPos);
                traverse(currentRow + 1, placedPositionsCopy);
            }
        }

        return;
    }
};
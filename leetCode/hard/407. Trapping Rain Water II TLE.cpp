class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {

        // idea: for every height from 1 to .., 
            // start water level at heightmap height instead
        // bfs at every cell to see if that water is contained
            // not contained if the bfs tries to go past the edge
        // if bfs fails, we can skip for future iterations 
            // or maybe handle one cell at a time, try every height at that cell
        int totalTrappedWater = 0;
        for (int i = 1; i < heightMap.size()-1; i++) {
            for (int j = 1; j < heightMap[0].size()-1; j++) {
                
                // for every tile, try water heights and use bfs to see if
                // that water height can be contained
                int waterLevel;
                for (waterLevel = heightMap[i][j]+1; ; waterLevel++) {
                    // new visited array each time
                    vector<vector<bool>> visited(
                        heightMap.size(), 
                        vector<bool>(heightMap[0].size(), false)
                    );
                    if (!bfs(i, j, waterLevel, heightMap, visited)) {
                        break;
                    }
                }
                // -1 because we broke out of the loop when the bfs failed
                // so best case is iteration right before exit loop
                totalTrappedWater += waterLevel - heightMap[i][j] - 1;
            }
        }

        return totalTrappedWater;
        
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool bfs(int i, int j, int waterLevel, vector<vector<int>>& h, vector<vector<bool>>& visited) {

        // add this tile to visited
        visited[i][j] = true;
        // look in all 4 directions
        // if we are surrounded with higher heights return true, if not return false
        for (int k = 0; k < 4; k++) {
            int newI = i + dx[k];
            int newJ = j + dy[k];

            // check if tile is out of bounds: return false
            if (newI < 0 || newJ < 0 || newI >= h.size() || newJ >= h[0].size()) return false;

            // check if tile is already visited: return true;
            if (visited[newI][newJ]) continue;

            // check if tile height is high enough
            if (h[newI][newJ] >= waterLevel) {
                continue;
            }
            else {
                // tile was not high enough, so continue the bfs from this tile
                bool success = bfs(newI, newJ, waterLevel, h, visited);
                if (!success) return false;
            }
        }
        // if we didnt return false, then all directions were taller so the water can be contained
        return true;
    }
};
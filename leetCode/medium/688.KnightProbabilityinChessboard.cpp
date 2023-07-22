class Solution {
public:
    unordered_map<string, double> cache;
    double knightProbability(int n, int k, int row, int column) {
        // string building is slow but i dont feel like making a 3d array lol
        if (cache.find("" + to_string(k) + " " + to_string(row) + " " + to_string(column)) != cache.end()) {
            return cache["" + to_string(k) + " " + to_string(row) + " " + to_string(column)];
        }
        if (k == 0) {
            return 1.;
        }
        
        double ans = 0;
        int dx[8] = {2, 2, 1, -1, -2, -2, -1, 1}; 
        int dy[8] = {1, -1, -2, -2, -1, 1, 2, 2}; 
        for (int i = 0; i < 8; i++) {
            int x = row + dx[i]; 
            int y = column + dy[i]; 

            if (x < 0 || y < 0 || x >= n || y >= n) {
                ans += 0;
                continue;
            }
            ans += knightProbability(n, k-1, x, y);
        }
        ans = ans/8;

        cache["" + to_string(k) + " " + to_string(row) + " " + to_string(column)] = ans;

        return ans;
    }
};
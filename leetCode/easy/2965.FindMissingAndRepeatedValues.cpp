class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        // a appears twice
        // b appears no time

        int n = grid.size();
        int a;

        vector<int> v(n*n+1, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                v[grid[i][j]]++;
            }
        }

        vector<int> ret(2);
        int both = 2;
        for (int i = 1; i <= n*n; i++) {
            if (v[i] == 2) {
                ret[0] = i;
                both--;
                if (both == 0) break;
            }
            if (v[i] == 0) {
                ret[1] = i;
                both--;
                if (both == 0) break;
            }
        }

        return ret;
        
    }
};
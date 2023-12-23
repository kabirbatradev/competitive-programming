class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        // a appears twice
        // b appears no time

        int n = grid.size();
        int a;

        unordered_set<int> nums;

        int num = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                nums.insert(num);
                num++;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (nums.count(grid[i][j]) == 0) {
                    a = grid[i][j];
                }
                else {
                    nums.erase(nums.find(grid[i][j]));
                }
            }
        }

        return {a, *nums.begin()};
        
    }
};
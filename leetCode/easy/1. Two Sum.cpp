class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        // num to index
        map<int, int> m;

        for (int i = 0; i < nums.size(); i++) {

            int goal = target - nums[i];
            if (m.count(goal)) {
                return {i, m[goal]};
            }

            m[nums[i]] = i; // add to map after so we don't use same number twice
        }

        return {}; // should never get here
        
    }
};
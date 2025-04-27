class Solution {
public:
    int countSubarrays(vector<int>& nums) {

        int counter = 0;
        for (int i = 0; i < nums.size()-2; i++) {
            counter += (nums[i] + nums[i+2]) * 2 == nums[i+1];
        }

        return counter;
    }
};
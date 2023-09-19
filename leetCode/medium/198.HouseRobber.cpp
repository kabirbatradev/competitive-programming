class Solution {
public:

    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];

        int prevTwo[2];
        prevTwo[0] = nums[0];
        prevTwo[1] = max(nums[1], prevTwo[0]);

        for (int i = 2; i < nums.size(); i++) {
            int next = max(nums[i] + prevTwo[0], prevTwo[1]);
            prevTwo[0] = prevTwo[1];
            prevTwo[1] = next;
        }

        return prevTwo[1];
    }
};
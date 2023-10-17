class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) {
            return nums[0];
        }
        if (n == 2) {
            return max(nums[0], nums[1]);
        }


        int considerFirst[n];
        int withoutFirst[n];

        // first and second
        int i = 0;
        considerFirst[i] = nums[0];
        withoutFirst[i] = 0;
        i = 1;
        considerFirst[i] = max(nums[0], nums[1]);
        withoutFirst[i] = nums[1];

        for (i = 2; i < n-1; i++) {
            int val = nums[i];
            considerFirst[i] = max(considerFirst[i-1], considerFirst[i-2] + val);
            withoutFirst[i] = max(withoutFirst[i-1], withoutFirst[i-2] + val);
        }

        // last
        i = n-1;
        // cannot use last if consider first
        considerFirst[i] = considerFirst[i-1];
        withoutFirst[i] = max(withoutFirst[i-1], withoutFirst[i-2] + nums[i]);

        return max(considerFirst[i], withoutFirst[i]);
    }
};
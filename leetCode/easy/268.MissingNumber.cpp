class Solution {
public:
    int missingNumber(vector<int>& nums) {

        // solve using cyclic sort

        for (int i = 0; i < nums.size(); i++) {

            while (true) {
                int num = nums[i];
                if (num == nums.size()) {
                    break;
                }

                swap(nums[num], nums[i]);
                if (i == nums[i]) break;
            }

        }

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i) return i;
        }

        

        return nums.size();
        
    }
};
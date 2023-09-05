// this solution uses O(1) extra space

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {

        // solve using cyclic sort

        // add a number to the end to make space for if all numbers from 1 to n are there
        nums.push_back(-1);

        for (int i = 0; i < nums.size(); i++) {
            
            // keep swapping the number at i with the number at index=num
                // this puts num at index=num
            // and stop when we hit a number larger than the array or negative
            // or stop when we finish swapping numbers and the number at i = i itself
            // or stop if index=num already has num at that index
            while (true) {
                int num = nums[i];
                if (num >= nums.size() || num < 0) {
                    break;
                }

                if (nums[num] == num) {
                    break;
                }

                swap(nums[num], nums[i]);
                if (i == nums[i]) break; // if the number for this position is found, then stop
            }

        }

        // all indexes should have their own number at that index
        // skip 0 because it is not positive
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != i) return i;
        }

        return nums.size();
        
    }
};
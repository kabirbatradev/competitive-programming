class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        
        int currentNumber = nums[0];
        int repeatAmount = 1;
        int nextIndexToFill = 1;
        for (int i = 1; i < nums.size(); i++) {
            
            if (nums[i] == currentNumber) {
                repeatAmount++;
                if (repeatAmount == 3) {
                    // do not increment nextIndexToFill
                    // and do not write
                    repeatAmount--;
                }
                else {
                    nums[nextIndexToFill] = nums[i];
                    nextIndexToFill++;
                }
            }
            else {
                currentNumber = nums[i];
                repeatAmount = 1;
                nums[nextIndexToFill] = nums[i];
                nextIndexToFill++;
            }
        }

        return nextIndexToFill;
        
    }
};
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() < 3) return 0;

        int comboLength = 1; // if combo length is 3, then we have an arithmetic sequence
        // if combo length is more than 3, then we have multiple sequences
        // 4: 1 + 2 = 3 sequences
        // 5: 1 + 2 + 3 = 6 sequences
        // every time the combo grows larger after 3, add combo size - 2
            // basically always add combolength -2 if combo length is 3 or more
        
        // wait actually combo = 2
        // then for 2, add 1

        int total = 0;

        int prevDistance = nums[1] - nums[0];
        for (int i = 1; i < nums.size()-1; i++) {
            int first = nums[i];
            int second = nums[i+1];
            int distance = second - first;

            if (distance == prevDistance) {
                comboLength++;
                if (comboLength >= 2)
                    total += comboLength - 1;
            }
            else {
                comboLength = 1; // reset to 1
            }

            prevDistance = distance;
        }

        return total;
    }
};
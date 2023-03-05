class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        
        int left = 0;
        int right = numbers.size()-1;

        // idea: 2 pointers (left and right)
        // if sum is bigger than target, then decrement right pointer
        while (left < right) {
            int sum = numbers.at(left) + numbers.at(right);
            if (sum > target) {
                right--;
            }
            else if (sum < target) {
                left++;
            }
            else {
                return {left+1, right+1};
            }
        }

        return vector<int>();
    }
};
class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {

        int evenSum = 0;
        for (int i : nums) {
            if (i % 2 == 0) {
                evenSum += i;
            }
        }
        vector<int> ret; 
        for (vector<int> q : queries) {
            int index = q[1];
            int val = q[0];
            if (nums[index] % 2 == 0) {
                evenSum -= nums[index];
            }
            nums[index] += val;
            if (nums[index] % 2 == 0) {
                evenSum += nums[index];
            }
            ret.push_back(evenSum);
        }
        return ret;
    }
};
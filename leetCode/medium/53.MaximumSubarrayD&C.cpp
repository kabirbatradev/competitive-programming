class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return divideAndConquer(nums, 0, nums.size())[0];
    }

    vector<int> divideAndConquer(vector<int>& nums, int start, int end) {

        // cout << start << " " << end << endl;

        // base case
        // if (nums.empty()) {
        if (start >= end) {
            return {0, 0, 0, 0};
        }
        // if (nums.size() == 1) {
        if (end - start == 1) {
            // return {max(0, nums[start]), max(0, nums[start]), max(0, nums[start]), nums[start]};
            return {nums[start], nums[start], nums[start], nums[start]};
        }

        // otherwise divide the array into left and right half
        // run divide and conquer
        // use results to build max, max anchored, and total
        int len = end - start;
        vector<int> left = divideAndConquer(nums, start, start + len/2);
        vector<int> right = divideAndConquer(nums, start + len / 2, end);

        // new max = max of left or max of right
            // or left's right anchored + right's left anchor
        // aka the max is either in the left, the right, or crosses over the middle
        int maxSum = max(left[0], right[0]);
        maxSum = max(maxSum, left[2]+right[1]);

        // anchored left of left vs left total + anchored left of right
        int maxAnchoredLeft = max(left[1], left[3] + right[1]);

        // anchored right of right vs right total + anchored right of left
        int maxAnchoredRight = max(right[2], right[3] + left[2]);

        // sum of totals
        int total = left[3] + right[3]; 

        vector<int> ret = {maxSum, maxAnchoredLeft, maxAnchoredRight, total};
        return ret;
        // return:
            // max sub array
            // max anchored left
            // max anchored right
            // total sum

    }
};
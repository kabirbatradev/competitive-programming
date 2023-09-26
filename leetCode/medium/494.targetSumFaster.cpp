class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum < target) return 0;
        if (target < -sum) return 0;

        // index, target
            // index 0 means we used first number
            // index 1 means we used the first and second number
            // at the cell, using index numbers, we reached target 'x' amount of times (x is returned)
        int dp[nums.size()][sum*2+1];

        // initialze everything to 0
        for (int index = 0; index < nums.size(); index++) {
            for (int j = 0; j < sum*2+1; j++) {
                dp[index][j] = 0;
            }
        }
        
        // for the first index, target = 1 at -val or +val
        // rest should be 0
        
        dp[0][sum+nums[0]] += 1;
        dp[0][sum-nums[0]] += 1;
        
        
        // for every new number, update the targets we can reach
        for (int i = 1; i < nums.size(); i++) {

            int currentNumber = nums[i];

            // check all the previous number's targets and go up or down from that
            for (int j = 0; j < sum*2+1; j++) {

                if (dp[i-1][j] == 0) {
                    // this target could not be reached using the previous numbers
                    continue;
                }

                int waysToReachPrevTarget = dp[i-1][j];

                // cout << i << " " << j-sum << " " << currentNumber << " " << waysToReachPrevTarget << endl;

                // j was reached: 
                dp[i][j + currentNumber] += waysToReachPrevTarget;
                dp[i][j - currentNumber] += waysToReachPrevTarget;

            }
        }

        // use all numbers
        // reach target
        int ret = dp[nums.size()-1][sum+target];

        return ret;
    }
};
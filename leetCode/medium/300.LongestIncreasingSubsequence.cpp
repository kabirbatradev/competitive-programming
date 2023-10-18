class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {

        // dp solution:
        // whats the LIS up to i including the ith number
        // dp[0] = 1
        // dp[i] = max(dp[k] + 1) for all k smaller than i where num[k] < num[i]
        
        // n^2 version:
        int dp[nums.size()];
        dp[0] = 1;
        int ans = 1;
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = 1;
            for (int j = i-1; j >= 0; j--) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }


        // for (int i = 0; i < nums.size(); i++) {
        //     cout << dp[i] << " ";
        // }
        return ans;
        
    }
};
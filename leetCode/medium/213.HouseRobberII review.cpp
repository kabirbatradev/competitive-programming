class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1)
            return nums[0];

        int dp[nums.size()];
        // vector<vector<int>> dp(nums.size(), vector<int>(2, 0));

        // base case: rob first house or not
        dp[0] = nums[0];

        // stop before last house
        for (int i = 1; i < nums.size() - 1; i++) {
            // take the previous house and dont take current
            // or take the current, and take the -2 if it exists
            dp[i] = nums[i];
            if (i >= 2) {
                dp[i] += dp[i-2];
            }
            dp[i] = max(dp[i], dp[i - 1]);
        }

        // do not consider last house
        int bestWithRobFirstHouse = dp[nums.size()-2];

        // base case: guaranteed do not rob first house
        dp[0] = 0;

        // include last house
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = nums[i];
            if (i >= 2) {
                dp[i] += dp[i-2];
            }
            dp[i] = max(dp[i], dp[i - 1]);
        }

        int bestWithLastHouse = dp[nums.size()-1];
        return max(bestWithLastHouse, bestWithRobFirstHouse);
    }
};

/*
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1)
            return nums[0];

        int dp[nums.size()][2];
        // vector<vector<int>> dp(nums.size(), vector<int>(2, 0));

        // base case: rob first house or not
        dp[0][false] = 0;
        dp[0][true] = nums[0];

        // stop before last house
        for (int i = 1; i < nums.size() - 1; i++) {
            dp[i][true] = dp[i - 1][false] + nums[i];
            if (i >= 2) {
                dp[i][true] = max(dp[i][true], dp[i - 2][true] + nums[i]);
            }
            dp[i][false] = max(dp[i - 1][true], dp[i - 1][false]);
        }

        // do not consider last house; consider robbing or not robbing second
        // last house
        int bestWithRobFirstHouse =
            max(dp[nums.size() - 2][true], dp[nums.size() - 2][false]);

        // vector<vector<int>> dp2(nums.size(), vector<int>(2, 0));
        // int dp[nums.size()][2];

        // base case: guarantee not robbing first house
        dp[0][false] = 0;
        dp[0][true] = 0;

        // include last house
        for (int i = 1; i < nums.size(); i++) {
            dp[i][true] = dp[i - 1][false] + nums[i];
            if (i >= 2) {
                dp[i][true] = max(dp[i][true], dp[i - 2][true] + nums[i]);
            }
            dp[i][false] = max(dp[i - 1][true], dp[i - 1][false]);
        }

        int bestWithLastHouse =
            max(dp[nums.size() - 1][true], dp[nums.size() - 1][false]);
        return max(bestWithLastHouse, bestWithRobFirstHouse);
    }
};
*/

/*
dp table
to make decisions, we need as input:
    index of a house that we are currently passing by (index)
    did we rob this house or not (true or false)
output: the max money we can make given these conditions
want to rob this house: dp[i][true] = dp[i-2][true] or dp[i-1][false]
dont want to rob this house: dp[i][false] = dp[i-1][true] or dp[i-1][false]

make sure not to consider last house, stop at dp[second last][true or false]

the last house can only be robbed if the first one was not robbed:
    can make a second dp table where first house is robbed is guaranteed
    dp2[0][true or false] = 0 no matter what
    then we can consider dp[last house][true or false]
*/


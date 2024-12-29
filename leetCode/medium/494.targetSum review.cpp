class Solution {
public:
    // vector<unordered_map<int, int>> dp; // index, current sum --> # ways
    int findTargetSumWays(vector<int>& nums, int target) {

        // modified bottom up approach using vector instead of map
        // also got rid of set 
            // (which existed to skip situations where a sum does not exist)
            // much faster now
        // memory is still not great

        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        // required checks for if target is out of range of our dp table
        if (totalSum < target) return 0;
        if (target < -totalSum) return 0;

        // int dp[totalSum*2+1] = {0};
        vector<int> dp(totalSum*2+1, 0); // current sum --> # ways; of previous index
            // size is 1000 for positives, 1000 for negatives, and 1 for 0 
            // 0 - 999 are negatives, index 1000 is 0 
        // set<int> dpExists;
        dp[totalSum] = 1; // to reach sum of 0, there is 1 way (init before using any nums)
        // dpExists.insert(sum);
        for (int i = 0; i < nums.size(); i++) {
            // int newdp[totalSum*2+1] = {0};
            vector<int> newdp(1000*2+1, 0);
            // set<int> newdpExists;

            // for every previous dp, using new index, increment new counts
            // for (int sum : dpExists) {
            for (int sum = 0; sum < totalSum*2+1; sum++) {
                int count = dp[sum];
                if (count == 0) continue;
                newdp[sum + nums[i]] += count;
                newdp[sum - nums[i]] += count;
                // newdpExists.insert(sum + nums[i]);
                // newdpExists.insert(sum - nums[i]);
            }

            dp = newdp;
            // dpExists = newdpExists;
        }
        return dp[target+totalSum]; // offset of totalSum
        


        // // actually slows down code
        // int sum = accumulate(nums.begin(), nums.end(), 0);
        // if (sum < target) return 0;
        // if (target < -sum) return 0;

        // // bottom up approach:
        // unordered_map<int, int> dp; // current sum --> # ways; of previous index
        // dp[0] = 1; // to reach sum of 0, there is 1 way (init before using any nums)
        // for (int i = 0; i < nums.size(); i++) {
        //     unordered_map<int, int> newdp; 

        //     // for every previous dp, using new index, increment new counts
        //     for (auto [sum, count] : dp) {
        //         // default value is 0 so can increment without checking existence
        //         newdp[sum + nums[i]] += count;
        //         newdp[sum - nums[i]] += count;
        //     }

        //     dp = newdp;
        // }
        // return dp[target];



        // // init dp for indices up to nums.size()
        // dp = vector<unordered_map<int, int>>(nums.size());
        // return recursion(0, 0, nums, target);
    }

    // int recursion(int index, int currentSum, vector<int>& nums, int target) {
    //     if (index == nums.size()) {
    //         return currentSum == target ? 1 : 0;
    //     }
    //     if (dp[index].count(currentSum)) {
    //         return dp[index][currentSum];
    //     }
    //     int ret = (
    //         recursion(index+1, currentSum + nums[index], nums, target) + 
    //         recursion(index+1, currentSum - nums[index], nums, target)
    //     );
    //     dp[index][currentSum] = ret;
    //     return ret;
    // }
};
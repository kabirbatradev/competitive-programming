class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        // input to table is left and right pointer describing a range we need to find the optimal solution for
        int dp[nums.size()][nums.size()];

        // i think the edges need to be set to 1 so whenever we ask for dp of the edge, it just returns 1
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                dp[i][j] = 1;
            }
        }

        // given some l r, go through and delete every balloon and use recursion to compute the neighboring subproblems?
        // bottom up:
            // for every range equal to 0, (left and right are equal), we just pop the balloon using the neighbor's scores
        // for every range equal to 1, (left is one less than right), best score = 
            // pop left after right: get solution of right, and then add left-1 * left * right+1
        // for every range equal to 2: (left to right has 3 numbers inclusive):
            // either do the edge (then similar case to prev)
            // or pop the middle one last: get solution of left, get solution of right, add l-1 * middle * r+1
        // last range should be of size n -1

        int n = nums.size()-2;
        for (int rangeSize=0; rangeSize < n; rangeSize++) {
            for (int startNum = 0+1; startNum + rangeSize < n+1; startNum++) {
                int endNum = startNum+rangeSize;

                // should compute this in advance?
                if (rangeSize == 0) {
                    dp[startNum][startNum] = nums[startNum-1] * nums[startNum] * nums[startNum+1];
                    continue;
                }

                // try every k such that the kth balloon is popped last and 
                // the left and right sides are popped independently and optimally
                int best = 0;
                for (int k = startNum; k <= endNum; k++) {
                    if (k != startNum && k != endNum) {
                        int score = dp[startNum][k-1] + dp[k+1][endNum] + nums[startNum-1] * nums[k] * nums[endNum+1];
                        best = max(best, score);
                    }
                    else if (k == startNum) {
                        int score = dp[k+1][endNum] + nums[startNum-1] * nums[k] * nums[endNum+1];
                        best = max(best, score);
                    }
                    else { // k == endNum
                        int score = dp[startNum][k-1] + nums[startNum-1] * nums[k] * nums[endNum+1];
                        best = max(best, score);
                    }
                }

                dp[startNum][endNum] = best;

            }
        }

        // get best num from 1 to index n - 2? n-3? n-2 bc we want to skip the 1 at the end
        return dp[1][nums.size()-1 - 1];
            // skip the 1 at the start
            // skip the 1 at the end
        
    }
};
class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {

        // concise solution explained by roommate harsh:
        // induction:
        // base case 0 at the start: solution 0
        // given solution for subarray 0 to k-1, solve for solution to subarray 0 to k
        // compare kth number to k-1 number:
            // if kth gets closer to 0, then add no work
            // if kth gets farther from 0 (same sign), then add work = kth - (k-1)th
            // if kth switches signs, then treat as if we start from 0; add work = kth

        int prev = 0;
        long long work = 0;
        for (int i = 0; i < nums.size(); i++) {
            int difference = nums[i] - target[i];
            // cout << "difference " << difference << endl;

            // if different sign
            if (prev > 0 != difference > 0) {
                work += abs(difference);
                // cout << abs(difference) << endl;
            }

            // if getting closer to 0
            else if (abs(prev) > abs(difference)) {
                // work += 0;
                // cout << 0 << endl;
            }

            // if we are getting farther from 0
            else {
                work += abs(difference) - abs(prev);
                // cout << abs(difference) - abs(prev) << endl;
            }

            prev = difference;
        }

        return work;
        
    }
};
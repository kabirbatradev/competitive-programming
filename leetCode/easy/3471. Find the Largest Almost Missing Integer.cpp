class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        
        // if k = 1, then every integer is its own window
            // if an integer appears once, then it should be considered
        // if k > 1, then only the first and last nums might appear once
            // if one of those already exists in the array somewhere else, then it is in multiple windows
            // unless k = size of subarray...

        if (k > 1 and k != nums.size()) {
            
            if (nums.front() == nums.back()) return -1;
            // count:
            map<int, int> m;
            for (int i = 0; i < nums.size(); i++) {
                m[nums[i]]++;
            }
            int front = nums.front();
            int back = nums.back();
            if (m[front] == 1 && m[back] == 1) {
                return nums.front() > nums.back() ? nums.front() : nums.back();
            }
            else if (m[front] == 1) {
                return front;
            }
            else if (m[back] == 1) {
                return back;
            }
            else {
                return -1;
            }
        }

        // if k == size, then find max num
        if (k == nums.size()) {
            int runningMax = -1;
            for (int num : nums) {
                runningMax = max(runningMax, num);
            }
            return runningMax;
        }


        // find the max num that doesnt appear multiple times
        map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            m[nums[i]]++;
        }
        int runningMax = -1;
        for (auto [num, count] : m) {
            if (count == 1) {
                runningMax = max(runningMax, num);
            }
        }

        return runningMax;
    }
};
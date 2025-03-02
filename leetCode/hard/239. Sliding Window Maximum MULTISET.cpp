class Solution {
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    
            // sliding windows from [i, i+k-1]
                // the last sliding window starts at i = n - k
                // number of sliding windows = n - k + 1
            // use ordered multiset to maintain sliding window elements 
            // logn insertion, deletion, and checking for max
    
            // initialize the first sliding window using the first k elements:
            multiset<int> s;
            vector<int> ret; ret.reserve(nums.size() - k + 1);
            for (int i = 0; i < k; i++) {
                s.insert(nums[i]);
            }
            ret.push_back(*s.rbegin());
            
            // iterate through all sliding windows: [i, i+k-1]
            for (int i = 1; i < nums.size() - k + 1; i++) {
                // remove element at i-1
                // s.erase(nums[i-1]);
                s.erase(s.find(nums[i-1])); // only erase one instance if there are duplicates
                // add element at i+k-1
                s.insert(nums[i+k-1]);
                ret.push_back(*s.rbegin());
            }
    
            return ret;
            
        }
    };
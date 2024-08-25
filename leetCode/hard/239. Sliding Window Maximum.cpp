class Solution {
public:
    struct pair {
        int val;
        int index;
    };
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        // idea: manage window maxes using deque
        // front will have max, remove from front when window is out of range
        // back will have latest element added to window, remove from back if it is smaller than latest element
        // note
            // add the latest element before asking for max
            // remove from front before asking for max
        // note: 
            // deque stores ints, but also we need to remember the index, so store a pair
        
        deque<pair> dq;

        // prepare first window
        int i;
        for (i = 0; i < k; i++) {
            while (!dq.empty()) {
                if (dq.back().val < nums[i]) dq.pop_back();
                else break;
            }
            dq.push_back(pair(nums[i], i));
        }
        
        vector<int> maxes;
        maxes.push_back(dq.front().val); // add the max of the first window

        // for all future possible windows
        for (; i < nums.size(); i++) {
            // remove stuff from the back 
            while (!dq.empty()) {
                if (dq.back().val < nums[i]) dq.pop_back();
                else break;
            }
            dq.push_back(pair(nums[i], i));
            // remove stuff from the start if its out of range of the new window (if the index = i -k)
            if (dq.front().index == i-k) dq.pop_front();
            // add the new max
            maxes.push_back(dq.front().val);
        }

        return maxes;
        // return maximum;
        
    }
};
class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int min = 0;
        int max = nums.size()-1;

        int mid;

        while (min <= max) {
            // while the range has at least 1 number in it

            mid = (min + max)/2;
            if (nums.at(mid) == target) return mid;

            // start is greater than mid, so mid ascends to the right
            if (nums.at(0) > nums.at(mid)) {
                if (nums.at(mid) < target && target <= nums.at(max)) {
                    // between mid and max
                    min = mid + 1;
                }
                else {
                    // not between mid and max, so must be on right side (less than mid or greater than max)
                    max = mid - 1;
                }
            }
            else {
                // start is less than mid
                
                if (nums.at(0) <= target && target < nums.at(mid)) {
                    // if between beginning and mid
                    max = mid - 1;
                }
                else {
                    // also less than the min (left most), so it is actually on the right side
                    min = mid + 1;
                }
            }
        }

        // if we got here, we never found the number
        return -1;
    }
};
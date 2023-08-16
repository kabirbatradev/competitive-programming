class Solution {
public:
    int findPeakElement(vector<int>& nums) {

        // binary search for a peak
        // look at left and right of selected number
        // if peak, then return
        // if right greater (or both right and left greater), then at least 1 peak guaranteed right
        // else, at least 1 peak guaranteed left

        int min = 0;
        int max = nums.size()-1;

        while (min <= max) {
            int mid = (min + max) / 2;

            // is it a peak?
            int midVal = nums.at(mid);
            // bool leftIsLess = (mid - 1 >= 0) ? nums.at(mid-1) < midVal : true;
            bool leftIsLess = (mid - 1 < 0) || nums.at(mid-1) < midVal;
            // bool rightIsLess = (mid + 1 <= nums.size()-1) ? nums.at(mid+1) < midVal : true;
            bool rightIsLess = (mid + 1 >= nums.size()) || nums.at(mid+1) < midVal;

            // guaranteed no 2 nums in a row are the same
            if (leftIsLess && rightIsLess) {
                return mid; // mid is a peak
            }

            // if not a peak, adjust binary search min or max

            if (!rightIsLess) {
                min = mid + 1;
            }
            else {
                max = mid - 1;
            }
        }

        // should never get here

        return -1;
        
    }
};
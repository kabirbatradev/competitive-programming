class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {


        // binary search for the correct partition position
        bool nums1Smaller = nums1.size() < nums2.size();
        vector<int>& smaller = nums1Smaller ? nums1 : nums2;
        vector<int>& bigger = nums1Smaller ? nums2 : nums1;

        int totalSize = nums1.size() + nums2.size();

        // edge case: length of array is 0 
        if (smaller.size() == 0) {
            if (totalSize % 2 == 0) {
                return (bigger[totalSize/2 - 1] + bigger[totalSize/2]) / 2.0;
            }
            else {
                return bigger[totalSize/2];
            }
        }
        if (bigger.size() == 0) {
            if (totalSize % 2 == 0) {
                return (smaller[totalSize/2 - 1] + smaller[totalSize/2]) / 2.0;
            }
            else {
                return smaller[totalSize/2];
            }
        }

        int start = 0; // 0 -> before first element
        int end = smaller.size() ; // size -> after last element
        while (start <= end) {
            // cout << start << " " << end << endl;
            int partitionPosition = (start + end) / 2; 
            int biggerPartitionPosition = totalSize/2 - partitionPosition;

            // check for partition position edge cases
            // if theres nothing before partition position
                // bigger[before] <= smaller[after] --> median
            // if (partitionPosition == 0) {
            //     if (!(biggerBefore <= smallerAfter)) {
            //         // only option is to move partition right
            //         // ? 
            //         // we could have only got here if this is the solution
            //     }
            // }
            // if theres nothing after partition position
                // smallerBefore <= biggerAfter

            if (partitionPosition == 0) {

                // we could be here and not be median because of truncation of midpoint
                // we are at the median only if biggerBefore <= smallerAfter
                int smallerAfter = smaller[partitionPosition];
                int biggerBefore = bigger[biggerPartitionPosition-1];
                // cout << smallerAfter << " " << biggerBefore << endl;
                if (!(biggerBefore < smallerAfter)) {
                    // cout << "bad" << endl;
                    start = partitionPosition+1;
                    continue;
                }

                // entire smaller array is in right partition
                // median is in bigger array starting from beginning 
                // (unless median is between arrays)
                // what if odd number of nodes so left side is smaller than right side
                    // then median could still be on right side (smallest element of right side)
                    // actually then median is the first element on right side
                if (totalSize % 2 == 0) {
                    // if median is between arrays:
                    if (totalSize/2 == bigger.size()) {
                        return (bigger[bigger.size()-1] + smaller[0]) / 2.0;
                    }
                    // right median could be leftmost element of smaller 
                    int left = bigger[totalSize/2 - 1];
                    int right = min(smaller[0], bigger[totalSize/2]);
                    return (left + right) / 2.0;
                }
                else {
                    // first element of right side = smaller[0] or bigger[totalSize/2], whichever is less
                    return min(smaller[0], bigger[totalSize/2]);
                }
            }
            if (partitionPosition == smaller.size()) {
                // cout << "(partitionPosition == smaller.size()) {" << endl;
                // entire smaller array is in left partition
                // median is in bigger array, but index is offset by size of smaller array
                // (unless median is between arrays)
                if (totalSize % 2 == 0) {
                    // cout << "if (totalSize % 2 == 0) {" << endl;
                    // if median is between arrays:
                    // really what we care about is if the median is on the partition line
                    // cout << totalSize/2 << " " << smaller.size() << endl;
                    // cout << totalSize/2 - 1 - smaller.size() << endl;
                    // cast because size_t is unsigned so it underflows 
                    // make sure we dont access bigger at index -1
                    if (totalSize/2 - 1 - (long)smaller.size() < 0) {
                        // cout << "if (totalSize/2 - 1 - smaller.size() < 0) {" << endl;
                        return (smaller[smaller.size()-1] + bigger[0]) / 2.0;
                    }
                        // we always need to consider the rightmost smaller number to be the "left" number in the median 
                    int left = max(
                        bigger[totalSize/2 - 1 - smaller.size()],
                        smaller[smaller.size()-1]
                    );
                    int right = bigger[totalSize/2 - smaller.size()];
                    return (left + right) / 2.0;
                }
                else {
                    return bigger[totalSize/2 - smaller.size()];
                }
            }

            int smallerBefore = smaller[partitionPosition-1];
            int smallerAfter = smaller[partitionPosition];

            int biggerBefore = bigger[biggerPartitionPosition-1];
            int biggerAfter = bigger[biggerPartitionPosition];

            // partition too far left: 
            // smaller after is less than bigger before
            if (smallerAfter < biggerBefore) {
                start = partitionPosition+1;
                continue;
            }
            // partition too far right:
            // bigger after is less than smaller before
            if (biggerAfter < smallerBefore) {
                end = partitionPosition - 1;
                continue;
            }
            // partition is at median
            // if even, then take the average of the middle 2
            if (totalSize % 2 == 0) {
                vector<int> nums = {
                    smallerBefore, smallerAfter, biggerBefore, biggerAfter
                }; 
                sort(nums.begin(), nums.end());
                return (nums[1] + nums[2]) / 2.0;
            }
            // if odd, then left side is smaller, so return smaller of "after" values
            else {
                return min(smallerAfter, biggerAfter);
            }
        }

        cout << "the while loop broke without returning" << endl;
        return 0; // i dont think we should have gotten here? unless the while loop broke without returning
        
    }
};
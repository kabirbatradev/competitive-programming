class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int n = nums.size();

        set<int> distinct; 
        for (int num : nums) {
            distinct.insert(num);
        }

        map<int, int> counter; // surprisingly, ordered sets and maps are faster
        int total = 0;

        int right = 0; // not inclusive
        for (int left = 0; left < n; ) {

            // if the counter doesnt have k different integers, then
            // we need to push right
            if (counter.size() < k) {
                if (right == n) break; // cooked (cant make any more valid arrays)
                counter[nums[right++]]++;
                continue;
            }

            // otherwise, we have exactly k distinct integers
            total++;
            // we can push right to see how far we can extend right
                // without adding anything new
            int oldRight = right;
            while (right < n) {
                // alr has num at right, so its still k
                if (counter.contains(nums[right])) {
                    right++; // note that we dont change counter's counts
                    total++;

                    // note: if we push right past the edge, we should break
                    // move that to the while loop lol
                }
                else {
                    break; // we can add this one without going over k distinct
                }
            }
            // then we should reset right
            // and push left (removing what is at left)
            right = oldRight;
            int removeNum = nums[left++];
            counter[removeNum]--;
            // also remove entry from map entirely if its 0
            if (counter[removeNum] == 0) {
                counter.erase(removeNum); 
            }
            
            
        }

        return total;
        
    }
};

/*
goal: count number of subarrays that have exactly k different integers

approach: create a sliding window that grows until it has k different integers
then it can continue to grow until a new integer is introduced
then it can shrink from the other direction until there are just enough
    unique integers again

i think we missed stuff
left is shifted forward to make it valid again
right is shifted forward to the point where it was invalid
    but now its valid because left was shifted forward

what if we shifted left earlier before shifting right 
we might have had valid stuff there?
before right was shifted so much it was invalid

i guess we could have counted how many we can push right before it becomes invalid
and then push left
but then pushing left might only be valid after pushing right enough

i almost just want to reset right to when it finally made things valid
then push left
then push right until its finally valid again
then reset right and push left
*/
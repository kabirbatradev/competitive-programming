class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {

        int n = nums.size();

        set<int> uniques;
        for (int num : nums) {
            uniques.insert(num);
        }

        int total = 0;
        map<int, int> counter;

        int right = 0; // note that it is not inclusive
        counter[nums[right++]]++; // add first element into counter
        for (int left = 0; left < n; ) {
            
            // this is a valid thing
            if (counter.size() == uniques.size()) {
                total++;

                // imagine pushing right pointer to the end 
                // and getting a bunch of valid states
                // right can be pushed to right=n
                total += n - right;

                // then left pointer is pushed and continue
                // when left pointer is pushed, 
                    // we need to remove that element from counter

                counter[nums[left]]--; // delete num at 'left'
                if (counter[nums[left]] == 0) {
                    counter.erase(nums[left]);
                }
                left++;
                continue;
            }

            // push the right pointer until you have one of everything
            if (right >= n) break; // want to push right but cant
            counter[nums[right]]++;
            right++;

        }

        return total;
        
    }
};


/*
i need a contiguous array
that has all of the distinct elements
# of distinct elements in the array = number of distinct elements in the whole array
this means that there needs to be at least one of every distinct element in the subarray

sliding window
make the window big:
    until it has one of each
    increase count by:
        one window for current right pointer
        more windows for pushing right pointer to the right

now move left pointer forward once
repeat process above
but the right pointer should start where it left off

stop when the left pointer passes the end of the array

*/
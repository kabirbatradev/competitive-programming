class Solution {
public:
using ll = long long;
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();

        ll count = 0;
        ll sum = 0; 

        // sliding window:
        int left = 0; // inclusive
        int right = 0; // not inclusive...
        // neither pointer are inclusive, but rather represent the next number to add or delete

        // size of window = right - left;
        while (left < n) {
            // push right repeatedly:
            while (true) {

                // out of bounds
                if (right == n) break;

                // overflow if multiply right num to product
                if (LLONG_MAX - nums[right] < sum) {
                    break;
                }

                // overflow if multiply size as well
                int size = right+1 - left; //+1 because right is not pushed yet
                // skip this check if size = 0
                if (size != 0 && LLONG_MAX / size < (sum + nums[right])) {
                    break;
                }

                // now check against the 'k' bound
                if (size != 0 && (size * (sum + nums[right])) >= k) {
                    break;
                }

                // increase product with new 'right' num
                sum += nums[right];
                right++;
            }

            // we are no longer able to push right pointer
            // left --> right is the largest subarray we can make starting at left
            int size = right - left; // = # of subarrays that start at left
            count += size;
            
            // printf("max len subarray from left=%d to right=%d\n", left, right);
            // printf("sum = %lld\n", sum);
            // printf("sum*size = %lld\n", sum*size);
            // printf("full array:\n");
            // for (int i = left; i < right; i++) {
            //     cout << nums[i] << " ";
            // }
            // cout << endl << endl;

            // now delete left element and push left pointer
            sum -= nums[left];
            left++;
        }

        return count;
        
    }
};

/*
score = sum * length
want: # non empty subarrays where score < k

note: all integers are positive
    therefore, by increasing the length of the subarray,
    we increase the score guaranteed
    "monotonic increasing"

one idea:
    for every start number, binary search for the max end number
    result: max length of array starting at that num
    if max is 5, then we can make 5 arrays that start at that num

    theoretical runtime: O(nlogn)

question: 
    can we get the max array length in O(1) instead of log(n)?
    idk but i dont think so
    if we could, runtime would be O(n)

question: 
    how do we get the product of the subarray starting at some num
    prefix sum, but its actually prefix product?
    that might overflow though!
    idk what to do about it...
    maybe this is not a valid direction to go in 

read the first hint:
    induction/dp style solution:
    process each num as if it was just added to the array, 
        and we had the solution to the old array
    solution to old array = 
        # of valid subarrays
        list of subarrays that ended at the last num but could grow further
            pair: product so far, size of array so far
    how to process new element:
        consider using it as a new element for each array that might still exist
        if overflow or cross k, then delete this possible array
        increase count for every subarray that survived, 
            and update product to have this new num

    why do we not have overflow issues:
        because we can check for overflow every time we are about
        to do a multiplication, and exit if its going to overflow 
            divide LLONG_MAX by num1 and make sure that is larger than num2
            if smaller, then num1*num is too big

    issue: the runtime is O(n^2) because we could have n alive arrays 
        at the time of processing the new element
    can we represent alive arrays more concisely?
        instead of a product and a size, we could just represent a start index
        we would need a quick way of getting the running product...
        brings us back to a prefix product idea, which has overflow issues

reading second and third hint:
    2 pointers???

wait a second!
    we ignored sliding window because we assumed it doesn't "count" well
    maybe we can count!
    grow a sliding window from index 0
    cant grow anymore, now have 'right' pointer 
        remove element from the back
        the product is guaranteed to be less
        we also know that index 1 through 'right' creates right-left 
            additional valid arrays
        product = prev product / back element

algo sudo code:
    sliding window from 0 to 0
    repeat (until left pointer too big)
        push right pointer until product is too big
            note: if right pointer wants to exceed size, stop pushing right early
        add size of sliding window to counter
            this represents # of arrays we can create starting at left pointer
        push left pointer

wait i read the problem wrong
    i thought it was product of nums, not sum of nums
    ugh

can we still use sliding window?
    adding a new number is guaranteed to increase the sum, and the product num
    maybe just modify the solution
    to have a running sum instead of product
*/
class Solution {
public:
    using ll = long long;

    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size();


        // count = # interesting nums
        ll count = 0; 
       
        // for each interesting num, i want to know buffer sizes
        // vector where every entry is an interesting num
        vector<pair<ll,ll>> bufferSizes;
        // also keep track of all buffer sizes for the k=0 case
        vector<ll> allSizes;

        // attempt to speedup
        bufferSizes.reserve(n); 
        allSizes.reserve(n);

        int bufferSize = 0;
        for (int i = 0; i < n; i++) {
            // set num to either true or false
            // depending on if its interesting
            bool interesting = (nums[i] % modulo == k);
            // cout << "interesting = " << interesting << endl;
            count += interesting;

            if (!interesting) {
                bufferSize++;
            }
            else {
                // if (prevIndex != -1) {
                //     // right side
                //     bufferSizes[prevIndex].second = bufferSize;
                // }
                // // left side
                // bufferSizes[i].first = bufferSize;
                // bufferSize = 0;

                if (bufferSizes.size() != 0) {
                    bufferSizes.back().second = bufferSize;
                }
                bufferSizes.push_back({bufferSize, 0});

                if (bufferSize != 0) // speedup attempt
                    allSizes.push_back(bufferSize);

                bufferSize = 0; // reset
            }
        }
        // set the right buffer size of the last number (if we left off at a not interesting num)
        if (count != 0) // make sure there is at least one interesting num
            bufferSizes.back().second = bufferSize;
        if (bufferSize != 0) // speedup attempt
            allSizes.push_back(bufferSize);

        // cout << "printing all buffer sizes: " << endl;
        // for (auto [a, b] : bufferSizes) {
        //     cout << a << " " << b << endl;
        // }


        // if all buffer sizes are 0, then this is a special case we can optimize
        if (allSizes.size() == 0) {
            ll total = 0;
            while (k <= count) {
                if (k == 0) {
                    // want 0 interesting numbers, but all buffer sizes are 0, 
                    // so there are no interesting numbers
                    // so we don't add anything
                }
                else {
                    total += count - k + 1; // # of arrays we can make of size k 
                }
                k += modulo;
            }
            return total;
        }

        ll total = 0;
        while (k <= count) {
            // cout << "calling with k = " << k << endl;
            if (k == 0) {
                // special edge case:
                // we want 0 interesting numbers
                // each buffer is a gap of not interesting numbers
                // of which you can create n + n-1 + n-2 + ... 2 + 1
                    // = n/2 * (n+1)
                // for each buffer
                for (auto bufferSize : allSizes) {
                    total += bufferSize*(bufferSize+1) / 2;
                }
            }
            else {
                total += slidingWindowHelper(k, bufferSizes);
            }
            k += modulo;
            // cout << "total is " << total << endl;
        }

        return total;

    }

    // make a window with k interesting numbers
    ll slidingWindowHelper(int k, vector<pair<ll,ll>>& bufferSizes) {
        int n = bufferSizes.size();
        ll total = 0;
        // go through every set of exactly k elements
        for (int right = k-1; right < n; right++) {
            // left and right are inclusive 
            // they represent start and end interesting nums
            int left = right - k + 1;

            // printf("left = %d, right = %d\n", left, right);
            // printf("buffer sizes: %d %d\n", bufferSizes[left].first, bufferSizes[right].second);

            // 1 for current array, and more for just one side at a time
            total += 1 + bufferSizes[left].first + bufferSizes[right].second;
            // left's left buffer * right's right buffer
            total += bufferSizes[left].first * bufferSizes[right].second;
        }

        return total;
    }
};

/*
goal: find number of subarrays that are "interesting"

interesting:
    in the subarray
    there are numbers where the remainder after dividing "mod" is k
    so basically they are perfectly k offset from a multiple of "mod"
    
    count = # of nums like this in the subarray
    the remainder of count / mod must also be k

idea:
    we can precompute whether a single number is interesting
    just go through them all, check if num % mod == k, true or false

    then we can sliding window: grow window until count is large enough that it equals k, or mod + k, or 2*mod + k ... etc

after precomputing, can we do faster?
    note: we know exactly how many numbers are interesting
    the numbers in between dont matter...

    the real question is, how many ways can we make 
        in order groups of size k, or mod+k, or 2*mod + k ... 
    for just k:
        if k = 2, and there are 5 nums, then its count - k + 1

i missed something:
    we can have a subarray with dummy numbers at the beginning or end
    and this adds more valid subarrays

what if we sliding window it:
    left pointer at the start
    push right until we have exactly k elements
    now this is one valid subarray
    but we can push right until right before a new interesting num
    those are all also valid
    and we can also push left until right before invalid 
    so for every tight valid subarray, we have 
        extra subarrays = left buffer * right buffer 
    maybe we can precompute a left and right buffer size for each num
        keep a count until we have an interesting num
        make that count the left buffer of that num
        keep a new count until next interesting num
        make prev number's right buffer = that count
    
    then we rerun the entire thing with k+mod as the requested size
    and stop when k+mod > count 

potential speedup:
    if all buffer sizes are 0, then we can just use
    count - k + 1
*/
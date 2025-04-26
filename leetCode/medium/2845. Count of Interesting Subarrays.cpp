class Solution {
public:
    using ll = long long;

    long long countInterestingSubarrays(vector<int>& nums, int mod, int k) {
        int n = nums.size();

        ll total = 0;
        int count = 0;
        unordered_map<int, int> freqMap;
        // simulate prefix sum 'count' starting at 0
        freqMap[0] = 1;
        for (int i = 0; i < n; i++) {
            bool interesting = (nums[i] % mod == k);
            count += interesting;
            
            total += freqMap[(count - k) % mod];
            freqMap[count % mod]++;
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
    a subarray is interesting if: the remainder of count / mod is also k

    basically, the number of interesting nums has to be a multiple of mod + k

prefix sum idea from editorial
    at every index, know how many interesting nums there are from 0 to i (inclusive)

for every right bound of the subarray, we want to find a left bound such that
    the total number of interesting nums is k + modulo*j (for any natural num j)

    the right bound is going to have more interesting nums than the left bound...
    we want to find a left that has a count that is k less, or k+mod less, or k+mod*2 less ...

if we were just looking for k less, we could check hashtable entry, looking for count-k
    one solution is we look into the hashtable for every single variation of
        count - (k + multiple of mod) = count - k - multiple of mod

    editorial says we can just store 'count' at key = count % mod
        this represents some count + some multiple of mod

    then when right bound has prefix sum of count, we look for (count - k) % mod
        this represents some multiple of mod + k less than count
        note that count - k could go negative, but that shouldnt matter because 
            we do not have enough count to even create one array of k interesting nums

finally, the start of the prefix sum should have a 0 to represent 
    before the first element, there is a count of 0
    this basically adds an initial value to the map of 0 --> 1
    which means there exists a left bound with 0 count
*/
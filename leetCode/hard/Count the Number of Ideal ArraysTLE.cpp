class Solution {
public:
    using ll = long long;

    int n;
    int maxVal;

    int MOD = 1e9 + 7;

    int idealArrays(int n, int maxValue) {
        this->n = n;
        this->maxVal = maxValue;

        // init cache
        // max prev = max value
        // cells left goes from 0 to n
        // init value -1 represents not yet solved
        cache.assign(maxValue+1, vector<int>(n+1, -1));
        
        // initial prev value is 1
        // because everything is divisible by 1
        return completeSearch(1, n) % MOD; 
        
    }

    // map<pair<int, int>, int> cache;
    vector<vector<int>> cache;

    // returns # valid combinations
    ll completeSearch(int prev, int cellsLeft) {
        
        // base case: we have achieved a valid way of getting here
        if (cellsLeft == 0) return 1;

        // check cache
        // auto it = cache.find({prev, cellsLeft});
        // if (it != cache.end()) {
        //     return it->second;
        // }
        if (cache[prev][cellsLeft] != -1) {
            return cache[prev][cellsLeft];
        }

        // special case: there is only one possible new num
        // this means there is only one possible valid array
        if (prev * 2 > maxVal) {
            return 1;
        }

        // consider every new num for next (multiples of prev)
        ll total = 0;
        for (int num = prev; num <= maxVal; num += prev) {
            total = (total + completeSearch(num, cellsLeft-1)) % MOD;
        }

        // update cache
        // cache[{prev, cellsLeft}] = total;
        cache[prev][cellsLeft] = total;

        return total;
    }
};

/*
nums in arr have to be in range 1 through maxValue inclusive
every element has to be divisible by prev element
    [2, 2] or [2, 4] or [2, 6] are valid
    2, 5 is not valid
    2, 4, 8 is valid
    2, 4, 6 is not valid because 4 followed by 6 fails 

complete search:
    select a number from 1 through max val for the first num
    try to generate the rest of the array 
        select the second number, skipping nums that are invalid
    note: state = array so far

dp intuition:
    state = prev number, number of cells left in array
    return: # ideal arrays aka valid permutations
    this state is better for caching because
        only 1 prev number instead of whole array
        the state describes the entire sub problem
note: given some prev number, there are only so many valid next sums
    they are simply the multiples of the prev num

how do we make it faster?
    with very large n: there are valid solutions, like all '1'
    our code considers max value by hitting that max value and then
    iterating O(n) for remaining cells, and only having that one valid solution where everything else is max value
    therefore, we have a shortcut:
        if the num is right before or equal to max value, then 
        there are no more multiples
        so all remaining cells must be that value
        so there is only 1 valid array

how else can we make it faster?
    maps are slow, we could use 2d array instead

what else?
    
*/
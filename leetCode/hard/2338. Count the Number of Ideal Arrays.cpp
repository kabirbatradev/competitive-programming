class Solution {
public:
    using ll = long long;

    const ll MOD = 1e9 + 7;

    const ll MAX_MAX_VALUE = 1e4 + 10;

    const ll MAX_N = 1e4 + 10;  // Maximum input number
    const ll MAX_PRIME_FACTOR_COUNT = 14 + 10;  // max number of duplicate prime factors
    // worst case: prime factorization is all '2's
    // in that case, max count is log_2(maxValue)
    // which is between 13 and 14

    const ll MAX_COMB = MAX_N + MAX_PRIME_FACTOR_COUNT;
    

    int idealArrays(int n, int maxValue) {

        // for every 'last' number, 
        // get the set of prime factors (and counts)
        // do stars and bars on each
        ll ans = 0;
        for (ll last = 1; last <= maxValue; last++) {

            // total ways to place all primes
            ll total = 1;

            for (auto [primeFactor, count] : primeFactorization(last)) {
                // prime factor value is irrelelvant

                // stars and bars result for this one prime factor
                ll waysToPlacePrimes = combinations[n-1 + count][count];
                total = (total * waysToPlacePrimes) % MOD;

                // cout << waysToPlacePrimes << endl;
            }
            ans = (ans + total) % MOD;
        }

        return ans;

    }

    // use constructor to do preprocessing before all test cases
    Solution() {

        // preprocessing alr complete
        if (spf.size() != 0) return;

        sieve();

        precomputeCombinations();

        // init prime factorization cache to -1
        primeFactorizationCache.assign(MAX_MAX_VALUE + 1, {});

    }

    // generate smallest prime factor for every num (from 1 to maxValue)
    vector<ll> spf; // spf = smallest prime factor
    void sieve() {
        spf.resize(MAX_MAX_VALUE+1);

        // init spf to "itself", which means, if we reach this number and it was not changed, this number is prime
        for (ll i = 0; i <= MAX_MAX_VALUE; i++) {
            spf[i] = i;
        }

        // loop through all nums up to sqrt(max value)
            // we dont go past that because smallest prime factor is always before that 
        // if spf is self, then this is a prime
        // if spf is not self, then we already set spf to the correct value
        for (ll i = 2; i*i <= MAX_MAX_VALUE; i++) {

            // spf is already set by another prime
            if (spf[i] != i) {
                continue;
            }

            // i must be prime:
            // for every multiple m of i, set spf of m to i
            // we start at i*i instead of i*2 or i*3, because
            // those multiples are already covered by 2 or 3 etc
                // 2 or 3 etc would have been the smaller prime factor
            // in other words:
                // the smallest num with the smallest prime factor
                // of 'i' is i^2
            for (ll m = i*i; m <= MAX_MAX_VALUE; m += i) {
                // ONLY set spf[m] if it hasn't been set before
                // otherwise spf no longer stores the "smallest" prime factor
                // ...possible to write prime factorization code differently
                    // to make it work with any prime factor
                if (spf[m] == m) {
                    spf[m] = i;
                }
            }
        }
    }

    // for some number, generates prime factorization:
    // list of [number, count]
    vector<vector<pair<ll, ll>>> primeFactorizationCache;
    vector<pair<ll, ll>> primeFactorization(ll n) {

        // if alr cached, return that
        if (!primeFactorizationCache[n].empty()) {
            return primeFactorizationCache[n];
        }

        ll originalN = n;

        vector<pair<ll, ll>> factors;

        // once n is 1, we have all the facotrs
        while (n > 1) {
            ll factor = spf[n]; // get smallest prime factor
            n /= factor; // divide it out from n

            // we need to create a new entry if:
            // size is 0
            // previous entry's number is not the same 
            if (factors.size() == 0 || factors.back().first != factor) {
                factors.push_back({factor, 1}); // new factor with count=1
            }
            else {
                factors.back().second++;
            }
        }

        // cache it
        // use original n!
        primeFactorizationCache[originalN] = factors;

        return factors;
    }

    vector<vector<ll>> combinations;
    void precomputeCombinations() {
        combinations.assign(
            MAX_COMB + 1, 
            vector<ll>(MAX_PRIME_FACTOR_COUNT + 1, 0)
        );

        // Base case: C(n,0) = 1 for all n
        for (ll n = 0; n <= MAX_COMB; n++) {
            ll k = 0;
            combinations[n][k] = 1;
        }

        // Fill the combination table using Pascal's identity:
        // C(n,r) = C(n-1,r-1) + C(n-1,r)
        for (ll n = 1; n <= MAX_COMB; n++) {
            // min() because 
            // we can only choose up to n elements
            // so k must be less or equal to n
            for (ll k = 1; k <= min(n, MAX_PRIME_FACTOR_COUNT); k++) {
                // note that we mod here since this is multiplied to the 
                // final solution
                combinations[n][k] = (
                    combinations[n-1][k-1] + combinations[n-1][k]
                ) % MOD;
            }
        }
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

dp lluition:
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
    time to read editorial (its been almost an hour)

new solution:

there are many potential last numbers 'last'
each has a prime factorization
that means, to get to that last number, 
we must have multipled all of those prime factors in the prime factorization
the array size is n
this means there are n-1 multiplications from start to end
but also we can start at any number
so really its like:
    there are n multiplications from start to end
    and we start at 1 forced
now we have a set and count of prime factors (in prime factorization)
    assume there are functions to do this for us
for each, we can choose a position to do the multiplication
    there are n positions to choose from
but: if there are multiple of the same prime factor, then 
    we are double counting
    2 combinations might be identical, with the identical prime factor swapped
instead:
    use stars and bars!
    you have c identical prime factors
    and n buckets, where you have to split the prime factors among the buckets
    
    so there are n-1 dividers/bars, and c stars to place
    total number of objects = n-1 + c
    and we need to choose c of those objects to be stars
    formula: n-1+c choose c

    note: for not identical prime factors, there is no double counting
    so they are independent problems, and we can just multiply the 
    result of each stars and bars 

how do we actually get prime factorization?

use sieve function to efficiently generate list of smallest prime factors
    for every number (from 2 to sqrt(max))
    if it is prime (assume it is), 
        then spf of every multiple of this num is this num
    if not prime, then spf should have been set by a prime earlier
        
get all prime factors:
    for some n,
    use spf to get smallest prime factor
    n = n / spf
    repeat until n = 1

    
*/
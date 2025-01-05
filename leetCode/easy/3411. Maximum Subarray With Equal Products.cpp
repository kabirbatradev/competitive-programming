class Solution {
public:
    using ll = long long;
    int maxLength(vector<int>& nums) {

        int bestLength = 0; 
        // one number: gcd = itself, lcm = itself, product is itself
        // this only works if num is 1

        for (int i = 0; i < nums.size(); i++) {
            ll product = nums[i];
            if (nums[i] == 1) bestLength = max(1, bestLength); // account for "1" case

            ll LCM = nums[i];
            ll GCD = nums[i];
            
            for (int j = i+1; j < nums.size(); j++) {
                // [i , j] is an inclusive subarray
                if (product > LONG_MAX / nums[j]) break; // if overflow, break subarray early
                product *= nums[j]; // latest product
                LCM = lcm(LCM, nums[j]);
                GCD = gcd(GCD, nums[j]);
                if (product == LCM * GCD) {
                    bestLength = max(j - i + 1, bestLength);
                }
                
            }
        }

        return bestLength;
        
    }
};

/*
class Solution {
public:
    using ll = long long;
    // ll LCM(ll a, ll  b) {return a * b / GCD(a, b)} // wait we dont have a GCD formula
    int maxLength(vector<int>& nums) {

        // apparently there are just formulas im supposed to use for this
        // LCM(a,b) = (a × b) / GCD(a,b); can be chained
        // my gcd idea was correct, but theres a formula for that too

        // greatest common divisor: greatest number that can divide every num
        // least common multiple: smallest number that is a multiple of every num

        // get LCM: 
        // divide num by small numbers starting at 2
        // if divides evenly, then replace num with new smaller num
        // and repeat
        // now we have prime factorization
        
        // compare 2 nums: (nvm)
        // if they share prime factors, then those get cancelled out(?)
        // now multiply remaining factors ...? idk

        // rethink get LCM:
        // multiply all unique nums together
        // divide by shared prime factors = GCD
        // that should result in LCM

        // get GCD: 
        // first get prime factorization
        // then find all shared prime factors and multiply them together
        // this product is the GCD


        // note this case: LCM = product, and GCD is just 1
        // would happen because nums have no shared prime factors?


        // int counts[11][11] = {0}; // first thing is num that we want prime factorization counts for
        vector<vector<int>> counts(11, vector<int>(11, 0));
        for (int i= 2; i <= 10; i++) {
            // counts[i] = ?

            int num = i;

            for (int j= 2; j <= 10; j++) {
                if (j > num) break;
                if (num % j == 0) {
                    // num found a prime factor, so make it smaller
                    counts[i][j]++;
                    num = num / j;
                    j = 1; // reset j to 2 after the increment
                }
                
            }
            
        }
        
        

        int bestLength = 0; // one number: gcd = itself, lcm = itself, product is itself
        // this only works if num is 1

        for (int i = 0; i < nums.size(); i++) {
            ll product = nums[i];
            if (nums[i] == 1) bestLength = max(1, bestLength);

            vector<int> sharedPrimeFactorsCounts = counts[nums[i]];
            
            set<int> uniqueNums;
            uniqueNums.insert(nums[i]);

            int uniqueProduct = nums[i];

            ll lcm = nums[i];
            
            for (int j = i+1; j < nums.size(); j++) {
                // [i , j] is an inclusive subarray

                product *= nums[j]; // latest product
                if (!uniqueNums.count(nums[j])) {
                    uniqueNums.insert(nums[j]);
                    uniqueProduct *= nums[j];
                }

                // int primeFactorizationCounts[11] = counts[nums[j]];
                vector<int>& primeFactorizationCounts = counts[nums[j]];

                ll gcd = 1;
                for (int k = 2; k <= 10; k++) {
                    sharedPrimeFactorsCounts[k] = min(
                        sharedPrimeFactorsCounts[k],
                        primeFactorizationCounts[k]
                    );
                    cout << sharedPrimeFactorsCounts[k] << " ";
                    if (sharedPrimeFactorsCounts[k] != 0) {
                        // gcd *= sharedPrimeFactorsCounts[k] * k;
                        // multiply gcd with k^count
                        for (int z = 0; z < sharedPrimeFactorsCounts[k]; z++)
                            gcd *= k;
                    }
                }
                cout << endl;

                
                // ll lcm = uniqueProduct / gcd;
                // lcm = LCM(lcm, nums[j]);
                lcm = lcm * nums[j] / gcd;

                cout << gcd << " " << lcm << endl;

                if (product == gcd * lcm) {
                    bestLength = max(j - i + 1, bestLength);
                }
                
            }
        }

        return bestLength;
        
    }
};
*/
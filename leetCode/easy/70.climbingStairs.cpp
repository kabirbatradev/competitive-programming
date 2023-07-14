class Solution {
public:

    unordered_map<int, int> alreadyComputed; 

    int climbStairs(int n) {

        // if n is in the map, then return that instead
        if (alreadyComputed.find(n) != alreadyComputed.end()) {
            return alreadyComputed.at(n);
        }
        if (n == 0 || n == 1) {
            return 1;
        }

        // update the map at n
        int ret = climbStairs(n-2) + climbStairs(n-1);
        alreadyComputed.insert({n, ret});

        return ret;
    }
};
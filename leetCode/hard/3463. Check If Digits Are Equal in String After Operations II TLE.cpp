class Solution {
public:
    bool hasSameDigits(string s) {

        // can we memoize?
        // string of digits is a subproblem:
        /*
        3902
        --> 
        292
        
        means 29 is 2, 90 is 9, and 02 is 2
        so the whole string becomes 292

        what about 390? --> 29
        so 3902 = 390 + 02
        = 29 + 2

        idk if this works because subproblems dont overlap...

        what about just caching 2 digit pairs?
        get 2 nums, ask for result in cache instead of computing with mod (slow)

        what about edge cases:
        all numbers are same? then last 2 digits will be same

        do we need to cache big chunks of the string and identify them to handle them quickly?
        like 123123
        = 1231 + 123
        = 123 + 31 + 123
        solve for 123 and 31 only once, and reuse! this could be a speedup!

        but where we do we decide where to break the string?
        find the longest repeating subsequences, and compute those once only
        maybe that means we need to use trie or something? nah that doesnt sound right

        what if we just broke string in the middle like d&c
        random chance that its cached
        continuously break string, hoping to hit something that was cached
        when building back up, store string results in cache
        123123:
        1231 123
        123 31 12 23
        12 23 31 12 23 
        then combine, but check in cache first
        will the cache memory overflow though? 
        the keys are every substring of super long string = every pair = n^2 different strings?

        what if we process strings 3 at a time and cache those
        and then 4 if needed instead
        so the max key len is 3 or 4 yk?

        but then generating that substring to check it in the cache is slow?
        3d array?
        
        */


        // even with this triple cache, i get TLE 667 / 683 testcases passed

        int cache[10][10] = {0};
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cache[i][j] = (i + j) % 10;
            }
        }

        int cache3D[10][10][10] = {0};
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    int a = cache[i][j];
                    int b = cache[j][k];
                    cache3D[i][j][k] = cache[a][b];
                }
            }
        }

        int size = s.length();
        while (size >= 4) { // if 4, then reduce by 2 to get 2 and stop
            // cout << s.substr(0, size) << endl;
            int allSame = true; // adding this failed to 619 / 683 testcases passed (fixed)
            int first = s[0];
            for (int i = 0; i < size-2; i++) {
                // cout << s[i] << " " << s[0] << endl;
                if (s[i] != first) allSame = false;
                int a = s[i] - '0';
                int b = s[i+1] - '0';
                int c = s[i+2] - '0';
                // int c = (a + b) % 10;
                // s[i] = (char)(cache[a][b] + '0');
                s[i] = (char)(cache3D[a][b][c] + '0');
            }
            if (s[size-1-1] != first) allSame = false; // check second last num as well!
            if (s[size-1] != first) allSame = false; // check last num as well!
            // cout << "all same: " << allSame << endl;
            if (allSame) return true; // return early
            // s.pop_back(); // remove last char might be too slow, so dont do it
            size--;
            size--; // got smaller by 2 bc we did 2 steps in one?
        }
        // edge case for 3: copy old solution
        while (size > 2) {
            // cout << s.substr(0, size) << endl;
            int allSame = true; // adding this failed to 619 / 683 testcases passed (fixed)
            int first = s[0];
            for (int i = 0; i < size-1; i++) {
                // cout << s[i] << " " << s[0] << endl;
                if (s[i] != first) allSame = false;
                int a = s[i] - '0';
                int b = s[i+1] - '0';
                // int c = (a + b) % 10;
                s[i] = (char)(cache[a][b] + '0');
            }
            if (s[size-1] != first) allSame = false; // check last num as well!
            // cout << "all same: " << allSame << endl;
            if (allSame) return true; // return early
            // s.pop_back(); // remove last char might be too slow, so dont do it
            size--;
        }
        
        return s[0] == s[1];
        


        // new solution: do not pop back string for size change
        // still TLE: 667 / 683 testcases passed
        // and return early if all nums same
        // 667 / 683 testcases passed still!

        // int cache[10][10] = {0};
        // for (int i = 0; i < 10; i++) {
        //     for (int j = 0; j < 10; j++) {
        //         cache[i][j] = (i + j) % 10;
        //     }
        // }

        // int size = s.length();
        // while (size > 2) {
        //     // cout << s.substr(0, size) << endl;
        //     int allSame = true; // adding this failed to 619 / 683 testcases passed (fixed)
        //     int first = s[0];
        //     for (int i = 0; i < size-1; i++) {
        //         // cout << s[i] << " " << s[0] << endl;
        //         if (s[i] != first) allSame = false;
        //         int a = s[i] - '0';
        //         int b = s[i+1] - '0';
        //         // int c = (a + b) % 10;
        //         s[i] = (char)(cache[a][b] + '0');
        //     }
        //     if (s[size-1] != first) allSame = false; // check last num as well!
        //     // cout << "all same: " << allSame << endl;
        //     if (allSame) return true; // return early
        //     // s.pop_back(); // remove last char might be too slow, so dont do it
        //     size--;
        // }
        // return s[0] == s[1];





        


        // new solution with cache: 667 / 683 testcases passed still!

        // int cache[10][10] = {0};
        // for (int i = 0; i < 10; i++) {
        //     for (int j = 0; j < 10; j++) {
        //         cache[i][j] = (i + j) % 10;
        //     }
        // }

        // while (s.length() > 2) {
        //     for (int i = 0; i < s.size()-1; i++) {
        //         int a = s[i] - '0';
        //         int b = s[i+1] - '0';
        //         // int c = (a + b) % 10;
        //         s[i] = (char)(cache[a][b] + '0');
        //     }
        //     s.pop_back(); // remove last char
        // }
        // return s[0] == s[1];



        // old solution TLE: 667 / 683 testcases passed
        // while (s.length() > 2) {
        //     for (int i = 0; i < s.size()-1; i++) {
        //         int a = s[i] - '0';
        //         int b = s[i+1] - '0';
        //         int c = (a + b) % 10;
        //         s[i] = (char)(c + '0');
        //     }
        //     s.pop_back(); // remove last char
        // }
        // return s[0] == s[1];
    }
};


// old solution:
// class Solution {
// public:
//     bool hasSameDigits(string s) {
//         while (s.length() > 2) {
//             for (int i = 0; i < s.size()-1; i++) {
//                 int a = s[i] - '0';
//                 int b = s[i+1] - '0';
//                 int c = (a + b) % 10;
//                 s[i] = (char)(c + '0');
//             }
//             s.pop_back(); // remove last char
//         }
//         return s[0] == s[1];
//     }
// };
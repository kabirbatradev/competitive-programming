class Solution {
public:
    int minChanges(int n, int k) {

        // can only change n's bits to 0
        int counter = 0;
        while (!(n == 0 && k == 0)) {
            // cout << n << endl;
            // cout << k << endl;
            // cout << endl;
            // last bit
            // n & 1;

            if ((n & 1) == (k & 1)) {
                // same last bit
                n = n >> 1;
                k = k >> 1;
                continue;
            }

            if ((n & 1) == 1) {
                counter++;
                n = n >> 1;
                k = k >> 1;
                continue;
            }

            if ((n & 1) == 0) {
                return -1;
            }
            
        }

        return counter;
        
    }
};
class Solution {
public:
    double myPow(double x, int n) {
        // memoize? might not be needed

        // cout << "x: " << x << " n: " << n << endl;

        if (x == 0) return 0.;
        if (n == 0) {
            // exponent is 0
            // return x > 0. ? 1. : -1.; // technically correct
            return 1.;
        }
        if (x == 1) return 1; // base is 1
        if (n == 1) return x; // exponent is 1
        // if (n < 0) { 
        //     // negative exponent (error: n is negative integer max)
        //     return 1. / myPow(x, -n);
        // }
        long longn = n;
        bool negativeExponent = false;
        if (n < 0) {
            negativeExponent = true;
            // longn = -n;
            longn = -longn;
        }

        // split the calculation in half
        double ans = 1.;
        int halfPower = int(longn / 2); // integer division

        ans *= myPow(x, halfPower);
        ans *= ans;

        // if n was odd, then we need 1 more power
        if (longn % 2 == 1) {
            ans *= x;
        }
        
        if (negativeExponent) {
            ans = 1. / ans;
        }

        return ans;
    }
};
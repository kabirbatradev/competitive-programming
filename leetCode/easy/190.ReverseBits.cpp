class Solution {
public:
    uint32_t reverseBits(uint32_t n) {

        uint32_t ret = 0;

        for (char i = 0; i < 32; i++) {
            ret = ret << 1; // shift ret left one to make a empty spot on the right
            ret = ret | (n&1); // write the rightmost bit of n to the rightmost spot
            n = n >> 1; // shift n to the right by 1 (deleting the right most bit)
        }

        return ret;
        
    }
};
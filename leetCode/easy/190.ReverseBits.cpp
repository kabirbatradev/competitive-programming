class Solution {
public:
    uint32_t reverseBits(uint32_t n) {

        uint32_t ret = 0;

        uint32_t singleBit = 0;
        for (int i = 0; i < 32; i++) {
            singleBit = n & 1; // extract the right most bit
            n = n >> 1; // shift n to the right by 1

            ret = ret << 1; // shift ret left one to make a empty spot on the right
            ret = ret | singleBit; // write the single bit to the rightmost spot
        }

        return ret;
        
    }
};
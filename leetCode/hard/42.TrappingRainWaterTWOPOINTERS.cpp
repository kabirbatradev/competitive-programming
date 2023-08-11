class Solution {
public:
    int trap(vector<int>& height) {

        // new perspective: how much water can we trap per bar
        // for each tile, we can trap min(tallestLeft, tallestRight)

        // instead of generating lists for tallestLeft and tallestRight, use 2 pointers
        int maxLeft = height.at(0), maxRight = height.at(height.size()-1);

        // start pointers off by 1 because left and right sides guaranteed to not have water
        int leftPointer = 1, rightPointer = height.size()-2;

        int trappedWater = 0;
        
        // get the water trappable on the pointer next to the less max height side
        while (leftPointer <= rightPointer) {
            if (maxLeft <= maxRight) {
                // check left pointer for water, shift left pointer, update maxLeft
                if (maxLeft > height.at(leftPointer)) {
                    // max is greater than height, so water was trapped
                    trappedWater += maxLeft - height.at(leftPointer);
                }
                else {
                    // max is less than height, so max should be updated
                    maxLeft = height.at(leftPointer);
                }
                leftPointer++;
            }
            else {
                // check right pointer for water, shift right pointer, update maxRight
                if (maxRight > height.at(rightPointer)) {
                    trappedWater += maxRight - height.at(rightPointer);
                }
                else {
                    maxRight = height.at(rightPointer);
                }
                rightPointer--;
            }
        }

        return trappedWater;
        
    }
};
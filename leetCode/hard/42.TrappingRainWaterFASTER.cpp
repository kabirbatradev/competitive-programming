class Solution {
public:
    int trap(vector<int>& height) {

        // new perspective: how much water can we trap per bar
        // for each tile, we can trap min(tallestLeft, tallestRight)

        // build tallestLeft and tallestRight lists:
        int tallestLeft[height.size()];
        int tallestRight[height.size()];

        // init start of tallestLeft
        tallestLeft[0] = 0;
        for (int i = 1; i < height.size(); i++) {
            tallestLeft[i] = max(tallestLeft[i - 1], height.at(i - 1));
        }

        // init end of tallestRight and iterate backward
        tallestRight[height.size()-1] = 0;
        for (int i = height.size() - 2; i >= 0; i--) {
            tallestRight[i] = max(tallestRight[i+1], height.at(i+1));
        }

        // now sum up how much we can trap per bar
        int sum = 0;
        for (int i = 0; i < height.size(); i++) {
            sum += max(0, 
                min(tallestLeft[i], tallestRight[i]) - height.at(i)
            );
        }

        return sum;
        
    }
};
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
        // imagine 3 x 5 matrix
        // for (int i = 0; i < 3 * 5; i++) {
        //     cout << (i / 3) << " " << (i % 3) << endl;
        // }

        // return false;


        int min = 0;
        int max = matrix.size() * matrix.at(0).size() - 1;
        if (target > matrix.at(max/matrix.at(0).size()).at(max%matrix.at(0).size()) || target < matrix.at(min/matrix.at(0).size()).at(min%matrix.at(0).size())) return false;
        while (max >= min) {
            int middle = (max + min) / 2;
            int row = middle / matrix.at(0).size();
            int col = middle % matrix.at(0).size();
            int numAtMiddle = matrix.at(row).at(col);

            if (numAtMiddle == target) {
                return true;
            }
            else if (target > numAtMiddle) {
                min = middle + 1;
            }
            else {
                max = middle - 1;
            }
        }
        return false;
    }
};
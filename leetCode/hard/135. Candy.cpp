// solution based on neetcode video: (3 min implementation)
class Solution {
public:
    int candy(vector<int>& ratings) {

        vector<int> v(ratings.size(), 1);

        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i-1]) {
                v[i] = v[i-1] + 1;
            }
        }

        for (int i = ratings.size()-2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1]) {
                if (v[i] <= v[i+1])
                    v[i] = v[i+1] + 1;
            }
        }

        return accumulate(v.begin(), v.end(), 0);
        
    }
};

// class Solution {
// public:
//     int candy(vector<int>& ratings) {
//         int total = 0;

//         int currentHeight = 1;
//         total++; // for first rating

//         int decreasingChain = 0;
//         int peak = 1;

//         for (int i = 1; i < ratings.size(); i++) {
//             int slope = ratings[i] - ratings[i-1];
//             if (slope < 0) {
//                 decreasingChain++;
//                 currentHeight = 1; 
//             }
//             else {

//                 // no longer decreasing
//                 // walk back up decreasing chain, adding to total
//                 // check height with peak (if higher, then peak needs to be updated)
//                 if (decreasingChain != 0) {
//                     // for (int j = 0; j < decreasingChain; j++) {
//                     //     total += j+1;
//                     // }
//                     total += (decreasingChain+1) * decreasingChain / 2;
//                     // at peak, should be decreasingChain+1
//                     if (peak < decreasingChain+1) total += decreasingChain+1 - peak;

//                 }

//                 if (slope > 0) { 
//                     currentHeight++;
//                 }
//                 else if (slope == 0) {
//                     // repeated number; can reset to 1
//                     currentHeight = 1;
//                 }

//                 total += currentHeight;
//                 decreasingChain = 0;

//                 peak = currentHeight;

//             }
//         }

//         // handle ending on a decreasing chain (unfortunate duplicate code)
//         if (decreasingChain != 0) {
//             total += (decreasingChain+1) * decreasingChain / 2;
//             if (peak < decreasingChain+1) total += decreasingChain+1 - peak;
//         }


//         return total;
//     }
// };
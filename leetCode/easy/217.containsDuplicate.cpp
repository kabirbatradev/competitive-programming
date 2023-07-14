#include <unordered_set>
#include <iostream>

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);

        unordered_set<int> mySet;


        for (int i = 0; i < nums.size(); i++) {
            if (mySet.insert(nums.at(i)).second == 0) {
                return true;
            }
        }






        // for (int num : nums) {
        //     // if (mySet.find(num) == mySet.end()) {
        //     //     mySet.insert(num);
        //     // }
        //     // else {
        //     //     // duplicate found bc its in the set alr
        //     //     return true;
        //     // }

        //     if (mySet.insert(num).second == 0) {
        //         // insert did not occur, so there is a duplicate
        //         // returns a pair: iterator, bool
        //         return true;
        //     }
            
        // }
        // cout << (mySet.find(nums.at(0)) != mySet.end()) << endl;
        // cout << true << false << endl;



        return false;
    }
};
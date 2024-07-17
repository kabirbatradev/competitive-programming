class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        // solution 1: 
        // sort each string (the lengths are quite short)
        // then put them all in a map<key = sorted string, value = list of all of the solutions
        // runtime: nlog(n) * m

        unordered_map<string, vector<string>> groups;

        for (string s : strs) {
            string clone = s; // unsorted clone
            sort(s.begin(), s.end());
            if (groups.count(s) == 0) {
                groups[s] = {clone};
            }
            else {
                groups[s].push_back(clone);
            }
        }

        vector<vector<string>> ret;
        for (auto group : groups) {
            vector<string> actualGroup = group.second;
            ret.push_back(actualGroup);
        }

        return ret;

    }
};
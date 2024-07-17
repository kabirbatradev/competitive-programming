class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        // solution 2:
        // hash the characters in the string instead of sorting
        // then make a hash table of the hashed strings
        // we cannot hash maps but we can hash a count array

        // count array for each string: array of size 26 of counts where the first entry is the letter a
        // table<key = int[26], value = list of original grouped strings>

        // it would have worked in python with a tuple gg
        unordered_map<int[26], vector<string>> groups;

        for (string s : strs) {
            int counts[26] = {0};

            for (char c : s) {
                int index = c - 'a';
                counts[index]++;
            }

            if (groups.count(counts) == 0) {
                groups[counts] = {s};
            }
            else {
                groups[counts].push_back(s);
            }

        }
        vector<vector<string> ret;
        for (auto pair : groups) {
            vector<string> group = pair.second;
            ret.push_back(group);
        }

        return ret;



        // solution 1: 
        // sort each string (the lengths are quite short)
        // then put them all in a map<key = sorted string, value = list of all of the solutions>
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
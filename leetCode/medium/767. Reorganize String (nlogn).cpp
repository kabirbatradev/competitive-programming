class Solution {
public:
    string reorganizeString(string s) {
        int counts[26] = {0};
        for (char c : s) {
            counts[c - 'a']++;
        }

        // weight=count, letter value
        priority_queue<pair<int, char>> pq;
        for (int i = 0; i < 26; i++) {
            if (counts[i] != 0)
                pq.push(make_pair(counts[i], 'a' + i));
        }

        string finalString;
        finalString.reserve(s.size());

        pair<int, char> prev = make_pair(0, 0); // 0 count means do not insert
        while (!pq.empty()) {
            auto curr = pq.top(); pq.pop();
            // cout << curr.first << " " << curr.second << endl;

            curr.first--; // decrement count
            finalString.push_back(curr.second); // append to stirng

            // after processing max element, reinsert char that was used prev
            if (prev.first != 0) {
                pq.push(prev);
            }
            // and now set prev:
            prev = curr;
        }
        // if prev still has more characters, we would have to use that character back to back
        if (prev.first > 0) {
            return "";
        }

        return finalString;
        
    }
};

/*
get all of the letter counts (histogram)

repeatedly play the letter of the greatest count first
if that letter was just played, then play the letter with the second greatest count

pq approach (prevent repeated uses)
weight = count
remove top item and store it in "prev used"
remove top item and then add back the prev used item
*/
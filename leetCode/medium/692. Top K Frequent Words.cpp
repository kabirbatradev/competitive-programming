class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // put all words into map for counting
        // transfer the map values into a pq with custom compare
        // pop and return the first k elements 

        unordered_map<string, int> counts;

        for (string& word : words) {
            // map int defaults to 0, so no need to check if already in map:
            counts[word]++;

            // // already in map
            // if (counts.count(word)) {
            //     counts[word]++;
            // }
            // else {
            //     counts[word] = 1;
            // }
        }

        // comparison for min heap is backward--> "greater"
        auto compare = [](pair<string, int> a, pair<string, int> b) {
            // if counts are the same
            if (a.second == b.second) {
                return a.first < b.first; // backward lexicographic --> "less than"
            }
            return a.second > b.second; // smaller count first --> "greater"
        };

        // comparison for max heap
        // auto compare = [](pair<string, int> a, pair<string, int> b) {
        //     // if counts are the same
        //     if (a.second == b.second) {
        //         return a.first > b.first; // earlier string first --> "less than"
        //     }
        //     return a.second < b.second; // larger count first --> "greater"
        // };
        priority_queue<pair<string, int>, vector<pair<string,int>>, decltype(compare)> pq;

        for (auto& pair : counts) {
            pq.push(pair);

            // O(nlog(k)) trick: remove from pq if we have enough numbers
            // this removes the least frequency number (since we have a min heap)
            // guarantees each push takes O(logk)
            if (pq.size() > k) pq.pop();
        }

        vector<string> ret;
        for (int i = 0; i < k; i++) {
            ret.push_back(pq.top().first);
            pq.pop();
        }

        // since we had a min heap, our solution is actually reversed
        reverse(ret.begin(), ret.end());

        return ret;
    }
};

/*
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // put all words into map for counting
        // transfer the map values into a vector of pairs (count, string)
        // sort this vector: it will automatically sort by count and then lexicographical order
        // return the first k elements in the vector

        unordered_map<string, int> counts;

        for (string& word : words) {
            // already in map
            if (counts.count(word)) {
                counts[word]++;
            }
            else {
                counts[word] = 1;
            }
        }

        vector<pair<int, string>> v;
        for (auto& pair : counts) {
            v.push_back(make_pair(pair.second, pair.first));
        }
        
        auto compare = [](pair<int, string> a, pair<int, string> b) {
            // if counts are the same
            if (a.first == b.first) {
                return a.second < b.second; // earlier string first --> "less than"
            }

            return a.first > b.first; // larger count first --> "greater"
        };
        sort(v.begin(), v.end(), compare);

        vector<string> ret;
        for (int i = 0; i < k; i++) {
            ret.push_back(v[i].second);
        }

        return ret;
    }
};
*/
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        // select k elements from grid
        // # taken from ith row <= limits[i]

        // greedy? take largest numbers first, until ith row of largest is filled
        // then take largest numbers from other rows until those limits are filled

        // put all nums in pq along with row it came from
        // if row counter = limit, then skip future numbers from that row
        int n = grid.size();
        int m = grid[0].size();

        priority_queue<pair<int, int>> pq; // val, row number, max heap by default
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pq.push(make_pair(grid[i][j], i));
            }
        }
        long long sum = 0;
        int count = 0; // stop at count = k
        int limitsReached = 0; // if limits reached = n = number of rows, then stop
        while (!pq.empty() && count != k && limitsReached != n) {
            auto [val, row] = pq.top(); pq.pop();
            // cout << "consider val: " << val << endl;
            if (limits[row] == 0) continue;
            
            limits[row]--;
            if (limits[row] == 0) {
                limitsReached++; // return early if all limits reached
            }

            // cout << "using val: " << val << endl;

            sum += val;
            count++; // increment number of nums used
        }
        return sum;
    }
};
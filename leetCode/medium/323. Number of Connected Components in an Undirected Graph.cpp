class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {

        // adj list, size n, all empty by default
        vector<vector<int>> adjList(n, vector<int>());

        for (vector<int>& edge : edges) {
            int a = edge[0];
            int b = edge[1];
            adjList[a].push_back(b);
            adjList[b].push_back(a);
        }

        vector<bool> visited(n, false);

        // dfs repeatedly
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            dfs(i, adjList, visited);
            count++;
        }
        
        return count;

    }

    void dfs(int node, vector<vector<int>>& adjList, vector<bool>& visited) {
        if (visited[node]) return;

        visited[node] = true;

        for (int neighbor : adjList[node]) {
            dfs(neighbor, adjList, visited);
        }
    }
};

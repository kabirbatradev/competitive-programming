class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // [a, b] means a has prereq b 
        // if a has no prereqs, then indegree = 0
        // b --> a

        // make adjacency list
        vector<vector<int>> adj;

        // make queue thing
        queue<int> q;

        int inDegrees[numCourses];
        // inDegrees = {0};
        for (int i = 0; i < numCourses; i++) {
            inDegrees[i] = 0;
            // cout << inDegrees[i] << " ";
            adj.push_back(vector<int>());
        }

        for (vector<int> req : prerequisites) {
            // a has prereq so increase indegree of a
            inDegrees[req.at(0)] += 1;
            adj.at(req.at(1)).push_back(req.at(0));
        }

        for (int i = 0; i < numCourses; i++) {
            if (inDegrees[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int nextNode = q.front();
            q.pop();

            for (int adjNode : adj.at(nextNode)) {
                inDegrees[adjNode]--;
                if (inDegrees[adjNode] == 0) {
                    q.push(adjNode);
                }
            }
            
        }

        for (int i = 0; i < numCourses; i++) {
            if (inDegrees[i] != 0) {
                return false;
            }
        }

        return true;
    }
};
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prereq) {
        
        // topological sort

        // find the indegrees of all of the nodes
        // also have adjacency list of all nodes
        // if indegree is 0, add it to a queue
        // remove items from queue to create order

        vector<vector<int>> adjLists;
        vector<int> indegrees;
        for (int i = 0; i < numCourses; i++) {
            adjLists.push_back(vector<int>());
            indegrees.push_back(0);
        }
        // optimizations:
        // adjList --> vector<int> adjLists[numCourses]
            // automatically does "adjLists.push_back(vector<int>())"
        // indegrees --> vector<int> indegrees(numCourses, 0) 
            // using constructor to specify size and inital value


        for (vector<int>& pair : prereq) {
            // pair[0] 
            // pair[1] prereq

            indegrees.at(pair[0])++;
            adjLists.at(pair[1]).push_back(pair[0]);

        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegrees.at(i) == 0) {
                q.push(i);
            }
        }

        vector<int> finalOrder;
        while (!q.empty()) {
            int nextNode = q.front();
            q.pop();
            
            finalOrder.push_back(nextNode);
            for (int adjNode : adjLists.at(nextNode)) {
                indegrees.at(adjNode)--;
                if (indegrees.at(adjNode) == 0) {
                    q.push(adjNode);
                }
            }
        }

        if (finalOrder.size() == numCourses) {
            return finalOrder;
        }
        return vector<int>();

    }
};
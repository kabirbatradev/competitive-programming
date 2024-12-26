class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

        vector<int> inDegree(numCourses, 0);

        vector<vector<int>> adjList(numCourses, vector<int>());

        for (vector<int>& prereq : prerequisites) {
            int start = prereq[0];
            int end = prereq[1];
            adjList[start].push_back(end);
            inDegree[end]++;
        }

        queue<int> q;
        for(int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int canTake = 0;
        while (!q.empty()) {
            int prereq = q.front();
            q.pop();

            for (int course : adjList[prereq]) {
                inDegree[course]--;
                if (inDegree[course] == 0) {
                    q.push(course);
                }
            }
            canTake++;
        }

        return canTake == numCourses;
        
    }
};
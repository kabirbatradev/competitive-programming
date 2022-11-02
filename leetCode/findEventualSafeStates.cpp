class Solution {
public:
    vector<int> nodeStates;
    vector<int> safeNodes;

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        
        nodeStates.reserve(graph.size());
        
        // node states:
            // -1: not visited
            // 0: safe
            // 1: not safe
            // 2: visited
        
        for (int i = 0; i < graph.size(); i++) {
            nodeStates.push_back(-1);
        }
        
        
        for (int i = 0; i < graph.size(); i++) {
            // if not visited, then DFS from that node
            if (nodeStates.at(i) == -1) {
                DFS(i, graph);
            }
        }
        
        // for (int i = 0; i < graph.size(); i++) {
        //     cout << i << " " << nodeStates.at(i) << endl;
        // }

        
        // return array of all safe nodes
        sort(safeNodes.begin(), safeNodes.end());
        return safeNodes;
        
        
    }
    
    void DFS(int newNode, vector<vector<int>>& graph) {
        nodeStates.at(newNode) = 2;
        
        // iterate through adjacency list
        vector<int> adjList = graph.at(newNode);
        
        bool areWeSafe = true;
        
        for (int i = 0; i < adjList.size(); i++) {
            int adjNode = adjList.at(i);
            if (nodeStates.at(adjNode) == -1) {
                // not visited
                // then DFS this node and check what it ends up being
                DFS(adjNode, graph);
            }
            
            
            if (nodeStates.at(adjNode) == 0) {
                // safe
                // then we are safe so far
                continue;
            }
            else if (nodeStates.at(adjNode) == 1) {
                // not safe
                areWeSafe = false;
                break;
            }
            else if (nodeStates.at(adjNode) == 2) {
                // already visited
                areWeSafe = false;
                break;
            }
        }
        
        if (areWeSafe) {
            nodeStates.at(newNode) = 0;
            safeNodes.push_back(newNode);
        }
        else {
            nodeStates.at(newNode) = 1;
        }
        
        
    }
};
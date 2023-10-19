class NodeAndDistance {
    public:    
    int i, d; // node index, distance
    NodeAndDistance(int i, int d): i(i), d(d) {}
};

class Compare {
    public:
    bool operator() (NodeAndDistance a, NodeAndDistance b) {
        return a.d > b.d;
    }
};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // n is number of nodes
        // times[i] contains edge u to v with weight w
        // k is the start node

        // dijkstra's algo implement practice problem

        
        // first create adjacency list 
        vector<vector<int>> adjList[n];
        // adjList[u] returns list of pairs {v, w} 
            // this represents an edge from u to v with weight w

        for (vector<int> edge : times) {
            int u = edge[0]-1;
            int v = edge[1]-1;
            int w = edge[2];
            adjList[u].push_back({v, w});
        }


        // run dijkstras with a priority queue

        // keep track of visited and distances
        int distances[n];
        for (int i = 0; i < n; i++) {
            distances[i] = -1; // not visited
        }

        priority_queue<NodeAndDistance, vector<NodeAndDistance>, Compare> pq;
        pq.push(NodeAndDistance(k-1, 0)); // push the first node
        // contains all edges that are currently accessible and the total distance required to get there
        while (!pq.empty()) {
            NodeAndDistance nd = pq.top();
            pq.pop();

            // if already visited, then skip
            if (distances[nd.i] != -1) continue;

            // update distances
            distances[nd.i] = nd.d;

            // for every adjacent node, add the new distance to it to the pq
            for (vector<int> nodeAndWeight : adjList[nd.i]) {
                NodeAndDistance newND(nodeAndWeight[0], nodeAndWeight[1] + nd.d);
                pq.push(newND);
            }
        }

        int big = -1;
        for (int i = 0; i < n; i++) {
            if (distances[i] == -1) return -1;
            big = max(big, distances[i]);
        }
        
        return big;
    }
};
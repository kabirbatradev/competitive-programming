/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    map<Node *, Node *> cloneMap;
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        Node *copyNode = new Node(node->val);
        cloneMap[node] = copyNode;
        // for each neighbor, clone its graph
        // but dont a node if it already exists
        for (Node *neighbor : node->neighbors) {
            if (cloneMap.count(neighbor) != 0) {
                copyNode->neighbors.push_back(cloneMap[neighbor]);
            }
            else {
                copyNode->neighbors.push_back(
                    cloneGraph(neighbor)
                );
            }
        }

        return copyNode;
    }
};
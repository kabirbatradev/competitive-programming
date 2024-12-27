/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        using Node = TreeNode; // I forgot its called TreeNode instead of Node oops

        if (root == nullptr) return {};

        vector<vector<int>> ret(1, vector<int>()); // initialize the first level to an empty list

        // alterating queues idea: always push to the other queue
            // when queue is empty, then that level is complete

        bool usingQueue0 = true;

        queue<Node *> q0;
        queue<Node *> q1;

        q0.push(root);
        
        while (true) {

            queue<Node *>& q = usingQueue0 ? q0 : q1;
            queue<Node *>& otherQ = usingQueue0 ? q1 : q0;

            while (!q.empty()) {
                Node* current = q.front();
                q.pop();

                ret.back().push_back(current->val); // push val
                // push children to other queue
                if (current->left != nullptr) otherQ.push(current->left);
                if (current->right != nullptr) otherQ.push(current->right);
            }

            // now queue is empty

            // if the other queue is also empty, then we are done
            if (otherQ.empty()) break;

            // otherwise, there are still nodes in the other level
            
            ret.push_back({}); // add new level to ret
            usingQueue0 = !usingQueue0; // toggle which queue is being used
        }

        return ret;
        
        
    }
};
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
        using Node = TreeNode;

        if (root == nullptr) return {};

        // initialize the first level to an empty list
        vector<vector<int>> ret; 

        queue<Node *> q;
        q.push(root);
        
        while (!q.empty()) {
            
            int count = q.size(); // nodes in this level
            // ret.push_back({});
            ret.emplace_back(count); // creates a vector of the known size

            for (int i = 0; i < count; i++) {

                Node* current = q.front();
                q.pop();

                ret.back()[i] = current->val; // put val in the last level 
                // push children if they exist
                if (current->left != nullptr) q.push(current->left);
                if (current->right != nullptr) q.push(current->right);

            }

        }

        return ret;
        
        
    }
};
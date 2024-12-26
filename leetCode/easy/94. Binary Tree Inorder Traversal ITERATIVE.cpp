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
    vector<int> inorderTraversal(TreeNode* root) {

        // interative solution: 

        if (root == nullptr) return {};
        stack<TreeNode*> s;
        set<TreeNode*> visited;
        s.push(root);
        
        vector<int> ret;

        while (!s.empty()) {
            TreeNode *top = s.top();

            // if already visited, then already went left, so "print" and go right this time
            if (visited.count(top)) {
                ret.push_back(top->val);
                s.pop();
                if (top->right != nullptr)
                    s.push(top->right);
            }
            // otherwise go left and mark visited (and don't pop it)
            else {
                if (top->left != nullptr)
                    s.push(top->left);
                visited.insert(top);
            }
        }

        return ret;
    }
};
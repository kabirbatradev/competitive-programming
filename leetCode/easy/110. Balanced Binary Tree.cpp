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
    int fail = false;
    bool isBalanced(TreeNode* root) {

        if (root == nullptr) return true;

        getDepth(root);

        return !fail;
        
    }

    int getDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        // if (root->left == nullptr && root->right == nullptr) return 1;
        // if (root->left == nullptr)
        int l = getDepth(root->left);
        int r = getDepth(root->right);

        if (abs(l - r) >= 2) {
            fail = true;
            return 0; // doesnt matter what we return
        }

        return max(l, r) + 1;
    }
};
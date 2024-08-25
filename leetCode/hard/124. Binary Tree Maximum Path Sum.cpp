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

    struct both {
        int complete;
        int incomplete;
    };

    int maxPathSum(TreeNode* root) {

        both ans = traverse(root);
        
        return max(ans.complete, ans.incomplete);
    }

    // dp(subtree) can return best incomplete path that goes through root of subtree (can still grow this path)
    // or return past complete path that stops before the root or goes through the root into the other side of the tree
    
    // cases for dp are: 
    // stop at the incomplete path returned by left and right, return as the best complete path
    // return the prev best complete path
    // return the root node by itself as best incomplete
    // return root plus one side as best incomplete
    // make new best complete path: left plus root plus right as best complete

    both traverse(TreeNode* root) {
        
        // dont let this happen
        // if (root = nullptr) {
        //     return  ...
        // }
        

        both ret;
        // default min values can be the root itself
        ret.complete = ret.incomplete = root->val;

        both leftResult;
        both rightResult;
        if (root->left != nullptr){
            leftResult = traverse(root->left);

            ret.complete = max(ret.complete, leftResult.complete); // prev complete
            ret.complete = max(ret.complete, leftResult.incomplete); // prev incomplete without adding root
            ret.incomplete = max(ret.incomplete, leftResult.incomplete + root->val); // prev incomplete with root
            ret.complete = max(ret.complete, leftResult.incomplete + root->val); // get with root added to complete as well bc why not
        }
        if (root->right != nullptr) {
            rightResult = traverse(root->right);

            ret.complete = max(ret.complete, rightResult.complete); // prev complete
            ret.complete = max(ret.complete, rightResult.incomplete); // prev incomplete without adding root
            ret.incomplete = max(ret.incomplete, rightResult.incomplete + root->val); // prev incomplete with root
            ret.complete = max(ret.complete, rightResult.incomplete + root->val); // get with root added to complete as well bc why not (some edge cases)
        }

        // new complete: go through root (with incompletes from both sides)
        if (root->left != nullptr && root->right != nullptr) {
            ret.complete = max(ret.complete, leftResult.incomplete + root->val + rightResult.incomplete);
        }

        // printf("node %d returning %d for complete\n", root->val, ret.complete);
        return ret;


    }

};
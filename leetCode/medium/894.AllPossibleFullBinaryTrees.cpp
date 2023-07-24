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
    vector<TreeNode*> dp[21];
    vector<TreeNode*> allPossibleFBT(int n) {

        // even though I used memoization, it isn't any faster
        if (dp[n].size() > 0) 
            return dp[n];

        if (n % 2 == 0) {
            return vector<TreeNode*>();
        }

        // one node for the root
        n--;

        if (n == 0) {
            // if no remaining nodes
            return {new TreeNode()};
        }

        vector<TreeNode*> allTrees;
        // try every combination of left and right nodes
        for (int i = 1; i < n; i += 2) {
            int numLeftNodes = i;
            int numRightNodes = n - i;
            // cout << numLeftNodes << " " << numRightNodes << endl;

            vector<TreeNode*> leftList = allPossibleFBT(numLeftNodes);
            vector<TreeNode*> rightList = allPossibleFBT(numRightNodes);

            for (TreeNode *leftRoot : leftList) {
                for (TreeNode *rightRoot : rightList) {
                    // create a new root
                    TreeNode *root = new TreeNode();

                    // create a deep copy of the left and right trees
                    // it seems we did not have to make a deep copy...
                    // this is because we are treating the subtrees as read-only

                    root->left = leftRoot;
                    root->right = rightRoot;
                    allTrees.push_back(root);
                }
            }
        }
        dp[n] = allTrees;

        return allTrees;

    }
};
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    union ThreeChars {
        // first two bytes for the value, the third byte for representing node children (2 bits)
        char c[3]; 
        short s;
        // bool b[16]; // bools will take a whole byte instead of a bit

    };

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // cout << "serialize" << endl;

        // function can call itself to serialize subtree; then append serialization to return string

        if (root == NULL) return "";

        string ret = "";

        bool isNegative = root->val < 0;
        ThreeChars value;
        // value.s = (short)abs(root->val);
        value.s = (short)root->val;

        // value.s = 1000;
        // cout << sizeof(ThreeChars) << endl;

        // for (int i = 0; i < 3; i++) {
        //     cout << (int)value.c[i] << " ";
        // }
        // cout << endl;

        char leftRightFlags = 0;
        if (root->left != NULL) {
            leftRightFlags += 1; // first bit
        }
        if (root->right != NULL) {
            leftRightFlags += 2; // second bit
        }
        
        value.c[2] = leftRightFlags;

        // for (int i = 0; i < 3; i++) {
        //     cout << (int)value.c[i] << " ";
        // }
        // cout << endl;

        // put information of this node on the string
        // first two bytes for the value, the third byte for representing node children (2 bits)
        ret += value.c[0];
        ret += value.c[1];
        ret += value.c[2];

        

        // put information of children onto string (in DFS fashion, where left subtree is put first)
        if (root->left != NULL) {
            ret += serialize(root->left);
        }
        if (root->right != NULL) {
            ret += serialize(root->right);
        }
        
        return ret;
    }

    
    int currentDecodePosition = 0;

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string &data) {
        // cout << "deserialize" << endl;

        // recursive breakdown of the data to generate the tree, the function stack represents the branch of the tree we are currently on

        // if (data == "") return NULL;
        if (currentDecodePosition == data.length()) return NULL;

        ThreeChars value;
        string valueString = data.substr(currentDecodePosition, 3);

        // for (int i = 0; i < 3; i++) {
        //     cout << (int)valueString[i] << " ";
        // }
        // cout << endl;

        value.c[0] = valueString[0];
        value.c[1] = valueString[1];
        value.c[2] = valueString[2];
        currentDecodePosition += 3;

        TreeNode* root = new TreeNode(value.s);

        bool hasLeftChild = value.c[2] & 0b01;
        bool hasRightChild = value.c[2] & 0b10;

        if (hasLeftChild) {
            root->left = deserialize(data);
        }
        
        if (hasRightChild) {
            root->right = deserialize(data);
        }

        return root;
        
    }

    // value -1000 -> 1000 means 2000 possible values means 11 bits means 2 characters (16 bits) per value
        // negative sign can be stored as first bit leaving 15 bits, 10 are used to represent the value
        // last 5 bits can be used to represent additional information, 
            // like whether a node is a leaf, has a left child, a right child, or both children
    
    
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class TreeInstance {
public:
    struct TreeNode {
        int value;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {};
    };

    TreeNode *
    CreateTree(vector<int> preSearch, vector<int> midSearch, int preLeft, int preRight, int midLeft, int midRight) {
        // judge whether empty subTree
        if (preLeft > preRight) {
            return nullptr;
        }
        TreeNode *root = new TreeNode(preSearch[preLeft]);
        if (preLeft + 1 == preRight) { return root; }

        // find root index in midSearch
        int midRootIndex = midLeft;
        while (midSearch[midRootIndex] != root->value) {
            midRootIndex++;
        }

        root->left = CreateTree(preSearch, midSearch, preLeft + 1, midRootIndex - midLeft + preLeft, midLeft,
                                midRootIndex - 1);
        root->right = CreateTree(preSearch, midSearch, midRootIndex - midLeft + preLeft + 1, preRight, midRootIndex + 1,
                                 midRight);
        return root;
    }

    void printTree(TreeNode *root) {
        if (root == nullptr) return;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            // for every layer
            while (size--) {
                TreeNode *tempNode = q.front();
                q.pop();
                // if node is nullptr, still push null point to queue
                if (tempNode == nullptr) {
                    cout << "* ";
                } else {
                    q.push(tempNode->left);
                    q.push(tempNode->right);
                    cout << tempNode->value << " ";
                }
            }
            cout << endl;
        }
    }
};

void testTreeCase1() {
    vector<int> preSearch{1, 2, 3};
    vector<int> inSearch{2, 1, 3};
    TreeInstance treeInstance;
    auto root = treeInstance.CreateTree(preSearch, inSearch, 0, preSearch.size() - 1, 0, inSearch.size() - 1);
    treeInstance.printTree(root);
}

void testTreeCase2() {
    vector<int> preSearch{1, 2, 3, 4};
    vector<int> inSearch{3, 2, 4, 1};
    TreeInstance treeInstance;
    auto root = treeInstance.CreateTree(preSearch, inSearch, 0, preSearch.size() - 1, 0, inSearch.size() - 1);
    treeInstance.printTree(root);
}

int main() {
    testTreeCase1();
    testTreeCase2();
    return 0;

}



#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template<class T>
class TreeInLinkedList {
    private:
        class TreeNode {
            public:
                TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
                TreeNode *parent;
                T data;
        };
        vector<TreeNode *> *nodeList;
        void displayPreorder(TreeNode *node) {
            cout << node->data << " ";
            // 前序遍歷：先顯示父節點，再遞迴顯示子節點
            for (auto child : *nodeList) {
                if (child->parent == node) {
                    displayPreorder(child); 
                }
            }
        }
        void displayPostorder(TreeNode *node) {
            // 後序遍歷：先遞迴顯示子節點，再顯示父節點
            for (auto child : *nodeList) {
                if (child->parent == node) {
                    displayPostorder(child);
                }
            }
            cout << node->data << " ";
         }
    public:
        TreeInLinkedList() {
            nodeList = new vector<TreeNode *>();
        }
        void addElement(T data) {
            int j, k = nodeList->size();
            if(data == 1) {
                nodeList->clear();
                nodeList = new vector<TreeNode *>();
                TreeNode *newNode = new TreeNode(data, nullptr);
                nodeList->push_back(newNode);
            }
            else {
                for(j = 0;j < k;j ++) {
                    if(data % (*nodeList)[j]->data == 0) {
                        TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
                        nodeList->push_back(newNode);
                    }
                }
            }
    }
    void displayPreorder() {
        if (!nodeList->empty()) {
            displayPreorder((*nodeList)[0]);  // 從根節點開始前序遍歷
        }
    }
    void displayPostorder() {
        if (!nodeList->empty()) {
            displayPostorder((*nodeList)[0]);  // 從根節點開始後序遍歷
        }
    }
};

int main()
{
  TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
  int j;
  int n;
  cin >> n;
  for(j = 1;j <= n;j ++)
    tree->addElement(j);
  tree->displayPreorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
}

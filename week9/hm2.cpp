#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template<class T>
class BinaryThreadedTreeNode {
public:
    BinaryThreadedTreeNode(T d) : right(nullptr), left(nullptr), isThread(false) {
        data = new T {d};
    }
    BinaryThreadedTreeNode() : data(nullptr), right(nullptr), left(nullptr), isThread(false) {}
    T *data;
    BinaryThreadedTreeNode *left, *right;
    bool isThread;
};

template<class T>
class BinarySearchThreadedTree : BinaryThreadedTreeNode<T> {
private:
    BinaryThreadedTreeNode<T> *root;
    BinaryThreadedTreeNode<T> *CreateThread(BinaryThreadedTreeNode<T> *root) {
        //樹為空
        if(!root){
            return NULL;
        }
        //左右子樹為空
        if(root->left == NULL && root->right == NULL){
            return root;
        }
        //遞迴找到左子樹的最右子樹
        if (root->left){
            BinaryThreadedTreeNode<T> *temp = CreateThread(root->left);
            temp->right = root;
            temp->isThread = true;
        }
        //沒有右子樹，返回自己(即為最右子樹)
        if(!root->right){
            return root;
        }
        //若還有右子樹返回右子樹
        return CreateThread(root->right);
    }
public:
    BinarySearchThreadedTree() : BinaryThreadedTreeNode<T>() {
        root = NULL;
    }
    // 插入節點 (保持原有結構)
    BinarySearchThreadedTree<T> *insert(T d) {
        if (!root) {
            root = new BinaryThreadedTreeNode<T>(d);
            return this;
        }
        BinaryThreadedTreeNode<T> *current = root;
        while (true) {
            if (d < *(current->data)) {
                if (!current->left) {
                    current->left = new BinaryThreadedTreeNode<T>(d);
                    return this;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new BinaryThreadedTreeNode<T>(d);
                    return this;
                }
                current = current->right;
            }
        }
    }
    void createthread(){
        CreateThread(root);
    }
     // 中序遍歷並輸出
    void print() {
        BinaryThreadedTreeNode<T> *current = root;

        // 找到最左節點
        while (current && current->left) {
            current = current->left;
        }

        // 開始遍歷
        while (current) {
            cout << *current->data << " ";
            if (current->isThread) {
                current = current->right; // 移動到後繼
            } else {
                // 找到右子樹中最左節點
                current = current->right;
                while (current && current->left) {
                    current = current->left;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int j;
    BinarySearchThreadedTree<int> bstt;
    srand(time(nullptr));
    for(j = 0;j < 10;j ++)
        bstt.insert(rand() % 100);
    bstt.createthread();
    bstt.print();
}

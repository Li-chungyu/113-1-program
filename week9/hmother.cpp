#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// 節點類別模板
template<class T>
class BinarySearchThreadedTree; // 預先宣告模板類別

// 節點類別模板
template<class T>
class BinaryThreadedTreeNode {
private:
    T *data;
    BinaryThreadedTreeNode *left, *right;
    bool isThread; // 標記右指標是否為線索

    friend class BinarySearchThreadedTree<T>;

public:
    BinaryThreadedTreeNode(T d) : data(new T(d)), left(nullptr), right(nullptr), isThread(false) {}
    BinaryThreadedTreeNode() : data(nullptr), left(nullptr), right(nullptr), isThread(false) {}

    ~BinaryThreadedTreeNode() {
        delete data;
    }
};

// 二元搜尋線索樹類別模板
template<class T>
class BinarySearchThreadedTree {
private:
    BinaryThreadedTreeNode<T> *root;

    // 輔助函數：建立線索
    void CreateThread(BinaryThreadedTreeNode<T> *node, BinaryThreadedTreeNode<T> *&prev) {
        if (!node || !node->data) return;

        // 遞迴處理左子樹
        CreateThread(node->left, prev);

        // 建立線索
        if (prev && !prev->right) {
            prev->right = node;
            prev->isThread = true;
        }

        prev = node; // 更新上一個節點

        // 遞迴處理右子樹
        if (!node->isThread) {
            CreateThread(node->right, prev);
        }
    }

    // 輔助函數：釋放節點記憶體
    void Clear(BinaryThreadedTreeNode<T> *node) {
        if (!node || !node->data) return;

        if (!node->isThread) {
            Clear(node->right);
        }

        Clear(node->left);
        delete node;
    }

public:
    BinarySearchThreadedTree() : root(nullptr) {}

    ~BinarySearchThreadedTree() {
        Clear(root);
    }

    // 插入節點
    BinaryThreadedTreeNode<T> *insert(T d) {
        if (!root) {
            root = new BinaryThreadedTreeNode<T>(d);
            return root;
        }

        BinaryThreadedTreeNode<T> *current = root;
        while (true) {
            if (d < *(current->data)) {
                if (!current->left) {
                    current->left = new BinaryThreadedTreeNode<T>(d);
                    return current->left;
                }
                current = current->left;
            } else {
                if (!current->right || current->isThread) {
                    auto *newNode = new BinaryThreadedTreeNode<T>(d);
                    newNode->right = current->right;
                    newNode->isThread = current->isThread;
                    current->right = newNode;
                    current->isThread = false;
                    return newNode;
                }
                current = current->right;
            }
        }
    }

    // 建立線索
    void createThread() {
        BinaryThreadedTreeNode<T> *prev = nullptr;
        CreateThread(root, prev);
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
    BinarySearchThreadedTree<int> bstt;

    srand(static_cast<unsigned>(time(nullptr)));
    for (int j = 0; j < 10; j++) {
        bstt.insert(rand() % 100);
    }

    // 建立線索
    bstt.createThread();

    // 中序輸出
    bstt.print();

    return 0;
}
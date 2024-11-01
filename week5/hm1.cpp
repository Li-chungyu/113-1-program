#include <iostream>
#include <cmath>
#include<queue>

using namespace std;

template<class T>
class BinaryTreeInArray {
    private:
        T *array;
        int height;
        int numOfElement;
        void resize(int size) {
            T *temp = new T[numOfElement];
            int j;
            for(j = 0;j < numOfElement;j ++)
            temp[j] = array[j];
            delete array;
            array = new T[static_cast<int>(pow(2, height + 1)) - 1];
            for(j = 0;j < numOfElement;j ++)
            array[j] = temp[j];
            height ++;
            delete temp;
        }
        void InorderTraversal(int index){
            if(index >= numOfElement) return;
            InorderTraversal(index*2+1);
            cout << array[index] << " ";
            InorderTraversal(index*2+2);
        }
        void PreorderTraversal(int index){
            if(index >= numOfElement) return;
            cout << array[index] << " ";
            PreorderTraversal(index*2+1);
            PreorderTraversal(index*2+2);
        }
        void PostorderTraversal(int index){
            if(index >= numOfElement) return;
            PostorderTraversal(index*2+1);
            PostorderTraversal(index*2+2);
            cout << array[index] << " ";
        }
    public:
        BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}
        void addElementAsCompleteTree(T data) {
            int cap = pow(2, height) - 1;
            if(numOfElement + 1 > cap)
            resize((cap + 1) * 2 - 1);
            array[numOfElement] = data;
            numOfElement ++;
        }
        void displayInorder() {
            InorderTraversal(0);
        }
        void displayPreorder() {
            PreorderTraversal(0);
        }
        void displayPostorder() {
            PostorderTraversal(0);
        }
};

template<class T>
class BinaryTreeInLinkedList {
    private:
        class TreeNode {
            public:
                TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
                TreeNode *left, *right;
                T data;
        };
        TreeNode *root;
        int numOfElement;
        void InorderTraversal(TreeNode *n){
            if(!n) return;
            InorderTraversal(n->left);
            cout << n->data << " ";
            InorderTraversal(n->right);
        }
        void PreorderTraversal(TreeNode *n){
            if(!n) return;
            cout << n->data << " ";
            PreorderTraversal(n->left);
            PreorderTraversal(n->right);
        }
        void PostorderTraversal(TreeNode *n){
            if(!n) return;
            PostorderTraversal(n->left);
            PostorderTraversal(n->right);
            cout << n->data << " ";
        }
    public:
        BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}
        void addElementAsCompleteTree(T data) {
            TreeNode *newNode = new TreeNode(data);
            if(!root){
                root = newNode;
            }else{
                queue<TreeNode *> q;
                q.push(root);
                while(!q.empty()){
                    TreeNode *cur = q.front();
                    q.pop();
                    if(!cur->left){
                        cur->left = newNode;
                        break;
                    }else{
                        q.push(cur->left);
                    }
                    if(!cur->right){
                        cur->right = newNode;
                        break;
                    }else{
                        q.push(cur->right);
                    }
                }
            }
            numOfElement++;
        }
        void displayInorder() {
            InorderTraversal(root);
        }
        void displayPreorder() {
            PreorderTraversal(root);
        }
        void displayPostorder() {
            PostorderTraversal(root);
        }
};

int main()
{
    BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
    BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
    int j, n;
    cin >> n;
    for(j = 0;j < n;j ++) {
        b->addElementAsCompleteTree(j);
        tree->addElementAsCompleteTree(j);
    }
    b->displayInorder();
    cout << endl;
    tree->displayInorder();
    cout << endl;
    b->displayPreorder();
    cout << endl;
    tree->displayPreorder();
    cout << endl;
    b->displayPostorder();
    cout << endl;
    tree->displayPostorder();
    cout << endl;
    return 0;
}

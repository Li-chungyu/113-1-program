#include <iostream>
#include <string>

using namespace std;

template<class T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node *left, *right;
        Node() : left(NULL),right(NULL){}
    };
    void inorder(Node *cur) {
        if(!cur)
        return;
        inorder(cur->left);
        cout << cur->data << " ";
        inorder(cur->right);
    }
    Node *root;
    int calculateHeight(Node *cur){
        if(cur == NULL){
            return 0;
        }
        int leftHeight = calculateHeight(cur->left);
        int rightHeight = calculateHeight(cur->right);
        return 1 + max(leftHeight,rightHeight);
    }
public:
    BinarySearchTree() : root(nullptr) {}
    void insertElement(T d) {
        Node *newNode = new Node;           //創造新node
        newNode->data = d;
        newNode->left = NULL;
        newNode->right = NULL;
        
        if(root == NULL){                   //空樹
            root = newNode;                 
        }else{                              
            Node *cur = root;
            Node *parent;                   //紀錄最後節點
            while(cur != NULL){
                parent = cur;
                if(cur->data > d){
                    cur = cur->left;
                }else{
                    cur = cur->right;
                }
            }
            if(parent->data > d){
                parent->left = newNode;
            }else{
                parent->right = newNode;
            }
        }
    }
    void print() {
        inorder(root);
        cout << endl;
    }
    bool search(T d) {
        Node *cur = root;
        while(cur != NULL){
            if(cur->data == d){
                return true;
            }else if(cur->data > d){
                cur = cur->left;
            }else{
                cur = cur->right;
            }
        }
        return false;
    }
    int height() {
        return calculateHeight(root);
    }
};

int main() {
    int data;
    string command;
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    while(true) {
        cin >> command;
        if(command == "insert") {
        cin >> data;
        bst->insertElement(data);
        }
        else if(command == "search") {
        cin >> data;
        if(bst->search(data))
            cout << "true" << endl;
        else
            cout << "false" << endl;
        }
        else if(command == "height") {
        cout << bst->height() << endl;
        }
        else if(command == "print") {
        bst->print();
        }
        else if(command == "exit") {
        break;
        }
    }
}

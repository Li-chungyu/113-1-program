#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <ctime>

using namespace std;

template<class T>
class Node {
public:
	Node() {
		data = new T;
	}
	Node(T d) {
		data = new T;
		(*data) = d;
	}
	Node& operator=(T d) {
		(*data) = d;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Node n) {
		out << *(n.data);
		return out;
	}
	friend ostream& operator<<(ostream& out, Node* n) {
		out << *(n->data);
		return out;
	}
	void setData(T d) {
		*data = d;
	}
	T& getData() const {
		return *data;
	}
protected:
	T* data;
};

template<class T>
class BinaryTreeNode : public Node<T> {
public:
	BinaryTreeNode() : Node<T>() {
		left = NULL;
		right = NULL;
		height = 1;
	}
	BinaryTreeNode(T d) : Node<T>(d) {
		left = NULL;
		right = NULL;
		height = 1;
	}
	BinaryTreeNode(BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) : Node<T>() {
		left = l;
		right = r;
		height = 1;
	}
	BinaryTreeNode(T d, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) : Node<T>(d) {
		left = l;
		right = r;
		height = 1;
	}
	void setLeft(BinaryTreeNode<T>* l) {
		left = l;
	}
	void setRight(BinaryTreeNode<T>* r) {
		right = r;
	}
	BinaryTreeNode<T>*& getLeft() {
		return left;
	}
	BinaryTreeNode<T>*& getRight() {
		return right;
	}
	int getHeight() {
		return height;
	}
	void setHeight(int h) {
		height = h;
	}
private:
	BinaryTreeNode<T>* left, * right;
	int height;
};

template<class T>
class AVLTree {
private:
	BinaryTreeNode<T>* root;

	int getHeight(BinaryTreeNode<T>* node) {
		return node ? node->getHeight() : 0;
	}

	int getBalanceFactor(BinaryTreeNode<T>* node) {
		if (!node) return 0;
		return getHeight(node->getLeft()) - getHeight(node->getRight());
	}

	BinaryTreeNode<T>* rotateRight(BinaryTreeNode<T>* y) {
		BinaryTreeNode<T>* x = y->getLeft();
		BinaryTreeNode<T>* T2 = x->getRight();

		x->setRight(y);
		y->setLeft(T2);

		y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);
		x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);
											
		return x;
	}

	BinaryTreeNode<T>* rotateLeft(BinaryTreeNode<T>* x) {
		BinaryTreeNode<T>* y = x->getRight();
		BinaryTreeNode<T>* T2 = y->getLeft();

		y->setLeft(x);
		x->setRight(T2);

		x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);
		y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);

		return y;
	}																																																

	BinaryTreeNode<T>* insertNode(BinaryTreeNode<T>* node, T d) {
		if (!node)
			return new BinaryTreeNode<T>(d);

		if (d < node->getData())
			node->setLeft(insertNode(node->getLeft(), d));
		else if (d > node->getData())
			node->setRight(insertNode(node->getRight(), d));
		else
			return node;

		node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight())));

		int balance = getBalanceFactor(node);

		// Left Left Case
		if (balance > 1 && d < node->getLeft()->getData())
			return rotateRight(node);

		// Right Right Case
		if (balance < -1 && d > node->getRight()->getData())
			return rotateLeft(node);

		// Left Right Case
		if (balance > 1 && d > node->getLeft()->getData()) {
			node->setLeft(rotateLeft(node->getLeft()));
			return rotateRight(node);
		}

		// Right Left Case
		if (balance < -1 && d < node->getRight()->getData()) {
			node->setRight(rotateRight(node->getRight()));
			return rotateLeft(node);
		}

		return node;
	}

	void inorder(BinaryTreeNode<T>* cur, int n) {
		if (cur == NULL)
			return;
		inorder(cur->getRight(), n + 1);
		for (int j = 0; j < n; j++)
			cout << "  ";
		cout << cur->getData() << endl;
		inorder(cur->getLeft(), n + 1);
	}

public:
	AVLTree() : root(NULL) {}

	void insert(T d) {
		root = insertNode(root, d);
	}

	void inorder() {
		inorder(root, 0);
	}
};

int main() {
	AVLTree<int> tree;
	srand(time(NULL));
	for (int j = 0; j < 20; j++) {
		int num = rand() % 100;
		cout << "Inserting: " << num << endl;
		tree.insert(num);
		tree.inorder();
		cout << "--------------" << endl;
	}
	return 0;
}

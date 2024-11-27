#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;
// 我決定用 unordered_map 和 list 來分別保存node children和 insertion order
/* 
Trie, also known as "Prefix Tree" or "自點數", the keys of it are often string.
Unlike binary tree, the key of Trie isn't stored in node. 
Instead, a node's position in the trie defines the key with which it is associated.
Application : text prediction 
 */
using namespace std;

class Trie
{
	struct Node
	{
		Node() : isTerminal(nullptr) {}
		vector<char> childrenOrder;  // 儲存每個字元insert的先後順序，彌補array或unordered_map沒辦法保存插入先後順序的缺點。
		unordered_map<char, Node*> children;  // 代替wiki中的array，儲存每個對應的字元和節點。可以用比較少空間。
		bool isTerminal; // 如果一個節點是一個字串的結束，則為true。
	};
	Node *root;
public:
	/*
	construct a Trie.
	*/
	Trie()
	{
		root = new Node;
	}
	/*
	search trie for key, return true if exist, false if not.
	*/
	bool search(string key)
	{
		Node *c = root;
		// 遍歷輸入的字串
		for(int i=0; i<key.length(); i++)
		{
			// find(k)會回傳k對應的pair的iterator，如果unordered_map沒有該pair，則回傳end()。
			// 如果字典樹找不到該字元
			if( c->children.find(key[i]) == c->children.end() )
			{			
					return false;
			}
			c = c->children[key[i]];
		}
		// 就算字典樹中已經有對應的字元排列，還是必須判斷是否有key字串存在於樹中。
		if(c->isTerminal)
			return true;
		else 
			return false;
	}
	/*
	insert value into trie.
	*/
	void insert(string value)
	{
		Node *c = root; // current node
		for(int i=0; i<value.length(); i++)
		{
			if( c->children.find(value[i]) == c->children.end() )
			{
				c->children[value[i]] = new Node;
				c->childrenOrder.push_back(value[i]);
			}
			c = c->children[value[i]];
		}
		c->isTerminal = true;
	}
	/*
	display trie in pre-order, each element in a line, 
	display space before element base on the level of the element. 
	level 1 for 2 space, level 2 for 4 space, level 3 for 6 space and so on, root is level 	0.
	*/
	/* 
	印在同一行(inline printing)的規則:
		1. 當節點只有一個子節點，而且這個子節點 isTerminal == false
		2. 當節點 isTerminal == true 或 不再只有一個子節點時，停止 inline printing.
	 */
	void preorderPrint_R(Node *c, int level)
    {
        if (!c)
            return; // Base case: null node

        // Traverse children in insertion order
        for (const auto ch : c->childrenOrder)
        {
            Node *child = c->children[ch];

            // Print leading spaces for this level
            for (int i = 0; i < (level + 1) * 2; i++)
                cout << " ";

            // Print the current character
            cout << ch;

            // Traverse inline as long as the child has exactly one child and is not terminal
            Node *temp = child;
            while (temp->childrenOrder.size() == 1 && !temp->isTerminal)
            {
                char nextChar = temp->childrenOrder[0];
                cout << nextChar; // Print inline
                temp = temp->children[nextChar];
            }

            // End the line when inline traversal is done
            cout << endl;

            // Recursive call for the last node processed in inline traversal
            preorderPrint_R(temp, level + 1);
        }
    }

	void preorder()
	{
		cout << "[]" << endl;
		preorderPrint_R(root, 0);
	}
};

int main()
{
	Trie *trie = new Trie();
	string command, key, value;
	while(1)
	{
		cin>>command;
		if(command == "insert")
		{
			cin>>value;
			trie->insert(value);
		}
		else if(command == "search")
		{
			cin>>key;
			if(trie->search(key))
				cout << "exist" << endl;
			else
				cout << "not exist" << endl;
		}
		else if(command == "print")
		{
			trie->preorder();
		}
		else if(command == "exit")
		{
			break;
		}
	}
}

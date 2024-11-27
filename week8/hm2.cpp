#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Trie
{
	private:
		struct Node{
			unordered_map<char,Node *> Children;
			vector<char> ChildrenOrder;
			bool IsEndOfWord;
			Node() : IsEndOfWord(false) {}
		};
		Node *root;
	public:
		Trie(){
			root = new Node;
		}

		bool search(string key){
			Node *c = root;
			for(int i=0;i<key.length();i++){
				if(c->Children.find(key[i]) == c->Children.end()){
					return false;
				}else{
					c = c->Children[key[i]];
				}
			}
			if(c->IsEndOfWord == true){
				return true;
			}else{
				return false;
			}
		}

		void insert(string value){
			Node *c = root;
			for(int i=0;i<value.length();i++){
				if(c->Children.find(value[i]) == c->Children.end()){
					c->Children[value[i]] = new Node;
					c->ChildrenOrder.push_back(value[i]);
				}
				c = c->Children[value[i]];
				
			}
			c->IsEndOfWord = true;
		}

		void preorder_Print(Node *c, int level){
			if(!c){
				return;
			}
			for(auto ch : c->ChildrenOrder){
				Node *child = c->Children[ch];
				for(int i=0;i<(level+1)*2;i++){
					cout << " ";
				}
				cout << ch;
				while(child->ChildrenOrder.size() == 1 && child->IsEndOfWord == false){
					char nextChar = child->ChildrenOrder[0];
					cout << nextChar;
					child = child->Children[nextChar];
				}
				cout << endl;
				preorder_Print(child,level+1);
			}

		}
		
		void preorder(){
			cout << "[]" << endl;
			preorder_Print(root,0);
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

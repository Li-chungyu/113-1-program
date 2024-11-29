#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class SuffixTreeNode {
  public:
    unordered_map<char,SuffixTreeNode *> Child;
    vector<int> Index;
    void insertSuffix(const string &suffix,int index){
      SuffixTreeNode *cur = this;
      for(char c : suffix){
        if(cur->Child.find(c) == cur->Child.end()){
          cur->Child[c] = new SuffixTreeNode;
        }
        cur = cur->Child[c];
        cur->Index.push_back(index);
      }
    }
};

class SuffixTree {
private:
    SuffixTreeNode *root;
    string text;
    void deleteTree(SuffixTreeNode *node){
        for(auto child : node->Child){
            delete child.second;
        }
        delete node;
    }
public:
    SuffixTree(const string &text) : text(text) {
      root = new SuffixTreeNode;
      for(int i=0;i<text.length();i++){
        root->insertSuffix(text.substr(i),i);
      }
    }

    bool exist(const string &substring) {
        SuffixTreeNode *cur = root;
        for(char c : substring){
          if(cur->Child.find(c) == cur->Child.end()){
            return false;
          }
          cur = cur->Child[c];
        }
        return true;
    }

    int count(const string &substring) {
        SuffixTreeNode *cur = root;
        for(char c : substring){
          if(cur->Child.find(c) == cur->Child.end()){
            return 0;
          }
          cur = cur->Child[c];
        }
        return cur->Index.size();
    }

    ~SuffixTree() {
        deleteTree(root);
    }
};

int main() {
    std::string text = "";
    while(true) {
      std::string temp;
      getline(std::cin, temp);
      if(temp == "")
        break;
      text += temp;
    }
    SuffixTree tree(text);

    std::string query;
    while(true) {
      getline(std::cin, query);
      if(query == "")
        break;
      std::cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << std::endl;
      std::cout << "Count of '" << query << "': " << tree.count(query) << std::endl;
    }
    return 0;
}

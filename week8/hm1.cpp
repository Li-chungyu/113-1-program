#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

//design your won SuffixTreeNode using in SuffixTree
class SuffixTreeNode {
  
};

class SuffixTree {
private:
    SuffixTreeNode *root;
    string text;
public:
    SuffixTree(const string &text) : text(text) {
        
    }

    bool exist(const string &substring) {

    }

    int count(const string &substring) {

    }

    ~SuffixTree() {

    }
};

int main() {
    string text = "";
    while(true) {
      string temp;
      getline(std::cin, temp);
      if(temp == "")
        break;
      text += temp;
    }
    SuffixTree tree(text);

    string query;
    while(true) {
      getline(std::cin, query);
      if(query == "")
        break;
      cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << std::endl;
      cout << "Count of '" << query << "': " << tree.count(query) << std::endl;
    }
    return 0;
}

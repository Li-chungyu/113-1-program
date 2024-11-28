#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class SuffixTreeNode {
  public:
    unordered_map<char,SuffixTreeNode *> Child;
    vector<int> index;
};

class SuffixTree {
private:
    SuffixTreeNode *root;
    std::string text;
public:
    SuffixTree(const std::string &text) : text(text) {
    }

    bool exist(const std::string &substring) {
    }

    int count(const std::string &substring) {
    }

    ~SuffixTree() {
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

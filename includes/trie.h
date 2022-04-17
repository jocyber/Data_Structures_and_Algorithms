#ifndef TRIE
#define TRIE

#include <array>
#include <string>
#include <stack>

class Trie {
	struct Node {
		char val;
		std::array<Node*, 26> nodeList;

		Node(char val_) : val(val_) {
			std::fill(nodeList.begin(), nodeList.end(), nullptr);
		}
	};

	Node *root = new Node('\0');
	//only for checking each consecutive level
	//must be reset when completely used
	Node *lcurr = root;
	Node *prev = root;

private:
	void deleteTrie(Node* root);
	bool removeWord(const std::string &word, unsigned int n, Node *root);

public:
	Trie() = default;
	~Trie();

	void addWord(const std::string &word);
	void fillWord(std::string &word);
	bool isWordPresent(const std::string &word);//full word
	void removeWord(const std::string &word);
};

#endif

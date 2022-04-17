#include "../includes/trie.h"
#include <iostream>

void Trie::addWord(const std::string &word) {
    Node *curr = root;

    for(const char &x : word) {
        Node *temp = curr->nodeList[x % 65];

        if(!temp) {
            Node *newnode = new Node(x);
            curr->nodeList[x % 65] = newnode;
            curr = newnode;
        }
        else {
            curr = temp;
        }
    }
}

//for autocompletion
void Trie::fillWord(std::string &word) {
    Node *curr = root;

    for(const char &x : word) {
        Node *temp = curr->nodeList[x % 65];

        if(!temp) return;
        curr = temp;
    }

    while(curr) {
        unsigned int count = 0;
        Node *nextnode = nullptr;

        for(Node* x : curr->nodeList) {
            if(x) {
                if(count == 1) // more than 1 path to take
                    return;

                ++count;
                nextnode = x;
            }
        }

        curr = nextnode;
        if(curr) {word += curr->val;}
    }
}

//destructor - postorder deletion
Trie::~Trie() {
    deleteTrie(root);

    root = new Node('\0');
}

void Trie::deleteTrie(Node *root) {
    if(root) {
        for(Node* x : root->nodeList) {
            deleteTrie(x);       
        }

        delete root;
    }
}

bool Trie::isWordPresent(const std::string &word) {
    Node *curr = root;

    for(const char &x : word) {
        Node *temp = curr->nodeList[x % 65];

        if(temp) {
            curr = temp;
        }
        else {
            return false;
        }
    }

    return true;
}

void Trie::removeWord(const std::string &word) {
    Node *curr = root->nodeList[word[0] % 65];
    removeWord(word, 0, curr);
}

bool Trie::removeWord(const std::string &word, unsigned int n, Node *root) {
    if(n == word.length()) {
        return true;
    }

    Node *temp = root->nodeList[word[n] % 65];
    bool shouldDelete = true;

    if(temp)
        shouldDelete = removeWord(word, n + 1, temp);

    //returning time
    if(!shouldDelete)
        return false;

    if(root) {
        for(const Node* x : root->nodeList)
            if(x) {return false;}

        delete root; return true;
    }

    return false;
}

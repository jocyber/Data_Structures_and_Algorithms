#include "../includes/trie.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>

std::unordered_set<std::string> words = {
    "SEEK","FIND","RANDOM","SLEUTH","BACKWARD","VERTICAL","DIAGONAL","WIKIPEDIA","HORIZONTAL","WORDSEARCH"
};

void printBoard(const std::vector<std::vector<char>> &board);

void searchWord(const std::vector<std::vector<char>> &board, Trie &trie, unsigned int i, unsigned int j, int hor_dir = 0, int vert_dir = 0, std::string word = "") {
    std::string uWord = word + board[i][j];

    if(words.find(uWord) != words.end())
        std::cout << "Found: " << uWord << '\n';
    else if(trie.isWordPresent(word)) {
        if(hor_dir == 0 && vert_dir == 0) { //check all directions
            if(i > 0 && j > 0)//upper left corner
                searchWord(board, trie, i - 1, j - 1, -1, -1,uWord);

            if(i > 0 && j < board[i].size() - 1) //top right corner
                searchWord(board, trie, i - 1, j + 1, 1, -1,uWord);

            if(i < board.size() - 1 && j < board[i].size() - 1) //bottom right corner
                searchWord(board, trie, i + 1, j + 1, 1, 1,uWord);

            if(i < board.size() - 1 && j > 0) //bottom left corner
                searchWord(board, trie, i + 1, j - 1, -1, 1,uWord);

            if(j > 0) //check left
                searchWord(board, trie, i, j - 1, -1, 0,uWord);

            if(i > 0) //top
                searchWord(board, trie, i - 1, j, 0, -1,uWord);

            if(j < board[i].size() - 1) //right 
                searchWord(board, trie, i, j + 1, 1, 0,uWord);   

            if(i < board.size() - 1) //bottom
                searchWord(board, trie, i + 1, j, 0, 1,uWord);
        }
        else {
            if(hor_dir == 1 && vert_dir == 1 && i < board.size() - 1 && j < board[i].size() - 1) // bottom right
                searchWord(board, trie, i + 1, j + 1, 1, 1,uWord);
            else if(hor_dir == 1 && vert_dir == 0 && j < board[i].size() - 1) // right
                searchWord(board, trie, i, j + 1, 1, 0,uWord); 
            else if(hor_dir == 0 && vert_dir == 1 && i < board.size() - 1) //bottom
                searchWord(board, trie, i + 1, j, 0, 1,uWord);
            else if(hor_dir == -1 && vert_dir == 0 && j > 0) //left
                searchWord(board, trie, i, j - 1, -1, 0,uWord);
            else if(hor_dir == 0 && vert_dir == -1 && i > 0) //top
                searchWord(board, trie, i - 1, j, 0, -1,uWord);
            else if(hor_dir == -1 && vert_dir == -1 && i > 0 && j > 0) //upper left
                searchWord(board, trie, i - 1, j - 1, -1, -1,uWord);
            else if(hor_dir == -1 && vert_dir == 1 && i < board.size() - 1 && j > 0) //bottom left
                searchWord(board, trie, i + 1, j - 1, -1, 1,uWord);
            else if(hor_dir == 1 && vert_dir == -1 && i > 0 && j < board[i].size() - 1) //upper right
                searchWord(board, trie, i - 1, j + 1, 1, -1,uWord);
        }
    }
}

int main(int argc, char* argv[]) 
{
    Trie trie;

    std::vector<std::vector<char>> board = {
        {'W','V','E','R','T','I','C','A','L','L'},
        {'R','O','O','A','F','F','L','S','A','B'},
        {'A','C','R','I','L','I','A','T','O','A'},
        {'N','D','O','D','K','O','N','W','D','C'},
        {'D','R','K','E','S','O','O','D','D','K'},
        {'O','E','E','P','Z','E','G','L','I','W'},
        {'M','S','I','I','H','O','A','E','R','A'},
        {'A','L','R','K','R','R','I','R','E','R'},
        {'K','O','D','I','D','E','D','R','C','D'},
        {'H','E','L','W','S','L','E','U','T','H'}
    };

    for(const std::string &x : words) {
        trie.addWord(x);
    }

    printBoard(board);

    for(unsigned int i = 0; i < board.size(); i++) {
        for(unsigned int j = 0; j < board[i].size(); j++) {
            searchWord(board, trie, i, j);
        }
    }

    return 0;
}

void printBoard(const std::vector<std::vector<char>> &board) {
    for(unsigned int i = 0; i < board.size(); ++i) {
        for(unsigned int j = 0; j < board[i].size(); ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


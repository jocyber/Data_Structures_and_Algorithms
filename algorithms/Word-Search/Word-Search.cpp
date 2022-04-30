#include "../../includes/trie.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>

std::unordered_set<std::string> words;
std::vector<std::vector<bool>> boardRes;

void printBoard(const std::vector<std::vector<char>> &board);
void printRes(const std::vector<std::vector<char>> &board, const std::vector<std::vector<bool>> &boardRes);

//algorithm to solve the puzzle
bool searchWord(const std::vector<std::vector<char>> &board, Trie &trie, unsigned int i, unsigned int j, int hor_dir = 0, int vert_dir = 0, std::string word = "") {
    std::string uWord = word + board[i][j];

    if(words.find(uWord) != words.end()) {
			boardRes[i][j] = true;
      return true;
		}
    else if(trie.isWordPresent(word)) {
        if(hor_dir == 0 && vert_dir == 0) { //check all directions
            if(i > 0 && j > 0) { //upper left corner
                bool found = searchWord(board, trie, i - 1, j - 1, -1, -1,uWord);
								if(found)
									boardRes[i][j] = true;
						}

            if(i > 0 && j < board[i].size() - 1) { //top right corner
	              bool found = searchWord(board, trie, i - 1, j + 1, 1, -1,uWord);
								if(found)
									boardRes[i][j] = true;
						}

            if(i < board.size() - 1 && j < board[i].size() - 1) {//bottom right corner
                bool found = searchWord(board, trie, i + 1, j + 1, 1, 1,uWord);
								if(found)	
									boardRes[i][j] = true;
						}

            if(i < board.size() - 1 && j > 0) { //bottom left corner
                bool found = searchWord(board, trie, i + 1, j - 1, -1, 1,uWord);
								if(found)
									boardRes[i][j] = true;
						}

            if(j > 0) { //check left
                bool found = searchWord(board, trie, i, j - 1, -1, 0,uWord);
								if(found)	
									boardRes[i][j] = true;
						}

            if(i > 0) { //top
                bool found = searchWord(board, trie, i - 1, j, 0, -1,uWord);
								if(found)	
									boardRes[i][j] = true;
						}

            if(j < board[i].size() - 1) { //right 
                bool found = searchWord(board, trie, i, j + 1, 1, 0,uWord);   
								if(found)
									boardRes[i][j] = true;
						}

            if(i < board.size() - 1) { //bottom
                bool found = searchWord(board, trie, i + 1, j, 0, 1,uWord);
								if(found)
									boardRes[i][j] = true;
						}
        }
        else {
						bool found = false;

            if(hor_dir == 1 && vert_dir == 1 && i < board.size() - 1 && j < board[i].size() - 1) // bottom right
                found = searchWord(board, trie, i + 1, j + 1, 1, 1,uWord);
            else if(hor_dir == 1 && vert_dir == 0 && j < board[i].size() - 1) // right
                found = searchWord(board, trie, i, j + 1, 1, 0,uWord); 
            else if(hor_dir == 0 && vert_dir == 1 && i < board.size() - 1) //bottom
                found = searchWord(board, trie, i + 1, j, 0, 1,uWord);
            else if(hor_dir == -1 && vert_dir == 0 && j > 0) //left
                found = searchWord(board, trie, i, j - 1, -1, 0,uWord);
            else if(hor_dir == 0 && vert_dir == -1 && i > 0) //top
                found = searchWord(board, trie, i - 1, j, 0, -1,uWord);
            else if(hor_dir == -1 && vert_dir == -1 && i > 0 && j > 0) //upper left
                found = searchWord(board, trie, i - 1, j - 1, -1, -1,uWord);
            else if(hor_dir == -1 && vert_dir == 1 && i < board.size() - 1 && j > 0) //bottom left
                found = searchWord(board, trie, i + 1, j - 1, -1, 1,uWord);
            else if(hor_dir == 1 && vert_dir == -1 && i > 0 && j < board[i].size() - 1) //upper right
                found = searchWord(board, trie, i - 1, j + 1, 1, -1,uWord);

						if(found) {	
							boardRes[i][j] = true;
							return true;
						}
        }
    }

		return false;
}

int main(int argc, char* argv[]) 
{
    Trie trie;
		std::fstream file("words.txt", std::ios::in);

		//insert words into trie and set
		if(file.is_open()) {
			std::string word;

			while(file >> word) {
				transform(word.begin(), word.end(), word.begin(), ::toupper);

				words.insert(word);
				trie.addWord(word);
			}

			file.close();
		}

		std::fstream puz_file("puzzle.txt", std::ios::in);
    std::vector<std::vector<char>> board;

		std::string row;

		//fill game board
		while(std::getline(puz_file, row)) {
			std::vector<char> puzzle_row;
			std::vector<bool> res_row;
			
			for(unsigned int i = 0; i < row.length(); i+=2) {
				puzzle_row.push_back(std::toupper(row[i]));
				res_row.push_back(false);
			}
		
			board.push_back(puzzle_row);
			boardRes.push_back(res_row);
		}

		puz_file.close();
    printBoard(board);

		std::cout << '\n';
		std::cout << "Press ENTER to start the game> ";
		std::cin.get();
		std::cout << '\n';

    for(unsigned int i = 0; i < board.size(); i++) {
        for(unsigned int j = 0; j < board[i].size(); j++) {
            searchWord(board, trie, i, j);
        }
    }

		std::cout << '\n';
		printRes(board, boardRes);

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

void printRes(const std::vector<std::vector<char>> &board, const std::vector<std::vector<bool>> &boardRes) {
    for(unsigned int i = 0; i < board.size(); ++i) {
        for(unsigned int j = 0; j < board[i].size(); ++j) {
						if(boardRes[i][j])
            	std::cout << "\033[1;31m" << board[i][j] << "\033[0m ";
						else
							std::cout << board[i][j] << ' ';
        }
        std::cout << '\n';
    }
}



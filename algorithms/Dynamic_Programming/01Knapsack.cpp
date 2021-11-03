#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

void Knapsack(vector<vector<int>> &table, const vector<int> &s, const vector<int> &vals, vector<vector<std::pair<int,int>>> &prev) 
{
    for(int i = 1; i < table.size(); i++) {
        for(int j = 1; j < table[i].size(); j++) {

            int decr_knapsack = j - s[i - 1];
            int second = table[i - 1][j];

            if(decr_knapsack >= 0) {
                int first = vals[i - 1] + table[i - 1][decr_knapsack];

                if(first >= second) {
                    table[i][j] = first;
                    prev[i][j] = std::make_pair(i - 1, decr_knapsack);
                }
                else {
                    table[i][j] = second;
                    prev[i][j] = std::make_pair(i - 1, j);
                }
            }
            else {
                table[i][j] = second;
                prev[i][j] = std::make_pair(i - 1, j);
            }
        }
    }
}

int main()
{
    int B = 10;
    int n = 4;

    vector<int> s = {2, 3, 5, 3};
    vector<int> vals = {10, 40, 40, 50};

    vector<vector<int>> table(n + 1, vector<int> (B+1, 0));
    vector<vector<std::pair<int,int>>> prev(n + 1, vector<std::pair<int,int>> (B+1, std::make_pair(0,0)));

    Knapsack(table, s, vals, prev);

    //print knapsack table
    for(int i = 0; i < table.size(); i++) {
        for(int j = 0; j < table[i].size(); j++) {
            std::cout << table[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << std::endl;

    for(int i = 0; i < prev.size(); i++) {
        for(int j = 0; j < prev[i].size(); j++) {
            std::cout << '(' << prev[i][j].first << ", " << prev[i][j].second << ") ";
        }
        std::cout << '\n';
    }
    

    return 0;
}
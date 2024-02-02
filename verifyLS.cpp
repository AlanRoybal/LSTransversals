#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool isLatinSquare(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        set<int> rowSet, colSet;
        for (int j = 0; j < n; ++j) {
            // Check if the value is within the valid range
            if (matrix[i][j] < 1 || matrix[i][j] > n) return false;
            // Insert the value in the row set and column set
            rowSet.insert(matrix[i][j]);
            colSet.insert(matrix[j][i]);
        }
        // Check if any number is repeated in the row or column
        if (rowSet.size() != n || colSet.size() != n) return false;
    }
    return true;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {3, 1, 2},
        {2, 3, 1}
    };
    cout << (isLatinSquare(matrix) ? "YES" : "NO") << endl;
    return 0;
}
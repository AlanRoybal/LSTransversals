#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool isSafe(int row, int col, vector<int>& rowTrack, vector<int>& colTrack, vector<int>& numTrack) {
    // Check if the cell at (row, col) can be part of the transversal
    return !rowTrack[row] && !colTrack[col] && !numTrack[col];
}

bool findTransversal(vector<vector<int>>& latinSquare, vector<int>& rowTrack, vector<int>& colTrack, vector<int>& numTrack, vector<pair<int, int>>& transversal, int n, int row) {
    if (row == n) {
        // All rows are processed, transversal is complete
        return true;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, rowTrack, colTrack, numTrack)) {
            // Choose the cell at (row, col) as part of the transversal
            rowTrack[row] = 1;
            colTrack[col] = 1;
            numTrack[latinSquare[row][col]] = 1;
            transversal.push_back({row, col});

            // Recursively try to find the rest of the transversal
            if (findTransversal(latinSquare, rowTrack, colTrack, numTrack, transversal, n, row + 1)) {
                return true;
            }

            // Backtrack if the current cell doesn't lead to a solution
            rowTrack[row] = 0;
            colTrack[col] = 0;
            numTrack[latinSquare[row][col]] = 0;
            transversal.pop_back();
        }
    }

    // No transversal found for this row
    return false;
}

int main() {
    string filename;
    cout << "Enter the filename of the Latin square: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return 1;
    }

    string line;
    vector<vector<int>> latinSquare;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> row;
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        latinSquare.push_back(row);
    }
    file.close();

    int n = latinSquare.size();
    vector<int> rowTrack(n, 0), colTrack(n, 0), numTrack(n + 1, 0);
    vector<pair<int, int>> transversal;

    if (findTransversal(latinSquare, rowTrack, colTrack, numTrack, transversal, n, 0)) {
        cout << "Transversal found: ";
        for (const auto& cell : transversal) {
            cout << "(" << cell.first + 1 << "," << cell.second + 1 << ") ";
        }
        cout << endl;
    } else {
        cout << "Transversal not found." << endl;
    }

    return 0;
}
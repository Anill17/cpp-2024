//
// Created by Anıl Sümer Topaloğlu on 13.05.2024.
//
#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(int size, int win_length) : size(size), win_length(win_length) {
    matrix = new char*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new char[size];
        fill_n(matrix[i], size, '-');
    }
}

Board::~Board() {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Board::print_board() {
    cout << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool Board::put_piece(char piece, int column) {
    if (column < 0 || column >= size) {
        return false;
    }
    for (int i = size - 1; i >= 0; --i) {
        if (matrix[i][column] == '-') {
            matrix[i][column] = piece;
            return true;
        }
    }
    return false;
}

void Board::turn_board_clockwise() {
    char** temp = new char*[size];
    for (int i = 0; i < size; ++i) {
        temp[i] = new char[size];
        for (int j = 0; j < size; ++j) {
            temp[i][j] = '-';
        }
    }

    // Rotating 90 degrees clockwise
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            temp[j][size - 1 - i] = matrix[i][j];
        }
    }

    // Applying gravity to each column
    for (int col = 0; col < size; col++) {
        int insertPos = size - 1;
        for (int row = size - 1; row >= 0; row--) {
            if (temp[row][col] != '-') {
                matrix[insertPos][col] = temp[row][col];
                insertPos--;
            }
        }
        // Fill the remaining cells in the column with '-'
        for (int fill = insertPos; fill >= 0; fill--) {
            matrix[fill][col] = '-';
        }
    }

    for (int i = 0; i < size; ++i) {
        delete[] temp[i];
    }
    delete[] temp;
}

char Board::get_game_status() {
    bool foundO = false;
    bool foundX = false;

    // Check all rows, columns, and diagonals
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Only initiate checks if there's enough space for a win
            if (j <= size - win_length) {
                // Check horizontal
                if (checkLine(i, j, 0, 1)) {
                    if (matrix[i][j] == 'O') foundO = true;
                    if (matrix[i][j] == 'X') foundX = true;
                }
            }
            if (i <= size - win_length) {
                // Check vertical
                if (checkLine(i, j, 1, 0)) {
                    if (matrix[i][j] == 'O') foundO = true;
                    if (matrix[i][j] == 'X') foundX = true;
                }
            }
            if (i <= size - win_length && j <= size - win_length) {
                // Check diagonal down-right
                if (checkLine(i, j, 1, 1)) {
                    if (matrix[i][j] == 'O') foundO = true;
                    if (matrix[i][j] == 'X') foundX = true;
                }
            }
            if (i <= size - win_length && j >= win_length - 1) {
                // Check diagonal down-left
                if (checkLine(i, j, 1, -1)) {
                    if (matrix[i][j] == 'O') foundO = true;
                    if (matrix[i][j] == 'X') foundX = true;
                }
            }
        }
    }

    if (foundO && foundX) {
        // Both players have lines long enough to win
        return 'D'; // It's a draw
    } else if (foundO) {
        return 'O'; // O wins
    } else if (foundX) {
        return 'X'; // X wins
    }

    // No winners found, check for a draw due to a full board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == '-') {
                return '-'; // Game continues
            }
        }
    }

    return 'D'; // It's a draw due to no available moves
}

bool Board::checkLine(int startRow, int startCol, int stepRow, int stepCol) {
    char player = matrix[startRow][startCol];
    for (int k = 1; k < win_length; k++) {
        if (matrix[startRow + k * stepRow][startCol + k * stepCol] != player) {
            return false;
        }
    }
    return true;
}

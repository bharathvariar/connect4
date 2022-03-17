#include <bits/stdc++.h>
using namespace std;

static int ROW_COUNT = 6, COLUMN_COUNT = 6;
bool gameOver = false;
int turn = 0;
int column;
int row;

vector<vector<int>> createBoard() {
    vector<vector<int>> board = vector<vector<int>>(ROW_COUNT, vector<int>(COLUMN_COUNT, 0));
    return board;
}

bool isValidColumn(int column) {
    if (column >= 0 and column <= 5) {
        return true;
    } else {
        return false;
    }
}

void printBoard(vector<vector<int>> board) {
    for (int row = ROW_COUNT - 1; row >= 0; row--) {
        cout << "|";
        for (int col = 0; col < COLUMN_COUNT; col++) {
            if (col != COLUMN_COUNT - 1) {
                cout << board[row][col] << " ";
            } else {
                cout << board[row][col];
            }
        }
        cout << "|" << endl;
    }
}

bool isValidLocation(vector<vector<int>> board, int column) {
    if (board[ROW_COUNT - 1][column] == 0) {
        return true;
    } else {
        return false;
    }
}

int getNextRow(vector<vector<int>> board, int column) {
    for (int row = 0; row < ROW_COUNT; row++) {
        if (board[row][column] == 0) {
            return row;
        }
    }
}

void insertPiece(vector<vector<int>> &board, int row, int column, int piece) {
    board[row][column] = piece;
    return;
}

bool isGameOver(vector<vector<int>> board, int piece) {
    // Checking Horizontal
    for (int col = 0; col < COLUMN_COUNT - 3; col++) {
        for (int row = 0; row < ROW_COUNT; row++) {
            if (board[row][col] == piece && board[row][col + 1] == piece && board[row][col + 2] == piece && board[row][col + 3] == piece) {
                return true;
            }
        }
    }
    // Checking Vertical
    for (int col = 0; col < COLUMN_COUNT; col++) {
        for (int row = 0; row < ROW_COUNT - 3; row++) {
            if (board[row][col] == piece && board[row + 1][col] == piece && board[row + 2][col] == piece && board[row + 3][col] == piece) {
                return true;
            }
        }
    }

    // Checking positively sloped diagonals
    for (int col = 0; col < COLUMN_COUNT - 3; col++) {
        for (int row = 0; row < ROW_COUNT - 3; row++) {
            if (board[row][col] == piece && board[row + 1][col + 1] == piece && board[row + 2][col + 2] == piece && board[row + 3][col + 3] == piece) {
                return true;
            }
        }
    }
    // Checking negatively sloped diagonals
    for (int col = 0; col < COLUMN_COUNT - 3; col++) {
        for (int row = 3; row < ROW_COUNT; row++) {
            if (board[row][col] == piece && board[row - 1][col + 1] == piece && board[row - 2][col + 2] == piece && board[row - 3][col + 3] == piece) {
                return true;
            }
        }
    }
    return false;
}
vector<vector<int>> board = createBoard();

int main() {
    printBoard(board);
    while (!gameOver) {
        if (turn == 0) {
            cout << "Player 1, please choose a column (1-6): ";
            cin >> column;
            column--;
            if (!isValidColumn(column)) {
                cout << "Not a valid column, choose again!" << endl;
                continue;
            }
            if (isValidLocation(board, column)) {
                int row = getNextRow(board, column);
                insertPiece(board, row, column, 1);
                if (isGameOver(board, 1)) {
                    gameOver = true;
                    cout << "Player 1 wins! Congratulations!" << endl;
                }
            } else {
                cout << "Column already full, choose again!" << endl;
                continue;
            }
        } else {
            cout << "Player 2, please choose a column (1-6): ";
            cin >> column;
            column--;
            if (!isValidColumn(column)) {
                cout << "Not a valid column, choose again!" << endl;
                continue;
            }
            if (isValidLocation(board, column)) {
                int row = getNextRow(board, column);
                insertPiece(board, row, column, 2);
                if (isGameOver(board, 2)) {
                    gameOver = true;
                    cout << "Player 2 wins! Congratulations!" << endl;
                }
            } else {
                cout << "Column already full, choose again!" << endl;
                continue;
            }
        }
        turn++;
        turn %= 2;
        printBoard(board);
    }
    return 0;
}
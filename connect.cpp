#include <Windows.h>
#include <bits/stdc++.h>
using namespace std;

static int ROW_COUNT = 6, COLUMN_COUNT = 7, PLAYER1 = 0, PLAYER2 = 1, AI = 1, PLAYER1_PIECE = 1, PLAYER2_PIECE = 2, AI_PIECE = 2, EMPTY = 0, WINDOW_LENGTH = 4;

bool gameOver = false;
int column;
int row;
int numPlayers;

vector<vector<int>> createBoard() {
    vector<vector<int>> board = vector<vector<int>>(ROW_COUNT, vector<int>(COLUMN_COUNT, 0));
    return board;
}
bool isValidColumn(int column) {
    if (column >= 0 and column <= COLUMN_COUNT - 1) {
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
int scorePosition(vector<vector<int>> board, int piece) {
    int score = 0;
    // Score Horizontal
    for (int row = 0; row < ROW_COUNT; row++) {
        vector<int> rowArray = board[row];
        for (int col = 0; col < COLUMN_COUNT - 3; col++) {
            vector<int> window;
            for (int i = col; i < WINDOW_LENGTH; i++) {
                window.push_back(rowArray[i]);
            }
            int countPiece = 0, countEmpty = 0;
            for (int i = 0; i < window.size(); i++) {
                if (window[i] == piece) {
                    countPiece++;
                } else if (window[i] == EMPTY) {
                    countEmpty++;
                }
            }
            if (countPiece == 4) {
                score += 100;
            } else if (countPiece == 3 and countEmpty == 1) {
                score += 10;
            }
        }
    }
    // Score Vertical
    for (int col = 0; col < COLUMN_COUNT; col++) {
        vector<int> colArray;
        for (int row = 0; row < ROW_COUNT; row++) {
            colArray.push_back(board[row][col]);
        }
        for (int row = 0; row < ROW_COUNT - 3; row++) {
            vector<int> window;
            for (int i = row; i < WINDOW_LENGTH; i++) {
                window.push_back(colArray[i]);
            }
            int countPiece = 0, countEmpty = 0;
            for (int i = 0; i < window.size(); i++) {
                if (window[i] == piece){
                    countPiece++;
                } else if (window[i] == EMPTY) {
                    countEmpty++;
                }
            }
            if (countPiece == 4) {
                score += 100;
            } else if (countPiece == 3 and countEmpty == 1) {
                score += 10;
            }
        }
    }
        // Score Diagonal
        return score;
}
vector<int> getValidLocations(vector<vector<int>> board) {
    vector<int> validLocations;
    for (int col = 0; col < COLUMN_COUNT; col++) {
        if (isValidLocation(board, col)) {
            validLocations.push_back(col);
        }
    }
    return validLocations;
}
int pickBestMove(vector<vector<int>> board, int piece) {
    vector<int> validLocations = getValidLocations(board);
    int bestScore = 0;
    srand(time(0));
    int index = rand() % validLocations.size();
    int bestCol = validLocations[index];
    for (int col : validLocations) {
        int row = getNextRow(board, col);
        vector<vector<int>> temp = board;
        insertPiece(temp, row, col, piece);
        int score = scorePosition(temp, piece);
        if (score > bestScore) {
            bestScore = score;
            bestCol = col;
        }
    }
    return bestCol;
}

int main() {

    cout << "Welcome! Choose your Mode of Play:\nPress 1 for 1 Player\nPress 2 for 2 Player" << endl;
    cin >> numPlayers;

    if (numPlayers == 1) {
        srand(time(0));
        int turn = rand() % 2; // Setting Random turn between 0 and 1
        printBoard(board);
        while (!gameOver) {
            if (turn == PLAYER1) {
                cout << "Player 1, please choose a column (1-7): ";
                cin >> column;
                column--;
                if (!isValidColumn(column)) {
                    cout << "Not a valid column, choose again!" << endl;
                    continue;
                }
                if (isValidLocation(board, column)) {
                    int row = getNextRow(board, column);
                    insertPiece(board, row, column, PLAYER1_PIECE);
                    if (isGameOver(board, PLAYER1_PIECE)) {
                        gameOver = true;
                        cout << "Player 1 wins! Congratulations!" << endl;
                    }
                } else {
                    cout << "Column already full, choose again!" << endl;
                    continue;
                }
            } else if (turn == AI) {

                cout << "AI Thinking..." << endl;
                Sleep(1000);
                int col = pickBestMove(board, AI_PIECE);
                if (isValidLocation(board, column)) {
                    int row = getNextRow(board, column);
                    insertPiece(board, row, column, AI_PIECE);
                    if (isGameOver(board, AI_PIECE)) {
                        gameOver = true;
                        cout << "Player 2 wins! Congratulations!" << endl;
                    }
                }
            }
            turn++;
            turn %= 2;
            printBoard(board);
        }
    } else if (numPlayers == 2) {
        int turn = 0;
        printBoard(board);
        while (!gameOver) {
            if (turn == PLAYER1) {
                cout << "Player 1, please choose a column (1-7): ";
                cin >> column;
                column--;
                if (!isValidColumn(column)) {
                    cout << "Not a valid column, choose again!" << endl;
                    continue;
                }
                if (isValidLocation(board, column)) {
                    int row = getNextRow(board, column);
                    insertPiece(board, row, column, PLAYER1_PIECE);
                    if (isGameOver(board, PLAYER1_PIECE)) {
                        gameOver = true;
                        cout << "Player 1 wins! Congratulations!" << endl;
                    }
                } else {
                    cout << "Column already full, choose again!" << endl;
                    continue;
                }
            } else if (turn == PLAYER2) {
                cout << "Player 2, please choose a column (1-7): ";
                cin >> column;
                column--;
                if (!isValidColumn(column)) {
                    cout << "Not a valid column, choose again!" << endl;
                    continue;
                }
                if (isValidLocation(board, column)) {
                    int row = getNextRow(board, column);
                    insertPiece(board, row, column, PLAYER2_PIECE);
                    if (isGameOver(board, PLAYER2_PIECE)) {
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
}
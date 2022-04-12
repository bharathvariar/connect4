#include <bits/stdc++.h>
#include <limits>
using namespace std;

static int ROW_COUNT = 6, COLUMN_COUNT = 7;
bool gameOver = false;
// int column;
// int row;
int Player = 0;
int Ai = 1;
int player_piece = 1;
int ai_piece = 2;
int window_length = 4;
int EMPTY = 0;

int turn;
int decide = rand();

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

vector<int> getValidLocations(vector<vector<int>> board) {
    vector<int> valid_locations;
    for (int i = 0; i < COLUMN_COUNT; i++) {
        if (isValidLocation(board, i))
            valid_locations.push_back(i);
    }
    return valid_locations;
}

int getNextRow(vector<vector<int>> board, int column) {
    int row = 0;
    for (row = 0; row < ROW_COUNT; row++) {
        if (board[row][column] == 0) {
            break;
        }
    }
    return row;
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

int evaluate_window(vector<int> window, int piece) {
    int score = 0;
    int opp_piece = player_piece;
    if (piece == player_piece)
        opp_piece = ai_piece;
    int countPiece = 0;
    int countEmpty = 0;
    for (int i = 0; i < window.size(); i++) {
        if (window[i] == piece)
            countPiece++;
        else if (window[i] == EMPTY)
            countEmpty++;
    }

    if (countPiece == 4)
        score += 100;
    else if (countPiece == 3 and countEmpty == 1)
        score += 5;
    else if (countPiece == 2 and countEmpty == 2)
        score += 2;

    int countOppPiece = 0;
    for (int i = 0; i < window.size(); i++) {
        if (window[i] == opp_piece)
            countOppPiece++;
    }

    if (countOppPiece == 3 and countEmpty == 1)
        score -= 4;

    cout << "score is: " << score << endl;
    return score;
}

int scorePosition(vector<vector<int>> board, int piece) {
    int score = 0;
    int center_count = 3;
    vector<int> center_array;
    for (int i = 0; i < ROW_COUNT; i++) {
        center_array[i] = board[i][COLUMN_COUNT / 2];
    }
    for (int i = 0; i < center_array.size(); i++) {
        if (center_array[i] == piece)
            center_count++;
    }
    score += center_count * 3;

    // Score horizontal
    vector<int> row_array;
    vector<int> window;
    int countPiece = 0, countEmpty = 0;
    for (int i = 0; i < ROW_COUNT; i++) {
        row_array = board[i];
        for (int c = 0; c < COLUMN_COUNT - 3; c++) {
            for (int j = 0; j < window_length; j++) {
                window.push_back(row_array[c + j]);
            }
            score += evaluate_window(window, piece);
        }
    }

    // Score Vertical
    vector<int> col_array;
    vector<int> window2;
    for (int i = 0; i < COLUMN_COUNT; i++) {
        col_array.clear(); // Initialising col_array
        for (int j = 0; j < ROW_COUNT; j++) {
            col_array.push_back(board[i][j]);
        }
        for (int r = 0; r < ROW_COUNT - 3; r++) {
            for (int j = 0; j < window_length; j++) {
                window.push_back(col_array[r + j]);
            }
            score += evaluate_window(window2, piece);
        }
    }

    // Scoring +vely sloped diagonal
    vector<int> window3;
    for (int r = 0; r < ROW_COUNT - 3; r++) {
        for (int c = 0; c < COLUMN_COUNT - 3; c++) {
            window3.clear();
            for (int i = 0; i < window_length; i++) {
                window3.push_back(board[r + i][c + i]);
            }
            score += evaluate_window(window3, piece);
        }
    }

    // Sccoring -vely sloped diagonal
    vector<int> window4;
    for (int r = 0; r < ROW_COUNT - 3; r++) {
        for (int c = 0; c < COLUMN_COUNT - 3; c++) {
            window4.clear();
            for (int i = 0; i < window_length; i++) {
                window4.push_back(board[r + 3 - i][c + i]);
            }
            score += evaluate_window(window4, piece);
        }
    }

    return score;
}

bool isTerminalNode(vector<vector<int>> board) {
    vector<int> valid_locations = getValidLocations(board);
    return isGameOver(board, Player) or isGameOver(board, Ai) or valid_locations.size() == 0;
}

vector<int> minimax(vector<vector<int>> board, int depth, int alpha, int beta, int maximizingPlayer) {
    vector<int> valid_locations = getValidLocations(board);
    bool isTerminal;
    isTerminal = isTerminalNode(board);
    if (depth == 0 or isTerminal) {
        if (isTerminal) {
            vector<int> v1;
            vector<int> v2;
            vector<int> v3;
            v1.push_back(NULL);
            v1.push_back(100000000);
            v2.push_back(NULL);
            v2.push_back(-100000000);
            v3.push_back(NULL);
            v3.push_back(0);

            if (isGameOver(board, Ai))
                return v1;
            else if (isGameOver(board, Player))
                return v2;
            else
                return v3;
        } else {
            vector<int> temp;
            temp.push_back(NULL);
            temp.push_back(scorePosition(board, Ai));
            return temp;
        }
    }
    if (maximizingPlayer) {

        int value = numeric_limits<int>::min();
        int row = 0;
        int newScore = 0;
        srand(time(0));
        int column = rand() % valid_locations.size();
        vector<vector<int>> tempBoard;
        for (int i = 0; i < valid_locations.size(); i++) {
            row = getNextRow(board, i);
            tempBoard = board;
            insertPiece(tempBoard, row, i, Ai);
            newScore = minimax(tempBoard, depth - 1, alpha, beta, false)[1];
            if (newScore > value) {
                value = newScore;
                column = i;
            }
            int alpha = max(alpha, value);
            if (alpha >= beta)
                break;
        }
        vector<int> v;
        v.push_back(column);
        v.push_back(value);
        return v;
    } else {
        int value2 = numeric_limits<int>::max();
        int row2 = 0;
        srand(time(0));
        int column2 = rand() % valid_locations.size();
        int newScore = 0;
        vector<vector<int>> tempBoard2;
        for (int i = 0; i < valid_locations.size(); i++) {
            row2 = getNextRow(board, i);
            tempBoard2 = board;
            insertPiece(tempBoard2, row2, i, Player);
            newScore = minimax(tempBoard2, depth - 1, alpha, beta, true)[1];
            if (newScore < value2) {
                value2 = newScore;
                column2 = i;
            }
            int beta = min(beta, value2);
            if (alpha >= beta)
                break;
        }

        vector<int> v;
        v.push_back(column2);
        v.push_back(value2);
        return v;
    }
}

int pickBestMove(vector<vector<int>> board, int piece) {
    vector<int> validLocations;
    validLocations = getValidLocations(board);
    int score = 0;
    int row = 0;
    int bestScore = -100000;
    srand(time(0));
    int bestCol = rand() % validLocations.size();
    vector<vector<int>> tempBoard;
    for (int i = 0; i < validLocations.size(); i++) {
        row = getNextRow(board, i);
        tempBoard = board;
        insertPiece(tempBoard, row, i, piece);
        score = scorePosition(tempBoard, piece);
        if (score > bestScore) {
            bestScore = score;
            bestCol = i;
        }
    }
    return bestCol;
}

vector<vector<int>> board = createBoard();

int main() {
    printBoard(board);
    int value1 = numeric_limits<int>::min();
    int value2 = numeric_limits<int>::max();
    srand(time(0));
    turn = rand() % 2;
    int column = 0;
    int minimax_score = 0;
    while (!gameOver) {
        if (turn == Player) {
            cout << "Player 1, please choose a column (1-7): ";
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

            cout << "AI is playing: " << endl;
            // column = pickBestMove(board,ai_piece);
            column = minimax(board, 2, value1, value2, true)[0];
            minimax_score = minimax(board, 2, value1, value2, true)[1];
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
        turn = turn % 2;
        printBoard(board);
    }
    return 0;
}

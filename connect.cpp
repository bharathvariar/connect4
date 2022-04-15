#include <Windows.h>
#include <bits/stdc++.h>
using namespace std;

static int ROW_COUNT = 6, COLUMN_COUNT = 7, PLAYER1 = 0, PLAYER2 = 1, AI = 1, PLAYER1_PIECE = 1, PLAYER2_PIECE = 2, AI_PIECE = 2, EMPTY = 0, WINDOW_LENGTH = 4;

vector<vector<int>> createBoard() {
    vector<vector<int>> board = vector<vector<int>>(ROW_COUNT, vector<int>(COLUMN_COUNT, 0));
    return board;
}

void insertPiece(vector<vector<int>> &board, int row, int column, int piece) {
    board[row][column] = piece;
    return;
}

bool isValidLocation(vector<vector<int>> board, int column) {
    if (board[ROW_COUNT - 1][column] == 0) {
        return true;
    }

    return false;
}

bool isValidColumn(int column) {
    if (column >= 0 and column <= COLUMN_COUNT - 1) {
        return true;
    }
    return false;
}

void printBoard(vector<vector<int>> board) {
    cout << " 1 2 3 4 5 6 7 " << endl;
    for (int row = ROW_COUNT - 1; row >= 0; row--) {
        cout << "|";
        for (int col = 0; col < COLUMN_COUNT; col++) {
            if (col != COLUMN_COUNT - 1) {
                if (board[row][col] == 1) {
                    cout << "X|";
                } else if (board[row][col] == 2) {
                    cout << "O|";
                } else if (board[row][col] == 0) {
                    cout << " |";
                }
            } else {
                if (board[row][col] == 1) {
                    cout << "X";
                } else if (board[row][col] == 2) {
                    cout << "O";
                } else if (board[row][col] == 0) {
                    cout << " ";
                }
                // cout << board[row][col];
            }
        }
        cout << "|" << endl;
    }
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

int getNextRow(vector<vector<int>> board, int column) {
    for (int row = 0; row < ROW_COUNT; row++) {
        if (board[row][column] == 0) {
            return row;
        }
    }
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

bool isTerminalNode(vector<vector<int>> board) {
    vector<int> validLocations = getValidLocations(board);
    return isGameOver(board, PLAYER1_PIECE) or isGameOver(board, AI_PIECE) or validLocations.size() == 0;
}

int evaluateWindow(vector<int> window, int piece) {
    int score = 0;
    int opp_piece = PLAYER1_PIECE;
    if (piece == PLAYER1_PIECE)
        opp_piece = AI_PIECE;
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
    return score;
}

int scorePosition(vector<vector<int>> board, int piece) {
    int score = 0;
    int center_count = 0;
    vector<int> center_array(6);
    for (int i = 0; i < ROW_COUNT; i++) {
        center_array[i] = board[i][COLUMN_COUNT / 2];
    }

    for (int i = 0; i < center_array.size(); i++) {
        if (center_array[i] == piece)
            center_count++;
    }
    // Score horizontal
    vector<int> row_array;
    vector<int> window1;
    int countPiece = 0, countEmpty = 0;
    for (int i = 0; i < ROW_COUNT; i++) {
        row_array = board[i];
        for (int c = 0; c < COLUMN_COUNT - 3; c++) {
            for (int j = 0; j < WINDOW_LENGTH; j++) {
                window1.push_back(row_array[c + j]);
            }
            score += evaluateWindow(window1, piece);
            window1.clear();
        }
    }

    vector<int> col_array;
    vector<int> window2;
    for (int i = 0; i < COLUMN_COUNT; i++) {
        col_array.clear(); // Initialising col_array
        for (int j = 0; j < ROW_COUNT; j++) {
            col_array.push_back(board[j][i]);
        }
        for (int r = 0; r < ROW_COUNT - 3; r++) {
            for (int j = 0; j < WINDOW_LENGTH; j++) {
                window2.push_back(col_array[r + j]);
            }
            score += evaluateWindow(window2, piece);
            window2.clear();
        }
    }
    // Score Vertical
    // Scoring +vely sloped diagonal
    vector<int> window3;
    for (int r = 0; r < ROW_COUNT - 3; r++) {
        for (int c = 0; c < COLUMN_COUNT - 3; c++) {
            window3.clear();
            for (int i = 0; i < WINDOW_LENGTH; i++) {
                window3.push_back(board[r + i][c + i]);
            }
            score += evaluateWindow(window3, piece);
            window3.clear();
        }
    }

    // Sccoring -vely sloped diagonal
    vector<int> window4;
    for (int r = 0; r < ROW_COUNT - 3; r++) {
        for (int c = 0; c < COLUMN_COUNT - 3; c++) {
            window4.clear();
            for (int i = 0; i < WINDOW_LENGTH; i++) {
                window4.push_back(board[r + 3 - i][c + i]);
            }
            score += evaluateWindow(window4, piece);
            window4.clear();
        }
    }
    return score;
}

int pickBestMove(vector<vector<int>> board, int piece) {
    vector<int> validLocations = getValidLocations(board);
    int score = 0;
    int row = 0;
    int bestScore = -100000;
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

vector<int> minimax(vector<vector<int>> &board, int depth, int alpha, int beta, int maximizingPlayer) {
    vector<int> validLoctions = getValidLocations(board);
    bool isTerminal = isTerminalNode(board);
    if ((depth == 0) or (isTerminal)) {
        vector<int> tup(2);
        if (isTerminal) {
            if (isGameOver(board, AI_PIECE)) {
                tup = {NULL,
                       1000000000};
            } else if (isGameOver(board, PLAYER1_PIECE)) {
                tup = {NULL,
                       -1000000000};
            } else {
                tup = {NULL, 0};
            }
        } else {
            tup = {NULL, scorePosition(board, AI_PIECE)};
        }
        return tup;
    }

    if (maximizingPlayer) {
        int row, column, value, newScore;
        vector<int> tup;
        value = numeric_limits<int>::min();
        column = rand() % validLoctions.size();
        for (int col : validLoctions) {
            row = getNextRow(board, col);
            vector<vector<int>> tempboard = board;
            insertPiece(tempboard, row, col, AI_PIECE);
            newScore = minimax(tempboard, depth - 1, alpha, beta, false)[1];
            if (newScore > value) {
                value = newScore;
                column = col;
            }
            alpha = max(alpha, value);
            if (alpha >= beta) {
                break;
            }
        }
        tup = {column, value};
        return tup;
    } else { // minimizingPlayer
        int row, column, value, newScore;
        vector<int> tup;
        value = numeric_limits<int>::max();
        column = rand() % validLoctions.size();
        for (int col : validLoctions) {
            row = getNextRow(board, col);
            vector<vector<int>> tempboard = board;
            insertPiece(tempboard, row, col, PLAYER1_PIECE);
            newScore = minimax(tempboard, depth - 1, alpha, beta, true)[1];
            if (newScore < value) {
                value = newScore;
                column = col;
            }
            beta = min(beta, value);
            if (alpha >= beta) {
                break;
            }
        }
        tup = {column, value};
        return tup;
    }
}

int main() {
beginGame:
    cout << "Welcome! Choose your Mode of Play:\nPress 1 for 1 Player\nPress 2 for 2 Player" << endl;
    srand(time(0));
    int numPlayers;
    cin >> numPlayers;
    vector<vector<int>> board = createBoard();
    bool gameOver = false;
    if (numPlayers == 1) {
        int alpha = numeric_limits<int>::min();
        int beta = numeric_limits<int>::max();
        int column = 0;
        int minimax_score = 0;
        int level;
        while (true) {
            cout << "Enter level of difficulty:\n1: Beginner\n2: Amateur\n3: Professional\n4: World Class\n";
            cin >> level;
            if (level < 1 or level > 4) {
                cout << "Please choose a valid level" << endl;
            } else {
                break;
            }
        }
        int turn = rand() % 2; // Setting Random turn between 0 and 1
        cout << "The Game begins...Enjoy!\nPress 0 to exit midgame" << endl;
        printBoard(board);
        while (!gameOver) {
            if (turn == PLAYER1) {
                cout << "Player 1, please choose a column (1-7): ";
                cin >> column;
                column--;
                if (column == -1) {
                    gameOver = true;
                    continue;
                }
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

                cout << "AI Thinking";
                Sleep(250);
                cout << ".";
                Sleep(250);
                cout << ".";
                Sleep(250);
                cout << ".";
                Sleep(250);
                cout << endl;
                int col = minimax(board, level, alpha, beta, true)[0];
                minimax_score = minimax(board, level, alpha, beta, true)[1];
                if (isValidLocation(board, col)) {
                    int row = getNextRow(board, col);
                    insertPiece(board, row, col, AI_PIECE);
                    if (isGameOver(board, AI_PIECE)) {
                        gameOver = true;
                        cout << "Sorry, You Lose! Better Luck Next Time" << endl;
                    }
                }
            }
            turn++;
            turn %= 2;
            printBoard(board);
        }
    } else if (numPlayers == 2) {
        int turn = 0;
        int column = 0;
        cout << "The Game begins...Enjoy!\nPress 0 to exit midgame" << endl;
        printBoard(board);
        while (!gameOver) {
            if (turn == PLAYER1) {
                cout << "Player 1, please choose a column (1-7): ";
                cin >> column;
                column--;
                if (column == -1) {
                    gameOver = true;
                    continue;
                }
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
                if (column == -1) {
                    gameOver = true;
                    continue;
                }
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
    } else {
        cout << "Please enter valid number of players!" << endl;
        goto beginGame;
    }

    if (gameOver) {
        while (true) {
            char c;
            cout << "Do you want to play again?\nPress Y or N" << endl;
            cin >> c;
            if (c == 'Y' or c == 'y') {
                goto beginGame;
            } else if (c == 'N' or c == 'n') {
                cout << "Thank you for playing!" << endl;
                break;
            } else {
                cout << "Please enter a valid character" << endl;
            }
        }
    }
}

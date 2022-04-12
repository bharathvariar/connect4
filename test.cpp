#include <Windows.h>
#include <bits/stdc++.h>
using namespace std;


static int ROW_COUNT = 6, COLUMN_COUNT = 7, PLAYER1 = 0, PLAYER2 = 1, AI = 1, PLAYER1_PIECE = 1, PLAYER2_PIECE = 2, AI_PIECE = 2, EMPTY = 0, WINDOW_LENGTH = 4;

vector<vector<int>> createBoard() {
    vector<vector<int>> board = vector<vector<int>>(ROW_COUNT, vector<int>(COLUMN_COUNT, 0));
    return board;
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
    vector<int> window1;
    int countPiece = 0, countEmpty = 0;
    for (int i = 0; i < ROW_COUNT; i++) {
        row_array = board[i];
        for (int c = 0; c < COLUMN_COUNT - 3; c++) {
            for (int j = 0; j < WINDOW_LENGTH; j++) {
                window1.push_back(row_array[c + j]);
            }
            score += evaluateWindow(window1, piece);
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
            for (int j = 0; j < WINDOW_LENGTH; j++) {
                window2.push_back(col_array[r + j]);
            }
            score += evaluateWindow(window2, piece);
        }
    }

    // Scoring +vely sloped diagonal
    vector<int> window3;
    for (int r = 0; r < ROW_COUNT - 3; r++) {
        for (int c = 0; c < COLUMN_COUNT - 3; c++) {
            window3.clear();
            for (int i = 0; i < WINDOW_LENGTH; i++) {
                window3.push_back(board[r + i][c + i]);
            }
            score += evaluateWindow(window3, piece);
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
        }
    }

    return score;
}

int main() {
    vector<vector<int>> board = createBoard();
}
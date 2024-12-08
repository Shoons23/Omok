#include "WinCondition.h"

bool WinCondition::checkWin(const std::vector<std::vector<int>>& board, int row, int col) {
    // 8방향 체크: 가로, 세로, 대각선
    const int directions[8][2] = {
        {0, 1},   // 가로
        {1, 0},   // 세로
        {1, 1},   // 대각선 ↘
        {1, -1},  // 대각선 ↙
        {0, -1},  // 가로 반대
        {-1, 0},  // 세로 반대
        {-1, -1}, // 대각선 ↖
        {-1, 1}   // 대각선 ↗
    };

    // 4방향에 대해 체크 (반대 방향은 같이 체크됨)
    for (int i = 0; i < 4; i++) {
        if (checkDirection(board, row, col, directions[i][0], directions[i][1])) {
            return true;
        }
    }
    return false;
}

bool WinCondition::checkDirection(const std::vector<std::vector<int>>& board, int row, int col, int dRow, int dCol) {
    int count = 1;  // 현재 돌을 포함하여 시작
    int player = board[row][col];

    // 정방향 확인
    for (int i = 1; i < 5; i++) {
        int newRow = row + dRow * i;
        int newCol = col + dCol * i;
        
        if (newRow < 0 || newRow >= BOARD_SIZE || newCol < 0 || newCol >= BOARD_SIZE) {
            break;
        }
        
        if (board[newRow][newCol] != player) {
            break;
        }
        
        count++;
    }

    // 반대방향 확인
    for (int i = 1; i < 5; i++) {
        int newRow = row - dRow * i;
        int newCol = col - dCol * i;
        
        if (newRow < 0 || newRow >= BOARD_SIZE || newCol < 0 || newCol >= BOARD_SIZE) {
            break;
        }
        
        if (board[newRow][newCol] != player) {
            break;
        }
        
        count++;
    }

    return count >= 5;
} 
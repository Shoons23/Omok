#ifndef WINCONDITION_H
#define WINCONDITION_H

#include <vector>

class WinCondition {
public:
    static bool checkWin(const std::vector<std::vector<int>>& board, int row, int col);

private:
    static bool checkDirection(const std::vector<std::vector<int>>& board, int row, int col, int dRow, int dCol);
    static const int BOARD_SIZE = 15;
};

#endif // WINCONDITION_H 
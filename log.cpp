#include <iostream>
#include <fstream>
#include <vector>

void logMoveToFile(int player, int row, int col, const std::string& filename) {
    std::ofstream logFile(filename, std::ios::app);  // append 모드로 열기
    
    if (logFile.is_open()) {
        logFile << "Player " << player << " placed a stone at (" << row << ", " << col << ")\n";
        logFile.close();
    } else {
        std::cerr << "로그 파일을 열 수 없습니다." << std::endl;
    }
}

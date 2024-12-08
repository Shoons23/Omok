#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <QtCore>

class UserLogin {
private:
    std::string username;
    std::string password;
    const std::string USER_FILE = "users.txt";

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    bool isValidCredentials() {
        std::ifstream file(USER_FILE);
        std::string line;
        std::string storedUser, storedPass;
        
        while (std::getline(file, line)) {
            size_t delimiter = line.find(':');
            if (delimiter != std::string::npos) {
                storedUser = line.substr(0, delimiter);
                storedPass = line.substr(delimiter + 1);
                
                if (storedUser == username && storedPass == password) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    UserLogin() {}

    bool registerUser() {
        clearScreen();
        std::cout << "=== 회원가입 ===" << std::endl;
        
        std::cout << "사용자 이름: ";
        std::cin >> username;
        std::cout << "비밀번호: ";
        std::cin >> password;

        std::ofstream file(USER_FILE, std::ios::app);
        if (file.is_open()) {
            file << username << ":" << password << std::endl;
            file.close();
            std::cout << "회원가입이 완료되었습니다!" << std::endl;
            return true;
        }
        
        std::cout << "회원가입 중 오류가 발생했습니다." << std::endl;
        return false;
    }

    bool login() {
        clearScreen();
        std::cout << "=== 로그인 ===" << std::endl;
        
        std::cout << "사용자 이름: ";
        std::cin >> username;
        std::cout << "비밀번호: ";
        std::cin >> password;

        if (isValidCredentials()) {
            std::cout << "로그인 성공!" << std::endl;
            return true;
        }

        std::cout << "잘못된 사용자 이름 또는 비밀번호입니다." << std::endl;
        return false;
    }
};

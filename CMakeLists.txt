# 최소 CMake 버전 지정
cmake_minimum_required(VERSION 3.1.0)

# 프로젝트 이름과 사용 언어 설정
project(Omok)

# Qt 패키지 찾기
find_package(Qt6 COMPONENTS Widgets REQUIRED)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt의 MOC(Meta-Object Compiler) 처리를 위한 설정
set(CMAKE_AUTOMOC ON)

# 디버그 모드 설정
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

set(SOURCES
    main.cpp
    OmokGUI.cpp
    userLogin.cpp
    log.cpp
    WinCondition.cpp
)

# 실행 파일 생성
add_executable(Omok ${SOURCES})
target_link_libraries(Omok PRIVATE Qt6::Widgets)
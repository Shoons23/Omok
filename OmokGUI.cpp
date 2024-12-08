#include "OmokGUI.h"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include "log.h"
#include "WinCondition.h"
#include <QMessageBox>

const int GRID_SIZE = 40;
const int BOARD_SIZE = 15;

OmokBoard::OmokBoard(QWidget *parent)
    : QWidget(parent), board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0)), currentPlayer(1) {
    setFixedSize(GRID_SIZE * BOARD_SIZE, GRID_SIZE * BOARD_SIZE);
}

void OmokBoard::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    
    // 배경색 설정
    painter.fillRect(rect(), QColor(255, 228, 181));

    // 격자 그리기
    painter.setPen(Qt::black);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        int pos = i * CELL_SIZE + BOARD_MARGIN;
        painter.drawLine(pos, BOARD_MARGIN, pos, height() - BOARD_MARGIN);
        painter.drawLine(BOARD_MARGIN, pos, width() - BOARD_MARGIN, pos);
    }

    // 바둑돌 그리기
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (board[y][x] == 1) {
                drawStone(painter, x, y, Qt::black);
            } else if (board[y][x] == 2) {
                drawStone(painter, x, y, Qt::white);
            }
        }
    }
}

void OmokBoard::mousePressEvent(QMouseEvent *event) {
    QPointF pos = event->position();
    
    QPoint intersection = getClosestIntersection(pos.x(), pos.y());
    int x = (intersection.x() - BOARD_MARGIN) / CELL_SIZE;
    int y = (intersection.y() - BOARD_MARGIN) / CELL_SIZE;

    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return;
    }

    if (board[y][x] != 0) {
        return;
    }

    board[y][x] = currentPlayer;
    logMoveToFile(currentPlayer, x, y, "omok_game.log");

    // 승리 조건 체크
    if (WinCondition::checkWin(board, y, x)) {
        QString winner = (currentPlayer == 1) ? "흑돌" : "백돌";
        QMessageBox::information(this, "게임 종료", winner + " 승리!");
        // 게임 초기화
        board = std::vector<std::vector<int>>(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));
        currentPlayer = 1;
        update();
        return;
    }

    currentPlayer = (currentPlayer == 1) ? 2 : 1;
    update();
}

// 가장 가까운 교차점 찾기 함수 구현
QPoint OmokBoard::getClosestIntersection(int x, int y) {
    x -= BOARD_MARGIN;
    y -= BOARD_MARGIN;
    
    // 가장 가까운 교차점 계산
    int gridX = round(static_cast<double>(x) / CELL_SIZE) * CELL_SIZE + BOARD_MARGIN;
    int gridY = round(static_cast<double>(y) / CELL_SIZE) * CELL_SIZE + BOARD_MARGIN;
    
    return QPoint(gridX, gridY);
}

void OmokBoard::drawStone(QPainter &painter, int x, int y, QColor color) {
    // 교차점 중심 좌표 계산
    int centerX = x * CELL_SIZE + BOARD_MARGIN;
    int centerY = y * CELL_SIZE + BOARD_MARGIN;
    
    // 바둑돌 크기의 절반
    int stoneRadius = STONE_SIZE / 2;
    
    // 바둑돌 그리기
    painter.setBrush(color);
    painter.setPen(Qt::black);
    painter.drawEllipse(QPoint(centerX, centerY), stoneRadius, stoneRadius);
}


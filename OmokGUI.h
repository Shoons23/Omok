#pragma once

#include <QWidget>
#include <vector>

class OmokBoard : public QWidget {
    Q_OBJECT

private:
    std::vector<std::vector<int>> board;
    int currentPlayer;
    const int CELL_SIZE = 40;  // 격자 한 칸의 크기
    const int BOARD_MARGIN = 40;  // 보드 여백
    const int STONE_SIZE = 36;  // 바둑돌 크기

public:
    OmokBoard(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void drawStone(QPainter &painter, int x, int y, QColor color);
    QPoint getClosestIntersection(int x, int y);  // 가장 가까운 교차점 찾기
}; 
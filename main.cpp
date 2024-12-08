#include <QApplication>
#include "OmokGUI.h"
#include "log.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    OmokBoard board;
    board.setWindowTitle("오목판");
    board.show();


    return app.exec();
}
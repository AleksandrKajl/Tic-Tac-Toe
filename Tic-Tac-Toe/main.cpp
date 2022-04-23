#include "TicTacToe.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicTacToe w;
    w.setWindowIcon(QIcon(":/resource/ticTacToe.png"));
    w.show();
    
    return a.exec();
}

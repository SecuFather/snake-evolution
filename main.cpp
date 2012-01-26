#include <QApplication>
#include "snakearea.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);
    SnakeArea sa;

    sa.show();
    return app.exec();
}

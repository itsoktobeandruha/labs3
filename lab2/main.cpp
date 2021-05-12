#include <QCoreApplication>
#include "modelview.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ModelView game;
    game.play(3);
    return a.exec();
}


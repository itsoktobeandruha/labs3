#ifndef MODEL_H
#define MODEL_H
#include <QVector>
#include <QPair>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <QDebug>

enum state{

    x,o,none,draw
};
class model
{
private:

    state _player= state::o;
    QVector<QVector<state>> board;
    int taken=0;

public:
    model(short size);
    void move();
    void gotoxy(int xpos, int ypos);
    void draw(QPair<short,short> crd);
    void change_player();
    const QVector<QVector<state>>& get_board();
    state check_diagonal();
    state check_horizont();
    state check_vertical();
    state check_win();

    const state& get_player();

};

#endif // MODEL_H

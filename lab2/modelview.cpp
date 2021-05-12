#include "modelview.h"

ModelView::ModelView()
{
}

void ModelView::play(short size)
{
    auto winner = none;
    _model = new model(size);
    draw_field(size);
    _model->gotoxy(1,1);
    while ((winner = _model->check_win()) == none)
    {
        _model->move();
        auto _player = _model->get_player();
        switch(_player)
        {
            case x:
            {
                std::cout << "x";
                break;
            }
            case o:
            {
                std::cout << "o";
                break;
            }
        }
    }

    switch(winner)
    {
        case o:
        {
            system("cls");
            std::cout << "O win" << std::endl;
            break;
        }
        case x:
        {
            system("cls");
            std::cout << "X win" << std::endl;
            break;
        }
        case draw:
        {
            system("cls");
            std::cout << "DRAW" << std::endl;
            break;
        }
    }
}

void ModelView::draw_field(short size)
{
    for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                std::cout << "--";
            std::cout << "-" << std::endl;
            for (int j = 0; j < size; j++)
                std::cout << "| ";
            std::cout << "|" << std::endl;
        }
        for (int j = 0; j < size; j++)
            std::cout << "--";
        std::cout << "-" << std::endl;
}



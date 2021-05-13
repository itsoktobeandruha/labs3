#include "model.h"


model::model(short size)
{
   for (int i=0; i<size;i++)
   {
      QVector<state> vec(size,state::none);
      board.push_back(vec);
   }

}

void model::move(QPair<int,int> crd)
{

    change_player();
    taken++;
    board[crd.first][crd.second]=_player;
}

void model::gotoxy(int xpos, int ypos)
{
  COORD scrn;

  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

  scrn.X = xpos; scrn.Y = ypos;

  SetConsoleCursorPosition(hOuput,scrn);

}

void model::change_player()
{
    _player = (state)(((int)_player +1) % 2);
}

const QVector<QVector<state> > &model::get_board()
{
    return board;
}

state model::check_diagonal()
{
    auto player = none;

    for (int i = 0; i < board.size(); ++i) // этот фор ищет по диагонали первое занятое место, и записывает в переменную player  того кто стоял в занятом месте, чтобы во 2 форе проверить, занял ли player все позиции по диагонали
    {
        if (board[i][i] != none)
        {
            player = board[i][i];
            break;
        }
    }

    if (player != none)
    {
        for (int i=0,j=0; i<board.size();i++,j++)
        {
            if (board[i][j] != player)
                return none;
        }
        return player;
    }

    return none;
}

state model::check_horizont()
{
    auto player = none;
    for (int i=0; i<board.size(); ++i)
    {
        if (board[i][0]==none)
        {
            continue;
        }
        player = board[i][0];
        for (int j=0; j<board.size();++j)
        {
            if (board[i][j]!=player)
            {
                    player = none;
                    break;
            }
        }
        if (player == none)
        {
            continue;
        }
        return player;
    }
    return player;
}

state model::check_vertical()
{
    auto player = none;
    for (int j=0; j<board.size(); j++)
    {
        if (board[0][j]==none)
        {
            continue;
        }
        player = board[0][j];
        for (int i=0; i<board.size(); i++)
        {
            if (board[i][j]!=player)
            {
                player = none;
                break;
            }
        }
        if (player == none)
        {
            continue;
        }
        return player;
    }
    return player;
}

state model::check_win()
{
    auto player = none;

     player = check_diagonal();
     if (player!=none)
     {
         return player;
     }
     player = check_horizont();
     if (player!=none)
     {
         return player;
     }
     player = check_vertical();
     if (player!=none)
     {
         return player;
     }

     if (taken==board.size()*board.size())
     {
         return state::draw;
     }

    return player;

}

const state& model::get_player()
{
    return _player;
}

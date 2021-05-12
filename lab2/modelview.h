#ifndef MODELVIEW_H
#define MODELVIEW_H
#include "model.h"

class ModelView
{
private:
    model* _model;
public:
    ModelView();
    void play(short size);
    void draw_field(short size);
};

#endif // MODELVIEW_H

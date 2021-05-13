#include "mypushbutton.h"


myPushButton::myPushButton(QWidget *parent, QPair<int, int> coordinates) : QPushButton(parent)
{
    coords = coordinates;
}

myPushButton::~myPushButton()
{

}

void myPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked(coords);
}

#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QPair>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(QWidget* parent = nullptr, QPair<int, int> coordinates = {-1, -1});
    QPair<int, int> coords;
    ~myPushButton();
signals:
    void clicked(QPair<int, int>);
protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);
};

#endif // MYPUSHBUTTON_H

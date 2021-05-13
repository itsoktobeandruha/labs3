#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QObject>
#include "mainwindow.h"

class modelview : public QObject
{
    Q_OBJECT
public:
    explicit modelview(QObject *parent = nullptr);
    modelview(Ui::MainWindow *ui);

private:
Ui::MainWindow *ui;

signals:

public slots:

};

#endif // MODELVIEW_H

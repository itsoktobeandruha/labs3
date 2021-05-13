#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(create_field()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::end_game()
{
    for (int i=0; i<_model->get_board().size();i++)
    {
        for (int j=0; j<_model->get_board().size();j++)
        {
            ui->boardLayout->itemAt(i)->layout()->itemAt(j)->widget()->setEnabled(false);
        }
    }
}

void MainWindow::create_field()
{
    QString str = ui->sizeEdit->text();
    int size = str.toInt();
    if (size<3 || size>10)
    {
        QMessageBox error;
        error.setText("SIZE MUST BE LARGER THAN 2 AND LESS THAN 10");
        error.exec();
        return;
    }
    _model = new model(size);
    ui->sizeEdit->setEnabled(false);
    ui->startButton->setEnabled(false);
    for (int i=0; i<size; i++)
    {
        ui->boardLayout->addLayout(new QHBoxLayout());
        for (int j=0; j<size; j++)
        {
            myPushButton *button = new myPushButton(nullptr,{i,j});
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
            ui->boardLayout->itemAt(i)->layout()->addWidget(button);
            connect(button,SIGNAL(clicked(QPair<int,int>)),this,SLOT(make_move(QPair<int,int>)));
        }

    }
}

void MainWindow::make_move(QPair<int,int> crd)
{
    _model->move(crd);
    qobject_cast<QPushButton*>(sender())->setEnabled(false);
    auto player = _model->get_player();
    if (player == state::x)
    {
         qobject_cast<QPushButton*>(sender())->setText("X");
    }
    else
    {
        qobject_cast<QPushButton*>(sender())->setText("O");
    }
    auto winner = _model->check_win();
    if (winner == state::x)
    {
          QMessageBox winner;
          winner.setText("X WIN!!!!");
          winner.exec();
          return end_game();
    }
    else if (winner == state::o)
    {
        QMessageBox winner;
        winner.setText("O WIN!!!!");
        winner.exec();
        return end_game();
    }
    else if (winner == state::draw)
    {
        QMessageBox winner;
        winner.setText("DRAW");
        winner.exec();
        return end_game();
    }


}


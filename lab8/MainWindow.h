#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <QString>
#include <QList>
#include <QTableWidgetItem>
#include <QProcess>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    struct proc{
        DWORD PID;
        SIZE_T MEMORY;
        QString NAME;
        QString PRIORITY;
        proc(int pid, wchar_t* name)
        {
            PID = pid;
            NAME = QString::fromWCharArray(name);
            MEMORY = GetProcMemory(pid);
            PRIORITY = ParsePriority(pid);
        }
    };

    static SIZE_T GetProcMemory(unsigned long PID);
    static QString ParsePriority(DWORD PID);
    friend proc;

private slots:
    void update_processes();
    void show_processes(QList<proc> proc_list);
    void kill_process();

signals:
    void update(QList<proc>);
};
#endif // MAINWINDOW_H

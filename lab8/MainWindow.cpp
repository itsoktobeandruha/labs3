#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::update_processes);
    connect(this, &MainWindow::update,this,&MainWindow::show_processes);
    connect(ui->killButton, &QPushButton::clicked, this, &MainWindow::kill_process);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_processes()
{
    QList<proc> proc_list;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pr_struct;
    pr_struct.dwSize = sizeof(PROCESSENTRY32);
    Process32First(snapshot, &pr_struct);
    do
    {    
            proc process(pr_struct.th32ProcessID, pr_struct.szExeFile);
            proc_list.push_back(process);
    }
    while (Process32Next(snapshot, &pr_struct));
    emit update(proc_list);
}

void MainWindow::show_processes(QList<MainWindow::proc> proc_list)
{
    ui->processTable->setSortingEnabled(false);
    ui->processTable->clearContents();
    ui->processTable->setRowCount(proc_list.size());
    int j=0;
    for (auto& i : proc_list)
    {
        ui->processTable->setItem(j,0,new QTableWidgetItem(i.NAME));
        ui->processTable->setItem(j,1, new QTableWidgetItem(QString::number(i.PID)));
        ui->processTable->setItem(j,2,new QTableWidgetItem(QString::number(i.MEMORY)));
        ui->processTable->setItem(j,3,new QTableWidgetItem(i.PRIORITY));
        j++;
    }
    ui->processTable->setSortingEnabled(true);
}

void MainWindow::kill_process()
{
    system(("taskkill /F /PID " + ui->killString->text()).toStdString().c_str());
    update_processes();
}

SIZE_T MainWindow::GetProcMemory(unsigned long PID)
{
    auto ProcHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(ProcHandle, &pmc, sizeof(pmc));
    return pmc.WorkingSetSize / 1024 / 1024;
}

QString MainWindow::ParsePriority(DWORD PID)
{
    auto hProc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);
    DWORD priority = GetPriorityClass(hProc);
    QString priority_string;

    switch (priority)
    {
        case ABOVE_NORMAL_PRIORITY_CLASS:
        priority_string = QString::fromWCharArray(L"ABOVE NORMAL");
        break;

        case BELOW_NORMAL_PRIORITY_CLASS:
            priority_string = QString::fromWCharArray(L"BELOW NORMAL");
            break;

        case NORMAL_PRIORITY_CLASS:
            priority_string = QString::fromWCharArray(L"NORMAL");
            break;

        case HIGH_PRIORITY_CLASS:
            priority_string = QString::fromWCharArray(L"HIGH");
            break;

        case IDLE_PRIORITY_CLASS:
            priority_string = QString::fromWCharArray(L"IDLE");
            break;

        case REALTIME_PRIORITY_CLASS:
            priority_string = QString::fromWCharArray(L"REALTIME");
            break;

        default:
            priority_string = QString::fromWCharArray(L"UNKNOWN");
            break;
    }

    return priority_string;
}





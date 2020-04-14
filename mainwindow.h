#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <qsharedmemory.h>

struct SData {
    int a;
    int b;
    int c;
    int d[24];
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbTweede_clicked();
    void on_actionProbeersel_triggered();
    void on_pbFillShem_clicked();

private:
    void detach();

    Ui::MainWindow *ui;
    QSharedMemory sharedMemory;
    SData *shData;
    int timerID;

protected:
    void timerEvent( QTimerEvent *event);
};

#endif // MAINWINDOW_H

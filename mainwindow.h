#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "mazeitem.h"

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
    void on_fileOpenButton_clicked();

private:
    Ui::MainWindow *ui;
    MazeItem *item;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileOpenButton_clicked()
{
    QString selectedFilter;
    QString openFilePath = QFileDialog::getOpenFileName(this,tr("Open maze file..."),
                                                        QString(),
                                                        "Maze file(*.dat)",
                                                        //";;Map text(*.txt)",
                                                        &selectedFilter);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    item = new MazeItem();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
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
    item = new MazeItem(openFilePath);
    scene->addItem(item);
}

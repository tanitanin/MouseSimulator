#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    item = new MazeItem();
    mouse = new MouseItem();
    scene->addItem(item);
    scene->addItem(mouse);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete item;
    //delete mouse;
    delete scene;
}

void MainWindow::on_fileOpenButton_clicked()
{
    QString selectedFilter;
    QString openFilePath = QFileDialog::getOpenFileName(this,tr("Open maze file..."),
                                                        QString(),
                                                        "Maze file(*.dat)",
                                                        //";;Map text(*.txt)",
                                                        &selectedFilter);
    if(item && item->scene()==scene) scene->removeItem(item);
    if(mouse && mouse->scene()==scene) scene->removeItem(mouse);
    if(item) delete item;
    if(mouse) delete mouse;
    item = new MazeItem(openFilePath);
    mouse = new MouseItem(openFilePath);
    scene->addItem(item);
    scene->addItem(mouse);
    ui->startButton->setEnabled(true);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mazescene = new QGraphicsScene(this);
    mazeitem = new MazeItem();
    mazescene->addItem(mazeitem);

    mousescene = new QGraphicsScene(this);
    item = new MazeItem();
    mouse = new MouseItem();
    mousescene->addItem(item);
    mousescene->addItem(mouse);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete item;
    //delete mouse;
    delete mazescene;
    delete mousescene;
}

void MainWindow::on_fileOpenButton_clicked()
{
    QString selectedFilter;
    QString openFilePath = QFileDialog::getOpenFileName(this,tr("Open maze file..."),
                                                        QString(),
                                                        "Maze file(*.dat)",
                                                        //";;Map text(*.txt)",
                                                        &selectedFilter);
    if(mazeitem && mazeitem->scene()==mazescene) mazescene->removeItem(mazeitem);
    if(mouse && mouse->scene()==mousescene) mousescene->removeItem(mouse);
    if(item) delete item;
    if(mouse) delete mouse;

    // サブ画面
    mazeitem = new MazeItem(openFilePath);
    mazescene->addItem(mazeitem);
    mazescene->setSceneRect(QRect(0,0,400,400));
    ui->subGraphicsView->setScene(mazescene);
    QMatrix matrix;
    matrix.scale(160.0/400.0,160.0/400.0);
    ui->subGraphicsView->setMatrix(matrix);

    // メイン画面
    item = new MazeItem(openFilePath);
    mouse = new MouseItem(openFilePath);
    mousescene->addItem(item);
    mousescene->addItem(mouse);
    mousescene->setSceneRect(QRect(0,0,400,400));
    ui->graphicsView->setScene(mousescene);

    QString w,h;
    w.setNum(item->width()), h.setNum(item->height());
    ui->widthLineEdit->setText(w);
    ui->heightLineEdit->setText(h);
    ui->startButton->setEnabled(true);
}

#include "mainwindow.h"
#include <QStatusBar>
#include <QActionGroup>
#include <QMessageBox>
#include <QColorDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
     setStyleSheet("background-color: white;");
    currentColor=Qt::black;

    setWindowTitle(tr("简单绘图程序 未命名"));
    centerWidget=new CenterWidget(this);
    setCentralWidget(centerWidget);


    fileMenu=menuBar()->addMenu(tr("文件"));
    newAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\new.png"),tr("新建"),this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("新建绘图文件"));
    openAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\open.png"),tr("打开"),this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("打开保存的绘图文件"));
    saveAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\save.png"),tr("保存"),this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("保存当前绘图文件"));
    exitAction=new QAction(tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+X"));
    exitAction->setStatusTip(tr("退出程序"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    lineAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\line.png"),tr("线条"),this);
    lineAction->setShortcut(tr("Ctrl+L"));
    lineAction->setStatusTip(tr("绘制线条"));
    ellipseAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\ellipse.png"),tr("椭圆"),this);
    ellipseAction->setShortcut(tr("Ctrl+E"));
    ellipseAction->setStatusTip(tr("绘制椭圆"));
    rectangleAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\rectangle.png"),tr("矩形"),this);
    rectangleAction->setShortcut(tr("Ctrl+R"));
    rectangleAction->setStatusTip(tr("绘制矩形"));
    pointAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\point.png"),tr("点"),this);
    pointAction->setShortcut(tr("Ctrl+P"));
    pointAction->setStatusTip(tr("绘制点"));
    undoAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\undo.png"),tr("撤销"),this);
    undoAction->setShortcut(tr("Ctrl+Z"));
    undoAction->setStatusTip(tr("撤销"));
    redoAction=new QAction(QIcon("D:\\gitcode\\SimpleDraw\\SimpleDraw_19_1\\res\\redo.png"),tr("重做"),this);
    redoAction->setShortcut(tr("Ctrl+Y"));
    redoAction->setStatusTip(tr("重做"));

    drawMenu= menuBar()->addMenu(tr("绘图"));
    lineAction->setCheckable(true);
    ellipseAction->setCheckable(true);
    rectangleAction->setCheckable(true);
    pointAction->setCheckable(true);
    QActionGroup *group=new QActionGroup(this);
    group->addAction(lineAction);
    group->addAction(ellipseAction);
    group->addAction(rectangleAction);
    group->addAction(pointAction);

    drawMenu->addAction(lineAction);
    drawMenu->addAction(ellipseAction);
    drawMenu->addAction(rectangleAction);
    drawMenu->addAction(pointAction);
    drawMenu->addSeparator();
    drawMenu->addAction(undoAction);
    drawMenu->addAction(redoAction);
    group->setExclusive (true);
    lineAction->setChecked(true);
    QMenu* colorMenu=new QMenu(tr("画笔颜色"),this);
    QAction* setColorAction=new QAction(tr("设置颜色"),this);
    colorMenu->addAction(setColorAction);
    menuBar()->addMenu(colorMenu);
    //颜色预览
    QAction* ColorAction=new QAction(tr(""),this);
    colorToolBar=addToolBar(tr("color"));
    ColorAction->setStatusTip(tr("当前颜色"));
    colorToolBar->addAction(ColorAction);
    QPixmap pixmap(20,20);
    pixmap.fill(currentColor);
    colorToolBar->actions().first()->setIcon(QIcon(pixmap));


    drawToolBar=addToolBar(tr("Draw"));
    drawToolBar->addAction(newAction);
    drawToolBar->addAction(openAction);
    drawToolBar->addAction(saveAction);
    drawToolBar->addSeparator();
    drawToolBar->addAction(lineAction);
    drawToolBar->addAction(ellipseAction);
    drawToolBar->addAction(rectangleAction);
    drawToolBar->addAction(pointAction);
    //线宽设置

    QSlider* lineWidthSlider=new QSlider(Qt::Horizontal);
    lineWidthSlider->setFixedWidth(300);
    lineWidthSlider->setRange(1,20);
    lineWidthSlider->setSingleStep(1);
    lineWidthSlider->setValue(3);
    lineWidthSlider->setToolTip(tr("线条宽度"));


    lineWidthSlider->setTracking(true);
    connect(lineWidthSlider,SIGNAL(valueChanged(int)),this,SLOT(setLineWidth(int)));

    QSpinBox *lineWidthBox=new QSpinBox(this);
    lineWidthBox->setRange(1,20);
    lineWidthBox->setSingleStep(1);
    lineWidthBox->setValue(3);
    lineWidthBox->setSingleStep(1);

    lineWidthSlider->setTracking(true);
    connect(lineWidthBox,SIGNAL(valueChanged(int)),this,SLOT(setLineWidth(int)));


    connect(lineWidthSlider,SIGNAL(valueChanged(int)),lineWidthBox,SLOT(setValue(int)));
    connect(lineWidthBox,SIGNAL(valueChanged(int)),lineWidthSlider,SLOT(setValue(int)));

    drawToolBar->addSeparator();
    drawToolBar->addWidget(lineWidthBox);
    drawToolBar->addWidget(lineWidthSlider);

    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(lineAction,SIGNAL(triggered()),this,SLOT(line()));
    connect(ellipseAction,SIGNAL(triggered()),this,SLOT(ellipse()));
    connect(rectangleAction,SIGNAL(triggered()),this,SLOT(rectangle()));
    connect(pointAction,SIGNAL(triggered()),this,SLOT(point()));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newDrawing()));
    connect(openAction,SIGNAL(triggered()),this,SLOT(openDrawing()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveDrawing()));
    connect(setColorAction,SIGNAL(triggered()),this,SLOT(setColor()));
    connect(ColorAction,SIGNAL(triggered()),this,SLOT(setColor()));
    connect(undoAction,SIGNAL(triggered()),this,SLOT(undo()));
    connect(redoAction,SIGNAL(triggered()),this,SLOT(redo()));
    centerWidget->setDrawType(0);
    statusBar()->show();
}

MainWindow::~MainWindow() {

}
void MainWindow::line() {
    centerWidget->setDrawType(0);
}
void MainWindow::ellipse() {
    centerWidget->setDrawType(1);
}
void MainWindow::rectangle() {
    centerWidget->setDrawType(2);
}
void MainWindow::point() {
    centerWidget->setDrawType(3);
}
void MainWindow::setColor(){
    QColorDialog colorDialog(this);
    colorDialog.setCurrentColor(currentColor);
    if(colorDialog.exec()==QDialog::Accepted){
        currentColor=colorDialog.selectedColor();
        centerWidget->setCurrentColor(currentColor);
    }
    QPixmap pixmap(16,16);
    pixmap.fill(currentColor);
    colorToolBar->actions().first()->setIcon(QIcon(pixmap));

}
void MainWindow::setLineWidth(int value){
    centerWidget->setLineWidth(value);
    //lineWidthBox->setValue(value);
    //lineWidthSlider->setValue(value);
}

void MainWindow::newDrawing() {
    if(centerWidget->getModifiedFlag()==true) { //文档已修改
        switch(QMessageBox::question(this,tr("文档保存提示"),
                                     tr("文档已经修改，是否保存文档"),
                                     QMessageBox::Ok|
                                     QMessageBox::Cancel|QMessageBox::No,
                                     QMessageBox::Ok)) {
            case QMessageBox::Ok:
                centerWidget->saveDrawing();
                break;
            case QMessageBox::Cancel:
                return;
            case QMessageBox::No:
                break;
            default:
                break;
        }
    }
    centerWidget->newDrawing();
}

void MainWindow::openDrawing() {
    if(centerWidget->getModifiedFlag()==true) { //文档已修改
        switch(QMessageBox::question(this,tr("文档保存提示"),
                                     tr("文档已经修改，是否保存文档"),
                                     QMessageBox::Ok|QMessageBox::Cancel
                                     |QMessageBox::No,
                                     QMessageBox::Ok)) {
            case QMessageBox::Ok:
                centerWidget->saveDrawing();
                break;
            case QMessageBox::Cancel:
                return;
            case QMessageBox::No:
                break;
            default:
                break;
        }
    }
    centerWidget->openDrawing();
}
void MainWindow::saveDrawing() {
    centerWidget->saveDrawing();
}
void MainWindow::closeEvent(QCloseEvent *event) {
    if(centerWidget->getModifiedFlag()==true) { //文档已修改
        switch(QMessageBox::question(this,tr("文档保存提示"),
                                     tr("文档已经修改，是否保存文档"),
                                     QMessageBox::Ok|QMessageBox::Cancel
                                     |QMessageBox::No,
                                     QMessageBox::Ok)) {
            case QMessageBox::Ok:
                centerWidget->saveDrawing();
                event->accept();
                break;
            case QMessageBox::Cancel:
                event->ignore();
                return;
            case QMessageBox::No:
                event->accept();
                break;
            default:
                event->accept();
                break;
        }
    }
}
void MainWindow::undo(){
    centerWidget->undo();
}
void MainWindow::redo(){
    centerWidget->redo();
}

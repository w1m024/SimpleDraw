#include "centerwidget.h"
#include <QPainter>
#include <QStatusBar>
#include "mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QColorDialog>
#include <QPen>
#include "shape.h"
CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent) {
    shapes.clear();
    beginDraw=false;
    isModified=false; //还没有绘制图形，未修改状态
    fileName=tr("");
    mousePosLabel=new QLabel;
    mousePosLabel->setText("");
    mousePosLabel->setFixedWidth(110);
    MainWindow *p=(MainWindow *)parent;
    p->statusBar()->addPermanentWidget(mousePosLabel);
    setMinimumSize(500,400);
    setMouseTracking(true);
    lineWidth=3;
}
CenterWidget::~CenterWidget() {
    for(auto shape:shapes)
        delete shape;
}
void CenterWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    qDebug()<<lineWidth;
    QPen pen(currentColor,lineWidth,Qt::SolidLine);
    for(auto shape:shapes)
        shape->draw(&p);
    if(beginDraw==true){
        if(3==drawType)
            return;
         Shape *temp=nullptr;
         switch(drawType){
         case 0:
         temp=new Line(p1,p2,currentColor,lineWidth);
         break;
         case 1:
              temp=new Ellipse(p1,p2,currentColor,lineWidth);
              break;
              case 2:
              temp=new Rectangle(p1,p2,currentColor,lineWidth);
              break;
              }
              temp->draw(&p);
              delete temp;
    }
}
void CenterWidget::setDrawType(int type) {
    drawType=type;
}
void CenterWidget::setLineWidth(int lw){
    lineWidth=lw;
}

void CenterWidget::mousePressEvent(QMouseEvent *e) {
    p1=e->pos();
    p2=p1;
    beginDraw=true;
    if(3==drawType)
        return;
    Shape *temp=nullptr;
    QPainter p(this);
    switch(drawType) {
        case 0:
            temp=new Line(p1,p2,currentColor,lineWidth);
            break;
        case 1:
            temp=new Ellipse(p1,p2,currentColor,lineWidth);
            break;
        case 2:
            temp=new Rectangle(p1,p2,currentColor,lineWidth);
            break;
    default:
        ;
    }
    qDebug()<<"xiangpi";
    temp->draw(&p);
    delete temp;
}
bool CenterWidget::getModifiedFlag() {
    return isModified;
}

void CenterWidget::mouseReleaseEvent(QMouseEvent *e) {
    p2=e->pos();
    beginDraw=false;
    Shape *shape=nullptr;
    if(p1==p2){
    if(3==drawType){
        shape=new Point(p2,currentColor,lineWidth);
        shapes.append(shape);
        isModified=true;
        update();
        waitingShapes.clear();
        return;
    }
    return;
    }
    switch(drawType) {
        case 0:
            shape=new Line(p1,p2,currentColor,lineWidth);
            break;
        case 1:
            shape=new Ellipse(p1,p2,currentColor,lineWidth);
            break;
        case 2:
            shape=new Rectangle(p1,p2,currentColor,lineWidth);
            break;
    default:
;
    }
    if(shape){
        shapes.append(shape);
        isModified=true;
    }
    waitingShapes.clear();
    update();
}
void CenterWidget::mouseMoveEvent(QMouseEvent *e) {
    mousePosLabel->setText("X:"+QString::number(e->x())+",Y:"
                           +QString::number(e->y()));
    p2=e->pos();
    if(beginDraw==false)
        return;
    p2=e->pos(); //更新 p2
    update(); //绘制 p1 和 p2 之间构成的图形
}
void CenterWidget::newDrawing() { //新建绘图
    for(auto shape:shapes)
        delete shape;
    shapes.clear();
    beginDraw=false;
    isModified=false;
    fileName=tr("");
    parentWidget()->setWindowTitle(tr("简单绘图程序 未命名"));
    update(); //更新窗口显示
}
void CenterWidget::openDrawing() { //打开绘图
    fileName=QFileDialog::getOpenFileName(this,
                                          tr("打开文件对话框"),"/","绘图文件(*.draw);;所有文件(*.*)");
    if(fileName==tr(""))
        return;
    for(auto shape:shapes)
        delete shape;
    shapes.clear();
    beginDraw=false;
    isModified=false;
    openFile(fileName); //存储文件
    parentWidget()->setWindowTitle(tr("简单绘图程序 ")+fileName);
    update();
}
void CenterWidget::saveDrawing() { //存储绘图
    if(fileName==tr("")) { //文件名为空，弹出文件选择对话框
        fileName=QFileDialog::getSaveFileName(this,
                                              tr("保存文件对话框"),"/","绘图文件(*.draw);;所有文件(*.*)");
        if(fileName==tr(""))
            return;
    }
    saveFile(fileName); //存储文件
    parentWidget()->setWindowTitle(tr("简单绘图程序 ")+fileName);
    isModified=false;
}

void CenterWidget::saveFile(QString fileName) { //写文件操作
    QFile file(fileName);
    if(file.open(QFile::WriteOnly|QFile::Truncate)) {
        QTextStream out(&file);
        out<<shapes.length()<<endl;
        for(auto shape:shapes)
            shape->save(out);
        file.close();
    }
}
void CenterWidget::openFile(QString fileName) { //读文件操作
    QFile file(fileName);
    if(file.open(QFile::ReadOnly)) { //只读方式打开
        QTextStream in(&file);
         int nums;
         in>>nums;
         int type;
         Shape *curShape;
         for(int i=0;i<nums;++i){
         in>>type;
         switch(type){
         case 0:
         curShape=Line::read(in);
         break;
         case 1:
         curShape=Ellipse::read(in);
         break;
         case 2:
         curShape=Rectangle::read(in);
         break;
         case 3:
             curShape=Point::read(in);
         }
         shapes.append(curShape);
         }
        file.close();
    }
}
void CenterWidget::setCurrentColor(const QColor &color){
    currentColor=color;
}
void CenterWidget::undo(){
    if(shapes.empty())
        return;
    Shape* temp=shapes.top();
    shapes.pop();
    waitingShapes.push(temp);
    update();
}
void CenterWidget::redo(){
    if(waitingShapes.empty())
        return;
    Shape* temp=waitingShapes.top();
    waitingShapes.pop();
    shapes.push(temp);
    update();
}

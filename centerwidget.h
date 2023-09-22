#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QList>
#include <QPoint>
#include <QRect>
#include <QMouseEvent>
#include <QLabel>
#include <QStack>
#include "line.h"
#include "ellipse.h"
#include "rectangle.h"
#include "point.h"
class CenterWidget : public QWidget
{
    Q_OBJECT
public:
    ~CenterWidget();
    explicit CenterWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void setDrawType(int type);
    void newDrawing();
     void openDrawing();
     void saveDrawing();
     void undo();
     void redo();
    bool getModifiedFlag(); //获取文档修改状态
signals:

public slots:
    void setCurrentColor(const QColor& color);
    void setLineWidth(int lw);
private:
    //QList<Shape*>shapes;
    QStack<Shape*>shapes;
    QStack<Shape*>waitingShapes;
    QPoint p1,p2; //绘图过程的临时起点坐标和终点坐标
    int drawType; //当前绘图类型，0-直线，1-椭圆，2-矩形,3-点
    QColor currentColor;
    int lineWidth;
    bool beginDraw;
    QLabel *mousePosLabel;
    bool isModified; //标识文档是否发生了修改
     QString fileName; //文件名，新建后为空
     void saveFile(QString fileName); //写文件的操作
     void openFile(QString fileName); //读文件的操作

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // CENTERWIDGET_H

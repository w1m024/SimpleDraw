#include "line.h"

Line::Line(QPoint p1,QPoint p2,QColor c,int lineWidth):
    Shape(c,lineWidth),point1(p1),point2(p2) {
}
QPoint Line::p1()const {
    return point1;
}
QPoint Line::p2()const {
    return point2;
}
void Line::draw(QPainter *p) {
    QPen pen(color,lineWidth,Qt::SolidLine);
    p->setPen(pen);
    p->drawLine(point1,point2); //绘制线条
}
void Line::save(QTextStream &out) {
    out<<"0 "<<p1().x()<<" "<<p1().y()<<" "
       <<p2().x()<<" "<<p2().y()
       <<" "<<color.red()<<" "<<color.green()<<" "<<color.blue()
      <<" "<<lineWidth<<endl;
}
Shape* Line::read(QTextStream &in) {
    int x1,y1,x2,y2,r,g,b,lw;
    in>>x1>>y1>>x2>>y2>>r>>g>>b>>lw;
    return new Line(QPoint(x1,y1),QPoint(x2,y2),QColor(r,g,b),lw);
}

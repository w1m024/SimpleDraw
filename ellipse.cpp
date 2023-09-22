#include "ellipse.h"
#include <QDebug>
#include <QColor>
Ellipse::Ellipse(QPoint p1,QPoint p2,QColor c,int lineWidth):
    Shape(c,lineWidth),point1(p1),point2(p2) {
}
QPoint Ellipse::topLeft()const {
    return point1;
}
QPoint Ellipse::bottomRight()const {
    return point2;
}
void Ellipse::draw(QPainter *p) {
    QPen pen(color,lineWidth,Qt::SolidLine);
    p->setPen(pen);
    p->drawEllipse(QRect(point1,point2));
}
void Ellipse::save(QTextStream &out) {
    out<<"1 "<<topLeft().x()<<" "<<topLeft().y()<<" "
       <<bottomRight().x()<<" "<<bottomRight().y()
      <<" "<<color.red()<<" "<<color.green()<<" "<<color.blue()
     <<" "<<lineWidth<<endl;
}
Shape* Ellipse::read(QTextStream &in) {
    int x1,y1,x2,y2,r,g,b,lw;
    in>>x1>>y1>>x2>>y2>>r>>g>>b>>lw;
    return new Ellipse(QPoint(x1,y1),QPoint(x2,y2),QColor(r,g,b),lw);
}

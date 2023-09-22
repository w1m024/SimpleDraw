#include "rectangle.h"
#include <QDebug>
Rectangle::Rectangle(QPoint p1,QPoint p2,QColor c,int lineWidth):
    Shape(c,lineWidth),point1(p1),point2(p2) {
    qDebug()<<lineWidth;
}
QPoint Rectangle::topLeft()const {
    return point1;
}
QPoint Rectangle::bottomRight()const {
    return point2;
}
void Rectangle::draw(QPainter *p) {
    QPen pen(color,lineWidth,Qt::SolidLine);
    qDebug()<<lineWidth;
    p->setPen(pen);
    p->drawRect(QRect(point1,point2));
}
void Rectangle::save(QTextStream &out) {
    out<<"2 "<<topLeft().x()<<" "<<topLeft().y()<<" "
       <<bottomRight().x()<<" "<<bottomRight().y()
      <<" "<<color.red()<<" "<<color.green()<<" "<<color.blue()
     <<" "<<lineWidth<<endl;
}
Shape* Rectangle::read(QTextStream &in) {
    int x1,y1,x2,y2,r,g,b,lw;
    in>>x1>>y1>>x2>>y2>>r>>g>>b>>lw;
    return new Rectangle(QPoint(x1,y1),QPoint(x2,y2),QColor(r,g,b),lw);
}

#include "point.h"
#include <QDebug>
Point::Point(QPoint p,QColor c,int lineWidth):
Shape(c,lineWidth),point(p)
{
}
QPoint Point::p() const{
    return point;
}

void Point::draw(QPainter *p){
    QPen pen(color,lineWidth,Qt::SolidLine);
    qDebug()<<point.x()<<" "<<point.y();
    p->setPen(pen);
    p->drawPoint(point);
}
void Point::save(QTextStream &out){
    out<<"3 "<<p().x()<<" "<<p().y()
       <<" "<<color.red()<<" "<<color.green()<<" "<<color.blue()
      <<" "<<lineWidth<<endl;
}
Shape* Point::read(QTextStream &in){
    int x,y,r,g,b,lw;
    in>>x>>y>>r>>g>>b>>lw;
    return new Point(QPoint(x,y),QColor(r,g,b),lw);
}

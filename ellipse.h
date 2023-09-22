#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"
class Ellipse : public Shape
{
public:
 Ellipse(QPoint p1,QPoint p2,QColor c=Qt::black,int lineWidth=1);
 QPoint topLeft()const;
 QPoint bottomRight()const;
 virtual void draw(QPainter *p);
 virtual void save(QTextStream& out);
 static Shape* read(QTextStream& in);
private:
 QPoint point1;
 QPoint point2;
};

#endif // ELLIPSE_H

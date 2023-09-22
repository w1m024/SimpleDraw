#ifndef LINE_H
#define LINE_H
#include "shape.h"
#include <QPoint>
class Line : public Shape
{
public:
 Line(QPoint p1,QPoint p2,QColor c=Qt::black,int lineWidth=1);
 QPoint p1()const;
 QPoint p2()const;
 virtual void draw(QPainter *p);
 virtual void save(QTextStream& out);
 static Shape* read(QTextStream& in);
private:
 QPoint point1;
 QPoint point2;

};

#endif // LINE_H

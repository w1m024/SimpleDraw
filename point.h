#ifndef POINT_H
#define POINT_H
#include "shape.h"
#include <QPoint>
class Point : public Shape
{
public:
    Point(QPoint p,QColor c=Qt::black,int lineWidth=10);
    QPoint p()const;
    virtual void draw(QPainter *p);
    virtual void save(QTextStream &out);
    static Shape*read(QTextStream& in);
private:
    QPoint point;
};

#endif // POINT_H

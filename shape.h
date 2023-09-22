#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>
#include <QPainter>
#include <QTextStream>
class Shape
{
public:
 Shape(QColor c,int lw);
 QColor getColor()const;
 void setColor(QColor c);
 //int getLineWidth()const;
 void setLineWidth(int lw);
 virtual void draw(QPainter *p)=0;
 virtual void save(QTextStream& s)=0;
protected:
 QColor color;
 int lineWidth;
};
#endif // SHAPE_H

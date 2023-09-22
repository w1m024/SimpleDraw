#include "shape.h"
Shape::Shape(QColor c,int lw):color(c),lineWidth(lw) {
}
void Shape::setColor(QColor c) {
    color=c;
}
void Shape::setLineWidth(int lw){
    lineWidth=lw;
}

QColor Shape::getColor()const {
    return color;
}

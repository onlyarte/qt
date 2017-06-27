#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{

    shape = Rect;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
}

void RenderArea::setColor(const QColor &color)
{
    this->color = color;
    update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    x0 = -1; x1 = -1;

    QPainter painter(this);

    for (int i = 0; i < figureShapes.size(); ++i) {
        painter.setPen(figureColors[i]);
        switch(figureShapes[i]){
        case 1:
            painter.drawRect(figures[i]);
            break;
        case 2:
            painter.drawEllipse(figures[i]);
            break;
        case 0:
            painter.drawLine(figures[i].bottomRight(), figures[i].topLeft());
        }
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RenderArea::mouseReleaseEvent(QMouseEvent* pe)
{
    if(x0 == -1){
        x0 = pe->x();
        y0 = pe->y();
    }
    else{
        x1 = pe->x();
        y1 = pe->y();

        QRect temp(x0, y0, x1-x0, y1-y0);
        figures.append(temp);
        figureColors.append(color);
        figureShapes.append(shape);
        update();
    }
}

void RenderArea::removeAll(){
    figures.clear();
    figureColors.clear();
    figureShapes.clear();
    update();
}

void RenderArea::save(QFile &file){
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << figures << figureColors << figureShapes;
}

void RenderArea::extract(QFile &file){
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> figures >> figureColors >> figureShapes;
}

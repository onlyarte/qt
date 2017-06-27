#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QtGui>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QList>
#include <QFile>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Line = 0, Rect = 1, Ellipse = 2 };

    RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void setShape(Shape shape);
    void setColor(const QColor &color);
    void removeAll();
    void save(QFile &file);
    void extract(QFile &file);

protected:
    void paintEvent(QPaintEvent *event) override;
    void paintRect(int x1, int y1, int w, int h);
    void paintOval(int x1, int y1, int w, int h);
    void paintLine(int x1, int y1, int x2, int y2);

    virtual void mouseReleaseEvent(QMouseEvent* pe);

private:
    QList<QRect> figures;
    QList<QColor> figureColors;
    QList<int> figureShapes;

    Shape shape;
    QColor color;
    QRect rect;
    int x0 = -1, y0 = -1, x1 = -1, y1 = -1;
};

#endif // RENDERAREA_H

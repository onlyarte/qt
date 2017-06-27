#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <qlabel.h>

class DragWidget : public QWidget
{
private:
    int lastPosY = 5;
    QList<QLabel *> list;

public:
    DragWidget(QWidget *parent = 0, bool secondFileSource = true);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGWIDGET_H

#ifndef WIDGETOBSERVER_H
#define WIDGETOBSERVER_H

#include <QtGui>
#include <QLabel>
#include <QMouseEvent>

class WidgetObserver : public QLabel {
public:
    WidgetObserver(QWidget* widget = 0);

protected:
    virtual void resizeEvent  (QResizeEvent* e);
    void dumpEvent (QResizeEvent* e, const QString& message);
};

#endif // WIDGETOBSERVER_H

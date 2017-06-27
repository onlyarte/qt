#include "WidgetObserver.h"

WidgetObserver::WidgetObserver(QWidget* widget) : QLabel(widget)
{
    setAlignment(Qt::AlignCenter);
}

void WidgetObserver::resizeEvent(QResizeEvent* e)
{
    dumpEvent(e, "");
}

void WidgetObserver::dumpEvent(QResizeEvent* e, const QString& message)
{
    setText(message + "\n x()=" + QString::number(e->size().width())
            + "\n y()=" + QString::number(e->size().height()) );
}

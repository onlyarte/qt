#include "widgetobserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetObserver w;
    w.show();

    w.resize(200, 200);

    return a.exec();
}

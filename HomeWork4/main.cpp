#include <QApplication>
#include <dragwidget.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(homework4);

    QApplication app(argc, argv);
    DragWidget window(0, false); // false to use words.txt
    window.show();

    DragWidget window2(0, true); // true to use words2.txt
    window2.show();

    return app.exec();
}

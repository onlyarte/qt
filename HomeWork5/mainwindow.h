#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <qstring.h>
#include <qfile.h>
#include <qfiledialog.h>

namespace Ui {
class MainWindow;
}

class RenderArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionColor_triggered();

    void on_actionAdd_rect_triggered();

    void on_actionAdd_oval_triggered();

    void on_actionAdd_line_triggered();

    void on_actionNew_triggered();

    void on_actionRemove_all_triggered();

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;

};

#endif // MAINWINDOW_H

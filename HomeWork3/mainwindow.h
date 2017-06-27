#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstring.h>
#include <qfile.h>
#include <qdebug.h>
#include <qfiledialog.h>
#include <QTextStream>
#include <qmessagebox.h>
#include <QDesktopServices>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString sourcePath;
    QString outPath;

private slots:
    void on_loadButton_released();
    void on_saveButton_released();
    void on_showOriginalButton_released();
    void on_ShowProcessedButton_released();
};

#endif // MAINWINDOW_H

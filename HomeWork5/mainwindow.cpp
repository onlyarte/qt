#include "renderarea.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    renderArea = new RenderArea;

    ui->verticalLayout->addWidget(renderArea);

    setWindowTitle(tr("Paint"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    renderArea->removeAll();
}

void MainWindow::on_actionOpen_triggered()
{
    QString sourcePath = QFileDialog::getOpenFileName(this,
            tr("Open File"), "",
            tr("Image (*.qimg);;All Files (*)"));

    if (sourcePath.isEmpty())
            return;

    QFile inFile(sourcePath);

    renderArea->extract(inFile);
}

void MainWindow::on_actionSave_triggered()
{
    QString outPath = QFileDialog::getSaveFileName(this,
            tr("Save Image"), "",
            tr("Image (*.qimg);;All Files (*)"));
    if (outPath.isEmpty())
            return;

    QFile outFile(outPath);

    renderArea->save(outFile);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAdd_rect_triggered()
{
    renderArea->setShape(RenderArea::Shape::Rect);
}

void MainWindow::on_actionAdd_oval_triggered()
{
    renderArea->setShape(RenderArea::Shape::Ellipse);
}

void MainWindow::on_actionAdd_line_triggered()
{
    renderArea->setShape(RenderArea::Shape::Line);
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white);
    renderArea->setColor(color);
}

void MainWindow::on_actionRemove_all_triggered()
{
    renderArea->removeAll();
}

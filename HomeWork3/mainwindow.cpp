#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_released()
{
    sourcePath = QFileDialog::getOpenFileName(this,
            tr("Open File"), "",
            tr("Text (*.txt);;All Files (*)"));
}

void MainWindow::on_saveButton_released()
{
    if(sourcePath.isEmpty()){
        QMessageBox::information(this, tr("Error"), tr("Please, select original file before processing!"));
        return;
    }
    outPath = QFileDialog::getSaveFileName(this,
            tr("Save Processed File"), "",
            tr("Text (*.txt);;All Files (*)"));
    if (outPath.isEmpty())
            return;


    QFile inFile(sourcePath);
    QFile outFile(outPath);

    if (inFile.open(QIODevice::ReadOnly)
            && outFile.open(QIODevice::WriteOnly)) {
        QTextStream inStream(&inFile);
        QTextStream outStream(&outFile);

        QChar ch;
        while (!inStream.atEnd()) {
            inStream >> ch;
            if(ch == QChar::Tabulation)
                outStream << ' ';
            else if (ch != '\n')
                outStream << ch;
        }
        inFile.close();
        outFile.close();
    }
}

void MainWindow::on_showOriginalButton_released()
{
    if(sourcePath.isEmpty()){
        QMessageBox::information(this, tr("Error"), tr("Please, select original file!"));
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(sourcePath));
}

void MainWindow::on_ShowProcessedButton_released()
{
    if(outPath.isEmpty()){
        QMessageBox::information(this, tr("Error"), tr("It seems no processings have been performed!"));
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(outPath));
}

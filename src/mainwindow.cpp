#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <io.h>
#include <Windows.h>
#include <string>


using namespace std;


char* toCharPtr(QString str) {
    QByteArray arr = str.toLocal8Bit();
    return arr.data();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GetCurrentDirectoryA(512, appDir);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_mainPyBrowse_clicked()
{
    mainPyPath = QFileDialog::getOpenFileName(this, "Open main.py", "C:/");
    ui->mainPyEdit->setText(mainPyPath);
}


void MainWindow::on_requirementsBtowse_clicked()
{
    requirementsPath = QFileDialog::getOpenFileName(this, "Open requirements.txt", "C:/");
    ui->requirementsEdit->setText(requirementsPath);
}


void MainWindow::on_run_clicked()
{
    if (!requirementsPath.isEmpty())
    {
        if (access(toCharPtr(requirementsPath), 0)) //Invalid requirements path
        {
            QMessageBox::information(this, "Invalid path", "Plese enter valid requirements path");
        }

        else
        {
            //If pip isn't installed run get-pip.py
            if (access(toCharPtr( QString(appDir) + QString("/python_embed/Scripts/pip.exe") ), 0))
            {
                system(toCharPtr( QString("\"\"") +
                                 QString(appDir) +
                                 QString("\\python_embed\\python\" \"") +
                                 QString(appDir) +
                                 QString("\\python_embed\\get-pip.py\"\"") ));
            }

            //Install packages from requirements
            system(toCharPtr( QString("\"\"") +
                             QString(appDir) +
                             QString("\\python_embed\\Scripts\\pip\" install -r \"") +
                             requirementsPath.replace("/", "\\") +
                             QString("\"\"") ));
        }
    }

    if (mainPyPath.isEmpty() || access(mainPyPath.toStdString().c_str(), 0)) //Invalid main.py path
    {
        QMessageBox::information(this, "Can't open file", "Enter correct path to python file");
    }

    else
    {
        //Run python file
        QString appendPath = QString(string( mainPyPath.toStdString().substr(0, mainPyPath.toStdString().rfind("/")) ).c_str()).replace("/", "\\");
        system(toCharPtr( QString("\"\"") +
                         QString(appDir) +
                         QString("\\python_embed\\python\" \"") +
                         QString(appDir) +
                         QString("\\runPython.py\" \"") +
                         appendPath +
                         QString("\" \"") +
                         mainPyPath.replace("/", "\\") +
                         QString("\"\"") ));
    }
}


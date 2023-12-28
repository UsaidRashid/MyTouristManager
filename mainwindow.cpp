#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/new/prefix1/resources/touristimg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    ui->pushButton->setStyleSheet("QPushButton { border: 2px solid #555; font: 9pt 'Wide Latin'; background: transparent; color: black; } QPushButton:hover { background-color: green; }");
    ui->pushButton_2->setStyleSheet("QPushButton { border: 2px solid #555; font: 7pt 'Wide Latin'; background: transparent; color: black; } QPushButton:hover { background-color: green; }");
    ui->pushButton_3->setStyleSheet("QPushButton { border: 2px solid #555; font: 9pt 'Wide Latin'; background: transparent; color: black; } QPushButton:hover { background-color: green; }");
    ui->pushButton_4->setStyleSheet("QPushButton { border: 2px solid #555; font: 9pt 'Wide Latin'; background: transparent; color: black; } QPushButton:hover { background-color: green; }");
    ptrAddPackage = new AddPackage();
    ptrRegisterTourist = new RegisterTourist();
    ptrFindPackage = new FindPackage();
    ptrFindTourist = new FindTourist();
    ui->textEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{

    delete ptrAddPackage;
    delete ptrRegisterTourist;
    delete ptrFindPackage;
    delete ptrFindTourist;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ptrAddPackage->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    ptrRegisterTourist->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    ptrFindPackage->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    ptrFindTourist->show();
}


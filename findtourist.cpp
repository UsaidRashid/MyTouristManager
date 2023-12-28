#include "findtourist.h"
#include "ui_findtourist.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>

FindTourist::FindTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindTourist),
    model(nullptr)  // Initialize model to nullptr in the member initialization list
{
    ui->setupUi(this);
    QPixmap bkgnd(":/new/prefix1/resources/touristimg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    ui->btnFind->setStyleSheet("QPushButton { border: 2px solid #555; font: 9pt 'Wide Latin'; background: transparent; color: black; } QPushButton:hover { background-color: green; }");
}

FindTourist::~FindTourist()
{
    delete ui;
    // Remember to clean up the model when the class is destroyed
    delete model;
}

void FindTourist::on_btnFind_clicked()
{
    QString touristName = ui->txtTouristName->text();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("E:/C++/QT/Database/MyToursitManager.db");

    if (!database.open()) {
        qDebug() << "Unable to open database";
    }

    QSqlQuery query(database);

    query.prepare("SELECT * FROM Tourist WHERE FirstName LIKE '%" + touristName + "%'");
    query.exec();
    qDebug() << "Last error" << query.lastError();

    // Create a QSqlQueryModel outside of the transaction to avoid potential issues
    if (model == nullptr) {
        model = new QSqlQueryModel();
    }

    model->setQuery(std::move(query));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 150);
    ui->tableView->setColumnWidth(2, 150);
    ui->tableView->setColumnWidth(3, 150);
    ui->tableView->setColumnWidth(4, 200);
    ui->tableView->setColumnWidth(5, 200);
    ui->tableView->setColumnWidth(6, 200);
    ui->tableView->setColumnWidth(7, 200);

    database.close();
}



/*#include "findtourist.h"
#include "ui_findtourist.h"
#include<QString>

FindTourist::FindTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindTourist)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/new/prefix1/resources/touristimg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

FindTourist::~FindTourist()
{
    delete ui;
}

void FindTourist::on_btnFind_clicked()
{
    QString touristName = ui->txtTouristName->text();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("E:/QT/Database/MyToursitManager.db");

    if(!database.open()){
        qDebug()<<"Unable to open database";
    }

    QSqlQuery query(database);

    query.prepare("select * from Tourist where FirstName like '%" + touristName +  "%'");
    query.exec();
    qDebug()<<"Last error"<<query.lastError();

    if(model==NULL){
        model = new QSqlQueryModel();
    }

    model->setQuery(std::move(query));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 200);

    database.close();
}
*/

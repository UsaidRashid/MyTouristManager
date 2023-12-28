#include "findpackage.h"
#include "ui_findpackage.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

FindPackage::FindPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPackage)
{
    ui->setupUi(this);
    model = nullptr;
    ui->btnFindPackage->setStyleSheet("QPushButton { border: 2px solid #555; font: 9pt 'Wide Latin'; background: transparent; color: black; } QPushButton:hover { background-color: green; }");
}

FindPackage::~FindPackage()
{
    delete ui;
}

void FindPackage::on_btnFindPackage_clicked()
{
    QString packageName = ui->txtPackageName->text();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("E:/C++/QT/Database/MyToursitManager.db");

    if (QFile::exists("E:/C++/QT/Database/MyToursitManager.db")) {
        qDebug() << "Database File EXISTS";
    } else {
        qDebug() << "Database File doesn't exist";
        return;
    }

    // Use the retry function to open the database
    // openDatabaseWithRetry(database);

    if (!database.open()) {
        qDebug() << "Unable to open database: " << database.lastError().text();
        return;
    } else {
        qDebug() << "Database opened successfully";
    }

    QSqlQuery query(database);

    query.prepare("SELECT * FROM package WHERE PackageName LIKE '%" + packageName + "%'");
    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        // Handle the error as needed
    }

    qDebug() << "Last error: " << database.lastError();

    // Create a QSqlQueryModel outside of the transaction to avoid potential issues
    if (model == nullptr) {
        model = new QSqlQueryModel();
    }

    model->setQuery(std::move(query));

    // Set the model for your tableView
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 100);
    ui->tableView->setColumnWidth(1, 250);
    ui->tableView->setColumnWidth(2, 400);
    ui->tableView->setColumnWidth(3, 200);

    // Close the database connection
    database.close();
}



/*#include "findpackage.h"
#include "ui_findpackage.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QThread>

FindPackage::FindPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPackage)
{
    ui->setupUi(this);
    model=nullptr;
}

FindPackage::~FindPackage()
{
    delete ui;
}

void FindPackage::openDatabaseWithRetry(QSqlDatabase& database)
{
    int retryCount = 0;
    const int maxRetries = 5;
    const int retryIntervalMs = 1000; // Adjust as needed

    while (retryCount < maxRetries) {
        if (database.open()) {
            qDebug() << "Database opened successfully.";
            break;  // Database opened successfully, exit the loop
        } else {
            qDebug() << "Error opening database: " << database.lastError().text();

            // Implement a delay before retrying
            QThread::msleep(retryIntervalMs);
        }
        retryCount++;
    }

    if (retryCount >= maxRetries) {
        qDebug() << "Exceeded maximum retry attempts. Unable to open database.";
    }
}*

void FindPackage::on_btnFindPackage_clicked()
{
    QString packageName = ui->txtPackageName->text();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("E:/QT/Database/MyToursitManager.db");

    if(QFile::exists("E:/QT/Database/MyToursitManager.db")){
        qDebug()<<"Database File EXISTS";
    }
    else{
        qDebug()<<"Database File doesnt exists";
        return;
    }

    // Use the retry function to open the database
   // openDatabaseWithRetry(database);

    if (!database.open()) {
        qDebug() << "Unable to open database.";
        return;
    }else{
        qDebug()<<"Database opened successfully";
    }

    QSqlQuery query(database);

    //if (database.transaction()) {
    query.prepare("select * from package where PackageName like '%" +packageName + "%' ");
    query.exec();
       /* if (query.exec()) {
            // Commit the transaction if the query executed successfully
            if (database.commit()) {
                qDebug() << "Transaction committed successfully.";
            } else {
                qDebug() << "Error committing transaction: " << database.lastError().text();
            }
        } else {
            qDebug() << "Error executing query: " << query.lastError().text();
            // Rollback the transaction in case of an error
            database.rollback();
        }*

    qDebug()<<"Last error"<<database.lastError();

        // Create a QSqlQueryModel outside of the transaction to avoid potential issues
        if (model == nullptr) {
            model = new QSqlQueryModel();
        }

        model->setQuery(std::move(query));

        // Set the model for your tableView
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0, 200);
        ui->tableView->setColumnWidth(1, 200);
        ui->tableView->setColumnWidth(2, 200);


        // Close the database connection
        database.close();
   // } else {
     //   qDebug() << "Error starting transaction: " << database.lastError().text();
    //}
}
*/

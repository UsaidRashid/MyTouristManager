#include "addpackage.h"
#include "ui_addpackage.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

AddPackage::AddPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPackage)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/new/prefix1/resources/touristimg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    ui->btnSave->setStyleSheet("QPushButton { border: 2px solid #555; font: 9pt 'Wide Latin'; background: transparent; color: black; } QPushButton:hover { background-color: green; }");
}

AddPackage::~AddPackage()
{
    delete ui;
}

void AddPackage::on_btnSave_clicked()
{
    QString packageName = ui->txtPackageName->text();
    QString packageDescription = ui->txtDescription->toPlainText();
    QString amount = ui->txtAmount->text();
    qDebug() << "Package Name" << packageName << "Package Description" << packageDescription << "Package Amount" << amount;

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("E:/C++/QT/Database/MyToursitManager.db");

    if (!QFile::exists("E:/C++/QT/Database/MyToursitManager.db")) {
        qDebug() << "Database File doesn't exist";
        return;
    }

    if (!database.open()) {
        qDebug() << "Unable to open database: " << database.lastError().text();
        return;
    }
    qDebug() << "Database opened successfully";

    QSqlQuery query(database);

    // Check if the query is prepared successfully
    if (!query.prepare("INSERT INTO package (PackageName, PackageDescription, Amount) VALUES (?, ?, ?)")) {
        qDebug() << "Error preparing query: " << query.lastError().text();
        // Handle the error as needed
        database.close();
        return;
    }

    // Bind values to placeholders
    query.bindValue(0, packageName);
    query.bindValue(1, packageDescription);
    query.bindValue(2, amount);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        // Handle the error as needed
    } else {
        qDebug() << "Package added successfully";
    }

    // Close the database connection
    database.close();
}




/*#include "addpackage.h"
#include "ui_addpackage.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QThread>

AddPackage::AddPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPackage)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/new/prefix1/resources/touristimg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

AddPackage::~AddPackage()
{
    delete ui;
}
/*
void AddPackage::openDatabaseWithRetry(QSqlDatabase& database)
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
}

*
void AddPackage::on_btnSave_clicked()
{
    QString packageName = ui->txtPackageName->text();
    QString packageDescription = ui->txtDescription->toPlainText();
    QString amount = ui->txtAmount->text();
    qDebug()<<"Package Name"<<packageName<<"Package Description"<<packageDescription<<"Package Amount"<<amount;

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
    //openDatabaseWithRetry(database);

    if (!database.open()) {
        qDebug() << "Unable to open database."<< database.lastError().text();;
        return;
    }
    else{
        qDebug()<<"Database opened successfully";
    }

    QSqlQuery query(database);

    //if (database.transaction()) {
        query.prepare("insert into package (PackageName, PackageDescription, Amount) values('"+packageName + "' , '"+packageDescription+"','"+amount+"')");
    query.exec();
      /*  if (query.exec()) {
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
    qDebug()<<"Last error:"<<database.lastError();
        // Close the database connection
        database.close();
    //} else {
      //  qDebug() << "Error starting transaction: " << database.lastError().text();
    //}
}

*/

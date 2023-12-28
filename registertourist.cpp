#include "registertourist.h"
#include "ui_registertourist.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

RegisterTourist::RegisterTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterTourist)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/new/prefix1/resources/touristimg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    ui->btnSave->setStyleSheet("QPushButton { border: 2px solid #555; font: 9pt 'Wide Latin'; background: transparent; color: black; } QPushButton:hover { background-color: green; }");
}

RegisterTourist::~RegisterTourist()
{
    delete ui;
}

/*void RegisterTourist::openDatabaseWithRetry(QSqlDatabase& database)
{
    // (Your retry logic, if needed)
}*/

void RegisterTourist::on_btnSave_clicked()
{
    QString firstName = ui->txtFirstName->text();
    QString middleName = ui->txtMiddleName->text();
    QString lastName = ui->txtLastName->text();
    QString passportNo = ui->txtPassportNo->text();
    QString contactNo = ui->txtContactNo->text();
    QString permanentAddress = ui->txtPermanentAddress->toPlainText();
    QString packageName = ui->cmbChoosePackage->currentText();

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

    //if (database.transaction()) {
    query.prepare("INSERT INTO Tourist (FirstName, MiddleName, LastName, PassportNo, ContactNo, PermanentAddress, PackageName)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, firstName);
    query.bindValue(1, middleName);
    query.bindValue(2, lastName);
    query.bindValue(3, passportNo);
    query.bindValue(4, contactNo);
    query.bindValue(5, permanentAddress);
    query.bindValue(6, packageName);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        // Handle the error as needed
    } else {
        qDebug() << "Tourist registered successfully";
    }

    // Close the database connection
    database.close();
    //} else {
    //  qDebug() << "Error starting transaction: " << database.lastError().text();
    //}
}


/*#include "registertourist.h"
#include "ui_registertourist.h"
#include<QString>
#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QThread>

RegisterTourist::RegisterTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterTourist)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/new/prefix1/resources/touristimg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

RegisterTourist::~RegisterTourist()
{
    delete ui;
}

/*void RegisterTourist::openDatabaseWithRetry(QSqlDatabase& database)
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

void RegisterTourist::on_btnSave_clicked()
{
    QString firstName = ui->txtFirstName->text();
    QString middleName = ui->txtMiddleName->text();
    QString lastName= ui->txtLastName->text();
    QString passportNo = ui->txtPassportNo->text();
    QString contactNo = ui->txtContactNo->text();
    QString permanentAddress = ui->txtPermanentAddress->toPlainText();
    QString packageName = ui->cmbChoosePackage->currentText();

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
    }
    else{
        qDebug()<<"Database opened successfully";
    }

    QSqlQuery query(database);

    //if (database.transaction()) {
        query.prepare("insert into Tourist (FirstName, MiddleName, LastName, PassportNo, ContactNo, PermanentAddress, PackageName)"
                      "values('" + firstName + "','" + middleName + "' , '" + lastName + "' , '" + passportNo + "' , '" + contactNo + "' , '" + permanentAddress + "', '" + packageName + "')");
    query.exec();
        qDebug()<<"Last error:"<<database.lastError();

        /*if (query.exec()) {
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

        // Close the database connection
        database.close();
    //} else {
      //  qDebug() << "Error starting transaction: " << database.lastError().text();
    //}
}
*/

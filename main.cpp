#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Create the database connection if it doesn't exist.
  //  if (!QSqlDatabase::contains("qt_sql_default_connection")) {
    //    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
      //  db.setDatabaseName("your_database_file_name.sqlite"); // Set your database file name here.
    //}

/*    AddPackage addPackage;
    RegisterTourist registerTourist;
    FindPackage findPackage;

    // Connect the signal from AddPackage/RegisterTourist to the slot in FindPackage
    QObject::connect(&addPackage, SIGNAL(databaseReady()), &findPackage, SLOT(handleDatabaseReady()));
    QObject::connect(&registerTourist, SIGNAL(databaseReady()), &findPackage, SLOT(handleDatabaseReady()));*/
    return a.exec();
}

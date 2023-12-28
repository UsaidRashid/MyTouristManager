#ifndef FINDPACKAGE_H
#define FINDPACKAGE_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class FindPackage;
}

class FindPackage : public QDialog
{
    Q_OBJECT

public:
    explicit FindPackage(QWidget *parent = nullptr);
    ~FindPackage();

private slots:
    void on_btnFindPackage_clicked();

private:
    Ui::FindPackage *ui;
    QSqlQueryModel* model;
    // void openDatabaseWithRetry(QSqlDatabase& database);
};

#endif // FINDPACKAGE_H

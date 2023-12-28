#ifndef REGISTERTOURIST_H
#define REGISTERTOURIST_H

#include <QDialog>

namespace Ui {
class RegisterTourist;
}

class RegisterTourist : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterTourist(QWidget *parent = nullptr);
    ~RegisterTourist();

private slots:
    void on_btnSave_clicked();

private:
    Ui::RegisterTourist *ui;
    // void openDatabaseWithRetry(QSqlDatabase& database);
};

#endif // REGISTERTOURIST_H

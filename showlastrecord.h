#ifndef SHOWLASTRECORD_H
#define SHOWLASTRECORD_H

#include <QDialog>
#include <db.h>
#include <QDebug>

namespace Ui {
class showLastRecord;
}

class showLastRecord : public QDialog
{
    Q_OBJECT

public:
    explicit showLastRecord(db* myDB,QWidget *parent = 0);
    ~showLastRecord();

private:
    Ui::showLastRecord *ui;

public:
    db* myDB1;

public slots:
    void changeEtalon(QString name);
private slots:
    void on_pushButton_clicked();
    void setTableItem(QString name, QString etalon, QList<detail> detailList);
    void on_pushButton_2_clicked();
    void on_exportButton_clicked();
};

#endif // SHOWLASTRECORD_H

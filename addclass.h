#ifndef ADDCLASS_H
#define ADDCLASS_H

#include <QDialog>
#include <db.h>

namespace Ui {
class addClass;
}

class addClass : public QDialog
{
    Q_OBJECT

public:
    explicit addClass(db* myDB,QWidget *parent = 0);
    ~addClass();

private slots:
    void on_flushButton_clicked();
    void on_delButton_clicked();
    void on_addButton_clicked();
private:
    Ui::addClass *ui;

public:
    db* myDB1;

public slots:
    void changeEtalon(QString name);
signals:
    void changeNames();
};

#endif // ADDCLASS_H

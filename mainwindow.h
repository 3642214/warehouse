#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <db.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void changeEtalon(QString name);
    void addRow(QList<detail> d);
    void clearRow();
    void setCulReadOnlay();

public:
    db* myDB;
private slots:
    void on_serachButton_clicked();
    void on_addButton_clicked();
    void on_delButton_clicked();
    void on_commitButton_clicked();
    void on_addClassButton_clicked();
    void flushNames();
    void on_exportButton_clicked();
};

#endif // MAINWINDOW_H

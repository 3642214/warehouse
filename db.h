#ifndef DB_H
#define DB_H

#include <QString>
#include <QList>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

#define qdebugDetail     qDebug()<<myDetail.id<<myDetail.date<<myDetail.number<<myDetail.summary<<myDetail.income<<myDetail.lend_long<<myDetail.lend_sort<<myDetail.loss<<myDetail.lost<<myDetail.t_lend_long<<myDetail.t_lend_sort<<myDetail.t_new<<myDetail.t_old<<myDetail.t_total<<myDetail.total

typedef struct
{
    int id;
    int classID;
    QString date;
    int number;
    int summary;
    int income;
    int lend_long;
    int lend_sort;
    int loss;
    int lost;
    int t_lend_long;
    int t_lend_sort;
    int t_new;
    int t_old;
    int t_total;
    int total;

} detail;

class db
{
private:
    QSqlDatabase ddb;
public:
    db();
    int setClass(QString name,QString etalon);
    bool delClass(QString name,QString etalon);
    int getClassID(QString name,QString etalon);
    QList<QString> getAllName();
    bool setDetail(detail myDetail);
    bool updateDetail(detail myDetail);
    bool delDetail(int ID);
    QList<QString> getEtalon(QString name);
    QList<detail> getDetails(int classID);
};

#endif // DB_H

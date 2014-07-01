#ifndef DB_H
#define DB_H

#include <QList>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QString>

#define qdebugDetail     qDebug()<<myDetail.id<<myDetail.date<<myDetail.number<<myDetail.summary<<myDetail.income<<myDetail.lend_long<<myDetail.lend_sort<<myDetail.loss<<myDetail.lost<<myDetail.t_lend_long<<myDetail.t_lend_sort<<myDetail.t_new<<myDetail.t_old<<myDetail.t_total<<myDetail.total

#define logError QString errorCode =  sql_q.lastError().text();\
    qDebug()<<__FUNCTION__<<" error :"<<errorCode;\
    QMessageBox::critical(0, QObject::tr("错误"),"错误名>>" + errorCode + " << ,操作数据库失败!!!")

#define logOK qDebug()<<__FUNCTION__<<" ok"

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
    void initDB();
    int setClass(QString name,QString etalon);
    bool updateClass(int classID,QString name,QString etalon);
    bool delClass(QString name,QString etalon);
    int getClassID(QString name,QString etalon);
    QList<QString> getAllName();
    bool setDetail(detail myDetail);
    bool updateDetail(detail myDetail);
    bool delDetail(int ID);
    bool delDetailByClassID(int classID);
    QList<QString> getEtalon(QString name);
    QList<detail> getDetails(int classID);
    QList<detail> getDetailsByName(QString name);
    QList<detail> getDetailsByEtalon(QString etalon);
    QList<detail> getAllDetails();
};

#endif // DB_H

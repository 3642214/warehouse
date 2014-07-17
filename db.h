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

#define qdebugDetail     //qDebug()<<"get details :"; \
                         qDebug()<<myDetail.id<<myDetail.date<<myDetail.number<<myDetail.summary<<myDetail.income<<myDetail.lend_long<<myDetail.lend_sort<<myDetail.loss<<myDetail.lost<<myDetail.t_lend_long<<myDetail.t_lend_sort<<myDetail.t_new<<myDetail.t_old<<myDetail.t_total<<myDetail.total

#define SETDETAIL {    \
                    sql_q.value(0).toInt(), \
                    sql_q.value(1).toInt(), \
                    sql_q.value(2).toString(),  \
                    sql_q.value(3).toString(),  \
                    sql_q.value(4).toString(),  \
                    sql_q.value(5).toInt(), \
                    sql_q.value(6).toInt(), \
                    sql_q.value(7).toInt(), \
                    sql_q.value(8).toInt(), \
                    sql_q.value(9).toInt(), \
                    sql_q.value(10).toInt(),    \
                    sql_q.value(11).toInt(),    \
                    sql_q.value(12).toInt(),    \
                    sql_q.value(13).toInt(),    \
                    sql_q.value(14).toInt(),    \
                    sql_q.value(15).toInt() \
                    }

#define logError QString errorCode =  sql_q.lastError().text();\
    qDebug()<<__FUNCTION__<<" error :"<<errorCode;\
    QMessageBox::critical(0, QObject::tr("错误"),"错误名>>" + errorCode + " << ,操作数据库失败!!!")

#define logOK //qDebug()<<__FUNCTION__<<" ok"

typedef struct
{
    int id;
    int classID;
    QString date;   //日期
    QString number; //凭证单号
    QString summary;    //摘要
    int income;     //收入数量
    int lend_long;  //发出(长期借)
    int lend_sort;  //发出(流动借)
    int loss;       //减少(损耗)
    int lost;       //减少(遗失)
    int t_lend_long;    //结存(常借)
    int t_lend_sort;    //结存(流借)
    int t_new;      //库存(新)
    int t_old;      //库存(旧)
    int t_total;    //库存合计
    int total;      //合计

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
    QList<detail> getLastDetail(int classID);
};

#endif // DB_H

#include "db.h"

db::db()
{
    //    ddb = QSqlDatabase::addDatabase(QSqlDatabase::driver())
    ddb = QSqlDatabase::addDatabase("QSQLITE");
    ddb.setDatabaseName("warehouse.db");
    if(!ddb.open())
    {
        QMessageBox::critical(0, QObject::tr("错误"),QObject::tr("无法打开数据库文件。。。！！！"));
        exit(0);
    }

}

void db::initDB()
{
    QSqlQuery sql_q;
    sql_q.exec("CREATE TABLE class (name TEXT,etalon TEXT)");
    sql_q.exec("CREATE TABLE detail (id INTEGER  PRIMARY KEY AUTOINCREMENT DEFAULT NULL,classID INTEGER DEFAULT NULL,date Date DEFAULT NULL,number INTEGER DEFAULT NULL,summary INTEGER DEFAULT NULL,income INTEGER DEFAULT NULL,lend_long INTEGER DEFAULT NULL,lend_sort INTEGER DEFAULT NULL,loss INTEGER DEFAULT NULL,lost INTEGER DEFAULT NULL,t_lend_long INTEGER DEFAULT NULL,t_lend_sort INTEGER  DEFAULT NULL,t_new INTEGER  DEFAULT NULL,t_old INTEGER DEFAULT NULL,t_total INTEGER  DEFAULT NULL,total INTEGER DEFAULT NULL)");
}

int db::setClass(QString name, QString etalon)
{
    int id = getClassID(name,etalon);
    if(id <= 0)
    {
        QSqlQuery sql_q;
        QString setClass_sql = "insert into class (name,etalon) VALUES (:name,:etalon)";
        sql_q.prepare(setClass_sql);
        sql_q.addBindValue(name);
        sql_q.addBindValue(etalon);
        if(!sql_q.exec())
        {
            logError;
        }
        else
        {
            logOK;
        }
        return getClassID(name,etalon);
    }
    else {
        return id;
    }

}

bool db::delClass(QString name, QString etalon)
{
    QSqlQuery sql_q;
    QString delClass_sql = "delete from class where name = :name and etalon = :etalon";
    sql_q.prepare(delClass_sql);
    sql_q.bindValue(":name",name);
    sql_q.bindValue(":etalon",etalon);
    if(!sql_q.exec())
    {
        logError;
        return false;
    }
    else
    {
        logOK;
        return true;
    }

}

int db::getClassID(QString name, QString etalon)
{
    QSqlQuery sql_q;
    QString getId_sql = "select rowid from class where name = :name and etalon = :etalon";
    sql_q.prepare(getId_sql);
    sql_q.bindValue(":name",name);
    sql_q.bindValue(":etalon",etalon);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    int i = 0;
    while (sql_q.next()) {
        i = sql_q.value(0).toInt();
    }
    return i;
}

QList<QString> db::getAllName()
{
    QList<QString> names;
    QSqlQuery sql_q;
    QString getEtalon_sql = "select name from class";
    sql_q.prepare(getEtalon_sql);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    while (sql_q.next()) {
        names<<sql_q.value(0).toString();
        //        qDebug()<<sql_q.value(0).toString();
    }
    return names.toSet().toList();
}

bool db::setDetail(detail myDetail)
{
    qDebug()<<"set detail :";
    qdebugDetail;
    QSqlQuery sql_q;
    QString setDetail_sql = "insert into detail (id,classID,date,number,summary,income,lend_long,lend_sort,loss,lost,t_lend_long,t_lend_sort,t_new,t_old,t_total,total) VALUES (:id,:classID,:date,:number,:summary,:income,:lend_long,:lend_sort,:loss,:lost,:t_lend_long,:t_lend_sort,:t_new,:t_old,:t_total,:total)";
    sql_q.prepare(setDetail_sql);
    //    sql_q.bindValue(":id",myDetail.id);
    sql_q.bindValue(":classID",myDetail.classID);
    sql_q.bindValue(":date",myDetail.date);
    sql_q.bindValue(":number",myDetail.number);
    sql_q.bindValue(":summary",myDetail.summary);
    sql_q.bindValue(":income",myDetail.income);
    sql_q.bindValue(":lend_long",myDetail.lend_long);
    sql_q.bindValue(":lend_sort",myDetail.lend_sort);
    sql_q.bindValue(":loss",myDetail.loss);
    sql_q.bindValue(":lost",myDetail.lost);
    sql_q.bindValue(":t_lend_long",myDetail.t_lend_long);
    sql_q.bindValue(":t_lend_sort",myDetail.t_lend_sort);
    sql_q.bindValue(":t_new",myDetail.t_new);
    sql_q.bindValue(":t_old",myDetail.t_old);
    sql_q.bindValue(":t_total",myDetail.t_total);
    sql_q.bindValue(":total",myDetail.total);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    return true;
}

bool db::updateDetail(detail myDetail)
{
    qDebug()<<"update detail :";
    qdebugDetail;
    QSqlQuery sql_q;
    QString setDetail_sql = "update detail set classID = :classID,date = :date,number = :number,summary = :summary ,income = :income,lend_long = :lend_long,lend_sort = :lend_sort,loss = :loss,lost = :lost,t_lend_long = :t_lend_long,t_lend_sort = :t_lend_sort,t_new = :t_new,t_old = :t_old,t_total = :t_total,total = :total where id = :id";
    sql_q.prepare(setDetail_sql);
    sql_q.bindValue(":id",myDetail.id);
    sql_q.bindValue(":classID",myDetail.classID);
    sql_q.bindValue(":date",myDetail.date);
    sql_q.bindValue(":number",myDetail.number);
    sql_q.bindValue(":summary",myDetail.summary);
    sql_q.bindValue(":income",myDetail.income);
    sql_q.bindValue(":lend_long",myDetail.lend_long);
    sql_q.bindValue(":lend_sort",myDetail.lend_sort);
    sql_q.bindValue(":loss",myDetail.loss);
    sql_q.bindValue(":lost",myDetail.lost);
    sql_q.bindValue(":t_lend_long",myDetail.t_lend_long);
    sql_q.bindValue(":t_lend_sort",myDetail.t_lend_sort);
    sql_q.bindValue(":t_new",myDetail.t_new);
    sql_q.bindValue(":t_old",myDetail.t_old);
    sql_q.bindValue(":t_total",myDetail.t_total);
    sql_q.bindValue(":total",myDetail.total);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    return true;
}

bool db::delDetail(int ID)
{
    QSqlQuery sql_q;
    QString delDetail_sql = "delete from detail where id = :id";
    sql_q.prepare(delDetail_sql);
    sql_q.bindValue(":id",ID);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    return true;
}

QList<QString> db::getEtalon(QString name)
{
    QList<QString> etalons;
    QSqlQuery sql_q;
    QString getEtalon_sql = "select etalon from class where name = ?";
    sql_q.prepare(getEtalon_sql);
    sql_q.addBindValue(name);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    while (sql_q.next()) {
        etalons<<sql_q.value(0).toString();
        //        qDebug()<<sql_q.value(0).toString();
    }
    return etalons;
}

QList<detail> db::getDetails(int classID)
{
    QList<detail> details;
    QSqlQuery sql_q;
    QString setDetail_sql = "select * from detail where classID = ?";
    sql_q.prepare(setDetail_sql);
    sql_q.addBindValue(classID);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    while (sql_q.next()) {
        detail myDetail ={
            sql_q.value(0).toInt(),
            sql_q.value(1).toInt(),
            sql_q.value(2).toString(),
            sql_q.value(3).toInt(),
            sql_q.value(4).toInt(),
            sql_q.value(5).toInt(),
            sql_q.value(6).toInt(),
            sql_q.value(7).toInt(),
            sql_q.value(8).toInt(),
            sql_q.value(9).toInt(),
            sql_q.value(10).toInt(),
            sql_q.value(11).toInt(),
            sql_q.value(12).toInt(),
            sql_q.value(13).toInt(),
            sql_q.value(14).toInt(),
            sql_q.value(15).toInt()
        };
        qDebug()<<"get details :";
        qdebugDetail;
        details<<myDetail;
    }
    return details;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHeaderView>
#include <QComboBox>
#include <QTableWidgetItem>
#include <addclass.h>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    myDB = new db();
    //    qDebug()<< myDB->setClass("呆扳手","8-10");
    //    qDebug()<< myDB->setClass("呆扳手","9-11");
    //    qDebug()<<myDB->getEtalon("呆扳手");
    //    detail myDetail = {0,3,"2014.06.18",3,4,5,6,7,8,9,10};
    //    qDebug()<< myDB->setDetail(myDetail);
    //    qDebug()<< myDB->updateDetail((detail){0,3,"2014.06.18",44,4,5,6,7,8,9,10});
    //    qDebug()<< myDB->getDetail(1).at(0).date;
    //    ui->namesComboBox->addItems(myDB->getAllName());
    //    changeEtalon(ui->namesComboBox->currentText());
    QObject::connect(ui->namesComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(changeEtalon(QString)));
    ui->namesComboBox->addItems(myDB->getAllName());
    //        ui->tableWidget->setRowCount(1);
    //        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("2221")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEtalon(QString name)
{
    ui->etalonComboBox->clear();
    ui->etalonComboBox->addItems(myDB->getEtalon(name));
}

void MainWindow::addRow(QList<detail> d)
{
    clearRow();
    int detailsSize = d.size();
    qDebug()<<"get details size is "<<detailsSize;
    if(detailsSize>=0)
    {
        ui->tableWidget->setRowCount(detailsSize);
        int i = 0;
        for(;i<detailsSize;i++){
            detail m_detail = d.at(i);
            qDebug()<<"addRow "<<i<<m_detail.id<<m_detail.classID<<m_detail.date<<m_detail.number<<m_detail.summary<<m_detail.income<<m_detail.lend_long<<m_detail.lend_sort<<m_detail.loss<<m_detail.lost<<m_detail.total;
            //            ui->tableWidget->setItem(0,0,new QTableWidgetItem("2222"));
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(m_detail.id)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(m_detail.date)));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(m_detail.number,10)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(m_detail.summary,10)));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(m_detail.income,10)));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(m_detail.lend_long),10));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(m_detail.lend_sort,10)));
            ui->tableWidget->setItem(i,7,new QTableWidgetItem(QString::number(m_detail.loss,10)));
            ui->tableWidget->setItem(i,8,new QTableWidgetItem(QString::number(m_detail.lost,10)));
            ui->tableWidget->setItem(i,9,new QTableWidgetItem(QString::number(m_detail.t_lend_long,10)));
            ui->tableWidget->setItem(i,10,new QTableWidgetItem(QString::number(m_detail.t_lend_sort,10)));
            ui->tableWidget->setItem(i,11,new QTableWidgetItem(QString::number(m_detail.t_new,10)));
            ui->tableWidget->setItem(i,12,new QTableWidgetItem(QString::number(m_detail.t_old,10)));
            ui->tableWidget->setItem(i,13,new QTableWidgetItem(QString::number(m_detail.t_total,10)));
            ui->tableWidget->setItem(i,14,new QTableWidgetItem(QString::number(m_detail.total,10)));
            //    ui->tableWidget->setItem(0,9,new QTableWidgetItem(d.date));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
    setCulReadOnlay();
}

void MainWindow::clearRow()
{
    ui->tableWidget->clearContents();
}

void MainWindow::setCulReadOnlay()
{
    int rowSize = ui->tableWidget->rowCount();
    qDebug()<<"row size is "<<rowSize;
    for(int i=0;i<rowSize;i++)
    {
//                if(ui->tableWidget->item(i,0) == NULL){
//                    ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString("")));
//                }
        ui->tableWidget->item(i, 0)->setFlags(Qt::NoItemFlags);
    }
}

void MainWindow::initItem(int row)
{
    int colSize = ui->tableWidget->columnCount();
    qDebug()<<"column size is "<<colSize;
    for(int i = 0;i<colSize;i++)
    {

        ui->tableWidget->setItem(row,i,new QTableWidgetItem(QString("")));
    }
}

void MainWindow::on_serachButton_clicked()
{
    QString name = ui->namesComboBox->currentText();
    QString etalon = ui->etalonComboBox->currentText();
    qDebug()<<"serach : name is "<<name<<" etalon is "<<etalon;
    int id = myDB->getClassID(name,etalon);
    qDebug()<<"serach : ID is "<<id;
    QList<detail> myDetails = myDB->getDetails(id);
    addRow(myDetails);

}

void MainWindow::on_addButton_clicked()
{
    int i = ui->tableWidget->rowCount() + 1;
    ui->tableWidget->setRowCount(i);
    initItem(i - 1);
    setCulReadOnlay();
}

void MainWindow::on_delButton_clicked()
{
    if(ui->tableWidget->rowCount() > 0 and ui->tableWidget->currentRow() >= 0)
    {
        QMessageBox::StandardButton delWarn = QMessageBox::warning(NULL, "删除提示", "是否删除第"+QString::number(ui->tableWidget->currentRow() + 1,10)+"行数据,删除无法恢复!!!", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(delWarn == QMessageBox::Yes)
        {
            //            qDebug()<<ui->tableWidget->currentRow();
            int id = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().toInt();
            myDB->delDetail(id);
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());

        }
    }
}

void MainWindow::on_commitButton_clicked()
{
    int row = ui->tableWidget->currentRow();
//    qDebug()<<"row is "<<row;
    if(row < 0)
    {
        QMessageBox::critical(0, tr("警告"), tr("请选择需要提交的一行记录"));
        return;
    }
    int classId = myDB->getClassID(ui->namesComboBox->currentText(),ui->etalonComboBox->currentText());
    detail m_detal ={
        ui->tableWidget->item(row,0)->text().toInt(),
        classId,
        ui->tableWidget->item(row,1)->text(),
        ui->tableWidget->item(row,2)->text().toInt(),
        ui->tableWidget->item(row,3)->text().toInt(),
        ui->tableWidget->item(row,4)->text().toInt(),
        ui->tableWidget->item(row,5)->text().toInt(),
        ui->tableWidget->item(row,6)->text().toInt(),
        ui->tableWidget->item(row,7)->text().toInt(),
        ui->tableWidget->item(row,8)->text().toInt(),
        ui->tableWidget->item(row,9)->text().toInt(),
        ui->tableWidget->item(row,10)->text().toInt(),
        ui->tableWidget->item(row,11)->text().toInt(),
        ui->tableWidget->item(row,12)->text().toInt(),
        ui->tableWidget->item(row,13)->text().toInt(),
        ui->tableWidget->item(row,14)->text().toInt()
    };
    qDebug()<<"m_detal.id "/*<<m_detal.id*/;
    if(m_detal.id == 0)
    {
        myDB->setDetail(m_detal);
    }
    else {
        myDB->updateDetail(m_detal);
    }
}

void MainWindow::on_addClassButton_clicked()
{
    //    addClass* ac = new addClass(myDB);
    //    QObject::connect(ac,SIGNAL(changeNames()),this,SLOT(flushNames()));
    //    ac->show();
    addClass ac(myDB,this);
    ac.exec();
    flushNames();
    this->on_serachButton_clicked();
}

void MainWindow::flushNames()
{
    ui->namesComboBox->clear();
    ui->namesComboBox->addItems(myDB->getAllName());
}

void MainWindow::on_exportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save excel"),".", tr("Microsoft Office 2003 (*.csv)"));//获取保存路径
    if (fileName.isEmpty()) {
        QMessageBox::critical(0, tr("错误"), tr("要保存的文件名为空！"));
        return;
    }
    QFile* m_file = new QFile(fileName);
    if(m_file->open(QIODevice::WriteOnly))
    {
        m_file->write("物品名:,");
        m_file->write(ui->namesComboBox->currentText().toUtf8().data());
        m_file->write(",规格:,");
        m_file->write(ui->etalonComboBox->currentText().toUtf8().data());
        m_file->write("\n");
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            m_file->write(ui->tableWidget->horizontalHeaderItem(j)->text().toUtf8().data());
            if(j!=ui->tableWidget->columnCount() -1)
            {
                m_file->write(",");
            }
        }
        m_file->write("\n");

        for(int i = 0;i<ui->tableWidget->rowCount();i++)
        {
            for(int j=0;j<ui->tableWidget->columnCount();j++)
            {
                m_file->write(ui->tableWidget->item(i,j)->text().toUtf8().data());
                if(j!=ui->tableWidget->columnCount() -1)
                {
                    m_file->write(",");
                }
            }
            if(i!=ui->tableWidget->rowCount() -1 )
            {
                m_file->write("\n");
            }
        }
        m_file->close();
    }


    QMessageBox::information(this, tr("OK"), tr("保存成功！"));
}
